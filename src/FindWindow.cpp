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


void main(int argc,char*argv[])
{
    if (argc < 3){
        printf("usage: FindWindow \"lpClassName\" \"lpWindowsName\"");
    }
    
    HWND hResultHwnd = ::FindWindowA(argv[1], argv[2]);

    char info[INFO_LEN] = {0};
    DumpWindow(hResultHwnd, info);
    printf("Find result: %s\n", info);
}
