#ifndef _CJD_MACH_MON_H_
#define _CJD_MACH_MON_H_


#ifdef NC_MON_EXPORT
#define DLL_MONIO __declspec( dllexport )
#else
#define DLL_MONIO __declspec( dllimport )
#endif

//�������ص�����
#ifndef SetProgPosFunPtr
typedef	void (*SetProgPosFunPtr)(void * pProgCtrl, int ProgPos);
#endif

#include "rpc.h"
#include <winsock.h>

//for c++ user
class DLL_MONIO CJDMachMon
{
public:
	CJDMachMon();
	virtual ~CJDMachMon();

public:
	/*-------------------------------------------------------------------------
	[����]:���ӵ�����
	[����]:servername:����IP��ַ
	[����]:TRUE:�ɹ� FALSE:ʧ��
	---------------------------------------------------------------------------*/
	BOOL ConnectJDMach(const char* servername);

	/*-------------------------------------------------------------------------
	[����]:������Ͽ�����
	[����]:TRUE:�ɹ� FALSE:ʧ��
	---------------------------------------------------------------------------*/
	BOOL DisConnectJDMach();
	
	/*-------------------------------------------------------------------------
	[����]:��ȡ��������
	[���]:MachCoord:��������;  AbsCoord:��������; RelCoord:�������
	[����]:TRUE:�ɹ� FALSE:ʧ��
	---------------------------------------------------------------------------*/
	BOOL GetMachPos(double MachCoord[3],double AbsCoord[3],double RelCoord[3]);

	/*-------------------------------------------------------------------------
	[����]:��ȡ����������Ϣ
	[���]:���µı�����Ϣ֮һ
	enum NcAlmInfo 
	{ 
	NCALM_NO,         //�ޱ���
	NCALM_EMG,        //��ͣ
	NCALM_ERR,        //����
	NCALM_UPS,        //�ⲿ��Դ�ѵ���
	NCALM_PROMPT      //��ʾ
	};
	[����]:TRUE:�ɹ� FALSE:ʧ��
	---------------------------------------------------------------------------*/
	BOOL GetMachAlmInfo(int & AlmInfo);


	/*-------------------------------------------------------------------------
	[����]:��ȡ����״̬
	[���]:���µĳ���״̬֮һ
	//����״̬
	enum NcProgState
	{
		NCPROG_STOP,      //ֹ̬ͣ
		NCPROG_RUN,       //ִ��̬
		NCPROG_PAUSE,     //��̬ͣ
		NCPROG_RESET,     //��λ̬
	};
	[����]:TRUE:�ɹ� FALSE:ʧ��
	---------------------------------------------------------------------------*/
	BOOL GetProgState(int & ProgState);


	/*-------------------------------------------------------------------------
	[����]:��������ͼӹ��ļ�(�ϴ�)
	[����]:FileName:�����ļ�����(full path name)
		   AddToTsk: �Ƿ��Զ����ص����� (ע: ��̨��Ҫ����EDIT��RESET״̬)
	       pProgCtrl:�������ؼ�ָ��; ProgFunPtr:�������ص�����.  �������Ҫ��ʾ������,������������NULL
	---------------------------------------------------------------------------*/
	BOOL SendFile(const char * FileName, BOOL AddToTsk, void * pProgCtrl, SetProgPosFunPtr ProgPosPtr = NULL);

	/*-------------------------------------------------------------------------
	[����]:���������NC�ӹ��ļ�(�ϴ�)
	[����]:FileName:�����ļ�����(full path name)
		   AddToTsk: �Ƿ��Զ���ӵ����� (ע: ��̨��Ҫ����EDIT��RESET״̬)
		   SetMainProgram: �Ƿ���ӵ�������(AddToTskΪTRUEʱ��Ч)
	       pProgCtrl:�������ؼ�ָ��; ProgFunPtr:�������ص�����.  �������Ҫ��ʾ������,������������NULL
	---------------------------------------------------------------------------*/
	BOOL SendNcFile(const char * FileName, BOOL AddToTsk, BOOL SetMainProgram, 
					void * pProgCtrl, SetProgPosFunPtr ProgPosPtr = NULL);


	/*-------------------------------------------------------------------------
	[����]:���ػ����ļ�
	[����]:SrcFileName:�������ļ�����(full path name)
		   DestFileName: �����ļ�����
	       pProgCtrl:�������ؼ�ָ��; ProgFunPtr:�������ص�����.  �������Ҫ��ʾ������,������������NULL
	---------------------------------------------------------------------------*/
	BOOL ReceiveFile(const char * SrcFileName, const char * DestFileName, void * pProgCtrl, SetProgPosFunPtr ProgPosPtr = NULL);

	/*-------------------------------------------------------------------------
	[����]:�����Ƿ���������������ļ�
	---------------------------------------------------------------------------*/
	void SetSendingFile(BOOL SendingFile)  { m_bSendingFile = SendingFile;}

	/*-------------------------------------------------------------------------
	[����]:�����Ƿ����ڽ����ļ�
	---------------------------------------------------------------------------*/
	void SetRcvingFile(BOOL RcvingFile)  { m_bRcvingFile = RcvingFile;}

	/*-------------------------------------------------------------------------
	[����]:�Ƿ���������������ļ�
	---------------------------------------------------------------------------*/
	BOOL IsSendingFile() const { return m_bSendingFile;}

	/*-------------------------------------------------------------------------
	[����]:�Ƿ�ͻ�������
	---------------------------------------------------------------------------*/
	BOOL IsConncect() const { return m_bConnectSuc;}

	/*-------------------------------------------------------------------------
	[����]:�Ƿ����ڽ����ļ�(�����ļ�)
	---------------------------------------------------------------------------*/
	BOOL IsRcvingFile() const { return m_bRcvingFile; }

	/*-------------------------------------------------------------------------
	[����]:��ȡ����ģ̬��Ϣ
	[���]: CurrWCoord:��ǰ��������ϵ(��1��ʼ����1:  G54 = 1, G55 = 2, G56, G57, G58, G59)
			Feedrate     : ��ǰ�����ٶ�
	        SpindleSpeed : ��ǰ����ת��
			ToolNo       : ��ǰ���ߺ�
			MachTime     : �ӹ�ʱ��(��������ʱ��) ��
			CurrO        : ��ǰ�����
			CurrMainO    : ��ǰ�������
	[����]:TRUE:�ɹ� FALSE:ʧ��
	---------------------------------------------------------------------------*/
	BOOL GetBasicModalInfo(int &CurrWCoord, float & Feedrate, int & SpindleSpeed, int & ToolNo, float & MachTime,
				int & CurrO, int & CurrMainO);

	/*-------------------------------------------------------------------------
	[����]:��ȡ�ļ��б�
	[����]: DestDir     : ��̨�ļ���Ŀ¼
			StrBufSize  : �ļ��б��ַ�������������
	[���]  FileList    : �ļ��б��ַ���
	[����]:TRUE:�ɹ� FALSE:ʧ��
	---------------------------------------------------------------------------*/
	BOOL GetMachFileList(const char *DestDir, int StrBufSize, char *FileList);

	/*-------------------------------------------------------------------------
	[����]:ɾ���ļ�(����ɾ���ļ���)
	[����]: DestDir     : ��̨�ļ���Ŀ¼
			FileName    : ��̨�ļ���Ŀ¼�µ�ĳ���ļ���(�����ļ���)
	[����]:TRUE:�ɹ� FALSE:ʧ��
	---------------------------------------------------------------------------*/
	BOOL DelMachFile(const char *DestDir, const char * FileName);


	/*-------------------------------------------------------------------------
	[����]:�������ļ�
	[����]: SrcFileName     : ��̨�ļ��� full path
			DestFileName    : �µ��ļ���
	[����]:TRUE:�ɹ� FALSE:ʧ��
	---------------------------------------------------------------------------*/
	BOOL RenameMachFile(const char *SrcFileName, const char * DestFileName);

	/*-------------------------------------------------------------------------
	[����]:��ȡ�����ӹ���ˮ������
	[����]: ArrSize     : ����Ԫ�ظ���
	[���]: WorkpieceCount     : ��������
	        ProgNo             : ���������
			MachTime           : �������ӹ�ʱ��
	[����]:TRUE:�ɹ� FALSE:ʧ��
	---------------------------------------------------------------------------*/
	BOOL GetWorkpieceMachTimeRecord(int ArrSize,int & WorkpieceCount, int ProgNo[1024], float MachTime[1024]);


	/*-------------------------------------------------------------------------
	[����]:���û��������ļ���(Ŀ¼), full path
	[����]: MachRcvFolder     : ���������ļ���(Ŀ¼) full path
	[����]:TRUE:�ɹ� FALSE:ʧ��
	---------------------------------------------------------------------------*/
	BOOL SetMachRcvFolder(const char *MachRcvFolder);

	/*-------------------------------------------------------------------------
	[����]:�õ����������ļ���(Ŀ¼), full path
	[����]: MachRcvFolder     : ���������ļ���(Ŀ¼) full path
	[����]:TRUE:�ɹ� FALSE:ʧ��
	---------------------------------------------------------------------------*/
	BOOL GetMachRcvFolder(char *MachRcvFolder);

	/*-------------------------------------------------------------------------
	[����]:��ȡ�ϸ�����
	---------------------------------------------------------------------------*/
	UINT GetLastErr() const { return m_nCurrErrCode; };
	
	void SetErrCode(UINT ErrCode) { m_nCurrErrCode = ErrCode;}

public:
	BOOL m_bSendNcFile;
	BOOL m_bSetMainNcFile;
	BOOL NotifyAutoLoadFile();
	BOOL NotifyAutoAddNcFile(BOOL SetMainProgram);

protected:

	//׼��RPC����
	BOOL PrepareRPC();

	//����socket����
	BOOL GenSocketConnect(const char* servername,unsigned short portno, SOCKET & OutSocket, BOOL bChkCnnct);

private:
	char           m_csMachIPAddr[64];
	BOOL           m_bConnectSuc;
	unsigned char* m_pszStringBinding;

#define CLIENT_SKT_COUNT 3
	SOCKET         m_aClientSocket[CLIENT_SKT_COUNT]; //�������ļ��ϴ�(����)���ļ�����(����)
	BOOL           m_bSendingFile;
	BOOL           m_bRcvingFile;
	handle_t       m_RPCHandle;

	//�ϸ�������
	UINT           m_nCurrErrCode;
	int            m_nVersion;
};

#endif