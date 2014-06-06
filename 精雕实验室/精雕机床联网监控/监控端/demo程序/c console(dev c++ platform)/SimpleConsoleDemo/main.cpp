#include <iostream>
#include <dos.h> 
#include <stdio.h> 
#include <windows.h>
#include "NcMonInterface.h"


/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) 
{
	JDMACHMON * pMachMon = CreateJDMachMon();
	if(pMachMon != NULL )
	{
		if(ConnectJDMach(pMachMon, "192.168.40.109"))
		{
			double MachCoord[3], AbsCoord[3], RelCoord[3];
			int nCount = 0;
			while(nCount < 19)
			{
				if(GetMachPos(pMachMon, MachCoord, AbsCoord, RelCoord))
				{
					printf ("��������:%.4f %.4f %.4f \n", MachCoord[0], MachCoord[1], MachCoord[2]);
				}
				else
				{
					break;
				} 
				Sleep(1000);
				nCount++;
			}
			
			//����nc�ļ� 
			SendNcFile(pMachMon, "C:\\(O0502)-��ɰ��Z����.nc", TRUE, TRUE, NULL,NULL);
			Sleep(3000);
			
			DisConnectJDMach(pMachMon);
		} 
		DeleteJDMachMon(pMachMon);		
	}

	return 0;
}
