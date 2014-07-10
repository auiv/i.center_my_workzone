#ifndef _NC_MON_INTERFACE_H_
#define _NC_MON_INTERFACE_H_

#ifdef NC_MON_EXPORT
#define DLL_MONIO __declspec( dllexport )
#else
#define DLL_MONIO __declspec( dllimport )
#endif

#ifndef BOOL
#define BOOL int
#endif

#ifndef UINT
#define UINT unsigned int
#endif

#define JDMACHMON void

//�������ص�����
#ifndef SetProgPosFunPtr
typedef	void (*SetProgPosFunPtr)(void * pProgCtrl, int ProgPos);
#endif

//API for c users
#ifdef __cplusplus 
extern "C" {
#endif

	/*-------------------------------------------------------------------------
	[����]:����������ض���(new)
	---------------------------------------------------------------------------*/
	DLL_MONIO JDMACHMON *  __cdecl CreateJDMachMon();

	/*-------------------------------------------------------------------------
	[����]:���ٻ�����ض���(delete)
	---------------------------------------------------------------------------*/
	DLL_MONIO void __cdecl DeleteJDMachMon(JDMACHMON * & JDMachMon);

	/*-------------------------------------------------------------------------
	[����]:���ӵ�����
	[����]:servername:����IP��ַ
	[����]:TRUE:�ɹ� FALSE:ʧ��
	---------------------------------------------------------------------------*/
	DLL_MONIO BOOL __cdecl ConnectJDMach(JDMACHMON *JDMachMon, const char* servername);

	/*-------------------------------------------------------------------------
	[����]:������Ͽ�����
	[����]:TRUE:�ɹ� FALSE:ʧ��
	---------------------------------------------------------------------------*/
	DLL_MONIO BOOL __cdecl DisConnectJDMach(JDMACHMON *JDMachMon);
	
	/*-------------------------------------------------------------------------
	[����]:��ȡ��������
	[���]: MachCoord:��������;  AbsCoord:��������; RelCoord:�������
	[����]:TRUE:�ɹ� FALSE:ʧ��
	---------------------------------------------------------------------------*/
	DLL_MONIO BOOL __cdecl GetMachPos(JDMACHMON *JDMachMon, double MachCoord[3],double AbsCoord[3],double RelCoord[3]);

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
	DLL_MONIO BOOL __cdecl GetMachAlmInfo(JDMACHMON *JDMachMon, int * AlmInfo);


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
	DLL_MONIO BOOL __cdecl GetProgState(JDMACHMON *JDMachMon, int * ProgState);

	/*-------------------------------------------------------------------------
	[����]:��������ͼӹ��ļ�
	       ע���������ڽ��мӹ�ʱ�������䷢�ͼӹ��ļ�
	[����]:FileName:�����ļ�����(full path name)
		   AddToTsk: �Ƿ��Զ����ص�����
		   pProgCtrl:�������ؼ�ָ��; ProgFunPtr:�������ص�����.  �������Ҫ��ʾ������,������������NULL
	---------------------------------------------------------------------------*/
	DLL_MONIO BOOL __cdecl SendFile(JDMACHMON *JDMachMon, BOOL AddToTsk, const char * FileName, void * pProgCtrl, SetProgPosFunPtr ProgPosPtr = NULL);

	/*-------------------------------------------------------------------------
	[����]:���������NC�ӹ��ļ�(�ϴ�)
	[����]:FileName:�����ļ�����(full path name)
		   AddToTsk: �Ƿ��Զ���ӵ����� (ע: ��̨��Ҫ����EDIT��RESET״̬)
		   SetMainProgram: �Ƿ���ӵ�������(AddToTskΪTRUEʱ��Ч)
	       pProgCtrl:�������ؼ�ָ��; ProgFunPtr:�������ص�����.  �������Ҫ��ʾ������,������������NULL
	---------------------------------------------------------------------------*/
	DLL_MONIO BOOL __cdecl  SendNcFile(JDMACHMON *JDMachMon, const char * FileName, BOOL AddToTsk, BOOL SetMainProgram, 
								void * pProgCtrl, SetProgPosFunPtr ProgPosPtr = NULL);

	/*-------------------------------------------------------------------------
	[����]:�Ƿ���������������ļ�
	---------------------------------------------------------------------------*/
	DLL_MONIO BOOL __cdecl IsSendingFile(const JDMACHMON *JDMachMon);

	/*-------------------------------------------------------------------------
	[����]:�Ƿ����ڽ����ļ�(�����ļ�)
	---------------------------------------------------------------------------*/
	DLL_MONIO BOOL __cdecl IsRcvingFile(const JDMACHMON *JDMachMon);

	/*-------------------------------------------------------------------------
	[����]:�Ƿ�ͻ�������
	---------------------------------------------------------------------------*/
	DLL_MONIO BOOL __cdecl IsConncect(const JDMACHMON *JDMachMon) ;

	/*-------------------------------------------------------------------------
	[����]:���ػ����ļ�
	[����]:SrcFileName:�������ļ�����(full path name)
		   DestFileName: �����ļ�����
	       pProgCtrl:�������ؼ�ָ��; ProgFunPtr:�������ص�����.  �������Ҫ��ʾ������,������������NULL
	[����]:TRUE:�ɹ� FALSE:ʧ��
	---------------------------------------------------------------------------*/
	DLL_MONIO BOOL ReceiveFile(JDMACHMON *JDMachMon, const char * SrcFileName, const char * DestFileName, void * pProgCtrl, SetProgPosFunPtr ProgPosPtr = NULL);


	/*-------------------------------------------------------------------------
	[����]:��ȡ����ģ̬��Ϣ
	[���]: CurrWCoord:��ǰ��������ϵ(��54��ʼ����1:  G54 , G55, G56, G57, G58, G59)
			Feedrate     : ��ǰ�����ٶ�
	        SpindleSpeed : ��ǰ����ת��
			ToolNo       : ��ǰ���ߺ�
			MachTime     : �ӹ�ʱ��(��������ʱ��) ��
			CurrO        : ��ǰ�����
			CurrMainO    : ��ǰ�������
	[����]:TRUE:�ɹ� FALSE:ʧ��
	---------------------------------------------------------------------------*/
	DLL_MONIO BOOL __cdecl GetBasicModalInfo(JDMACHMON *JDMachMon, int &CurrWCoord, float & Feedrate, int & SpindleSpeed, int & ToolNo, float & MachTime,
				int & CurrO, int & CurrMainO);

	/*-------------------------------------------------------------------------
	[����]:��ȡ�ļ��б�
	[����]: DestDir     : ��̨�ļ���Ŀ¼
	StrBufSize  : �ļ��б��ַ�������������
	[���]  FileList    : �ļ��б��ַ���
	[����]:TRUE:�ɹ� FALSE:ʧ��
	---------------------------------------------------------------------------*/
	DLL_MONIO BOOL __cdecl GetMachFileList(JDMACHMON *JDMachMon, const char *DestDir, int StrBufSize, char * FileList);

	/*-------------------------------------------------------------------------
	[����]:ɾ���ļ�
	[����]: DestDir     : ��̨�ļ���Ŀ¼
	FileName    : ��̨�ļ���Ŀ¼�µ�ĳ���ļ���(�����ļ���)
	[����]:TRUE:�ɹ� FALSE:ʧ��
	---------------------------------------------------------------------------*/
	DLL_MONIO BOOL __cdecl DelMachFile(JDMACHMON *JDMachMon, const char *DestDir, const char * FileName);

	/*-------------------------------------------------------------------------
	[����]:�������ļ�
	[����]: SrcFileName     : 
			��̨�ļ��� full path
			DestFileName    : �µ��ļ���
	[����]:TRUE:�ɹ� FALSE:ʧ��
	---------------------------------------------------------------------------*/
	DLL_MONIO BOOL __cdecl RenameMachFile(JDMACHMON *JDMachMon, const char *SrcFileName, const char * DestFileName);

	/*-------------------------------------------------------------------------
	[����]:��ȡ�����ӹ���ˮ������(ע������¼1024�������ļӹ�ʱ����ˮ)
	[����]: ArrSize     : ����Ԫ�ظ���
	[���]: WorkpieceCount     : ��������
	        ProgNo             : ���������
			MachTime           : �������ӹ�ʱ��
	[����]:TRUE:�ɹ� FALSE:ʧ��
	---------------------------------------------------------------------------*/
	DLL_MONIO BOOL __cdecl GetWorkpieceMachTimeRecord(JDMACHMON *JDMachMon, int ArrSize,int & WorkpieceCount, int ProgNo[1024], float MachTime[1024]);


	/*-------------------------------------------------------------------------
	[����]:���û��������ļ���(Ŀ¼), full path
	[����]: MachRcvFolder     : ���������ļ���(Ŀ¼) full path
	[����]:TRUE:�ɹ� FALSE:ʧ��
	---------------------------------------------------------------------------*/
	DLL_MONIO BOOL __cdecl SetMachRcvFolder(JDMACHMON *JDMachMon, const char *MachRcvFolder);

	/*-------------------------------------------------------------------------
	[����]:�õ����������ļ���(Ŀ¼), full path
	[����]: MachRcvFolder     : ���������ļ���(Ŀ¼) full path
	[����]:TRUE:�ɹ� FALSE:ʧ��
	---------------------------------------------------------------------------*/
	DLL_MONIO BOOL __cdecl GetMachRcvFolder(JDMACHMON *JDMachMon, char *MachRcvFolder);

	/*-------------------------------------------------------------------------
	[����]:��ȡ�ϸ�����
	---------------------------------------------------------------------------*/
	DLL_MONIO UINT __cdecl GetLastErr(const JDMACHMON *JDMachMon);

#ifdef __cplusplus 
}
#endif


#endif