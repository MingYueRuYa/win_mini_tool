/******************************************************************************
 *  ��Ȩ���У�C��terry.zhao                                                   *
 *  ��������Ȩ����                                                            *
*******************************************************************************
 *  ��Դ : https://github.com/k1988/win_mini_tool
 *  �汾 : 1.0
 *  ����˵�������ָ�����ƴ��ڣ���������֮
******************************************************************************/
/*  �޸ļ�¼: 
      ����       �汾    �޸���             �޸�����
    --------------------------------------------------------------------------
******************************************************************************/

#include <windows.h>
#include <stdio.h>

#pragma comment(lib, "User32.lib")

//#define CHANGE_TITLE 0

//#define CHANGE_ICON 0

#define CHANGE_WINDOW 1

volatile bool quit = 0;
BOOL stop(DWORD signal)
{
	switch(signal)
	{
	case CTRL_C_EVENT:    
	case CTRL_BREAK_EVENT:
	case CTRL_CLOSE_EVENT:
	case CTRL_LOGOFF_EVENT:
	case CTRL_SHUTDOWN_EVENT:
		quit = 1;
		MessageBox(NULL, "", "", MB_OK);
		break;
	}
	return TRUE;
}

void main(int argn, char* argv[])
{
	if (argn < 2)
	{
		printf("usage: winhide ���ڱ��� [hide|deamon|restore]\ndesc:���ػ�ԭ����\n\thide:���ش��ڲ����˳�\n\tdeamon:���Ӵ��ڣ�һ�����ִ���������֮�����ұ��ֽ��̲��˳������û��˳�����̨ʱ��ԭ����\n\trestore:��ԭ�����صĴ���");
		return;
	}
	char* windowTitle = argv[1];
	char* mode = "hide";
	if (argn > 2)
	{
		mode = argv[2];
	}
	
	if (stricmp(mode, "restore") == 0)
	{
		HWND dest = FindWindow(NULL, windowTitle);
		if (!dest)
		{
			printf("Window not found,exit...");
			return;
		}

#ifdef CHANGE_WINDOW
		DWORD orgStyle = ::GetWindowLong(dest, GWL_EXSTYLE);
		::SetWindowLong(dest, GWL_EXSTYLE, orgStyle & ~WS_EX_TOOLWINDOW);
		::SetWindowPos(dest, NULL, 400, 400, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_HIDEWINDOW | SWP_FRAMECHANGED);
		//::SendMessage(dest, WM_SYSCOMMAND, SC_MINIMIZE, NULL);
		::ShowWindow(dest, SW_MINIMIZE);
#endif // CHANGE_WINDOW

		return;
	}

	SetConsoleCtrlHandler( (PHANDLER_ROUTINE)stop, TRUE);
	do 
	{
		HWND dest = FindWindow(NULL, windowTitle);
		if (!quit && !dest)
		{
			Sleep(200);
			continue;
		}

		printf("Window found: 0x%x\n", dest);
		Sleep(200);

#ifdef CHANGE_TITLE
		SetWindowText(dest, "���±�");
#endif // CHANGE_TITLE

#ifdef CHANGE_ICON
		// ���´���δ�ɹ�
		LRESULT bigIcon = SendMessage(dest, WM_GETICON,ICON_BIG, NULL);
		LRESULT smallIcon = SendMessage(dest, WM_GETICON,ICON_SMALL, NULL);
		SendMessage(dest, WM_SETICON, ICON_BIG,NULL);
		SendMessage(dest, WM_SETICON, ICON_SMALL,NULL);
#endif // CHANGE_ICON

		ShowWindow(dest, SW_HIDE);
		DWORD orgStyle = ::GetWindowLong(dest, GWL_EXSTYLE);
		::SetWindowLong(dest, GWL_EXSTYLE, orgStyle | WS_EX_TOOLWINDOW);
		//::SetWindowPos(dest, NULL, -9999, -9999, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_HIDEWINDOW | SWP_FRAMECHANGED);

		if (stricmp(mode, "deamon") != 0)
		{
			//���ػ�ģʽ
			printf("not deamon mode, exit...");
			return;
		}

		printf("deamon mode...");
		while (!quit && ::IsWindow(dest))
		{
			Sleep(200);
		}

		if (quit)
		{
#ifdef CHANGE_ICON
			SendMessage(dest, WM_SETICON, ICON_BIG, (LPARAM)bigIcon);
			SendMessage(dest, WM_SETICON, ICON_SMALL, (LPARAM)smallIcon);
#endif // CHANGE_ICON

#ifdef CHANGE_TITLE
			SetWindowText(dest, windowTitle);
#endif // CHANGE_TITLE

#ifdef CHANGE_WINDOW
			::ShowWindow(dest, SW_MINIMIZE);
			::SetWindowLong(dest, GWL_EXSTYLE, orgStyle);
			::SendMessage(dest, WM_SYSCOMMAND, SC_MINIMIZE, NULL);
#endif // CHANGE_WINDOW
			break;
		}
		else
		{
			printf("Window destory: 0x%x\n", dest);
		}
	} while (true);
}
