/******************************************************************************
 *  ��Ȩ���У�C��terry.zhao                                                   *
 *  ��������Ȩ����                                                            *
*******************************************************************************
 *  ��Դ : https://github.com/k1988/win_mini_tool
 *  �汾 : 1.0
 *  ����˵�������ϵͳ��ǰ���㴰�ڣ�����ӡ���ô�����Ϣ
******************************************************************************/
/*  �޸ļ�¼: 
      ����       �汾    �޸���             �޸�����
    --------------------------------------------------------------------------
******************************************************************************/

#include <windows.h>
#include <stdio.h>

#pragma comment(lib, "User32.lib")

#define INFO_LEN 1024

void DumpWindow(HWND hwnd, char info[INFO_LEN])
{
	char title[MAX_PATH] = {0};
	char className[MAX_PATH] = {0};

	GetWindowText(hwnd, title, MAX_PATH);
	GetClassName(hwnd, className, MAX_PATH);
	
	sprintf(info, "%x \n\ttitle=%s\n\tclass=%s\n", hwnd, title, className);
}


void main()
{
	do 
	{
		HWND forge = ::GetForegroundWindow();

		//��ǰǰ�ô��ڵ��߳�id
		DWORD dwForeID = GetWindowThreadProcessId(forge, NULL);

		//Ŀ�괰�ڵ��߳�id
		DWORD dwDstID = GetWindowThreadProcessId(forge, NULL);

		::AttachThreadInput(dwDstID, dwForeID, TRUE);
		HWND focus = ::GetFocus();
		HWND active = ::GetActiveWindow();
		::AttachThreadInput(dwDstID, dwForeID, FALSE);

		char info[INFO_LEN] = {0};
		DumpWindow(forge, info);
		printf("forge: %s\n", info);

		//DumpWindow(focus, info);
		//printf("focus: %s\n", info);

		//DumpWindow(active, info);
		//printf("active: %s\n", info);

		Sleep(1000);
	} while (true);
}
