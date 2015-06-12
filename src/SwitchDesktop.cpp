/******************************************************************************
 *  ��Ȩ���У�C��terry.zhao                                                   *
 *  ��������Ȩ����                                                            *
*******************************************************************************
 *  ��Դ : https://github.com/k1988/win_mini_tool
 *  �汾 : 1.0
 *  ����˵�����ڲ�ͬ��ϵͳ����֮ǰ�л��������������δ�������л�ʧ��
******************************************************************************/
/*  �޸ļ�¼: 
      ����       �汾    �޸���             �޸�����
    --------------------------------------------------------------------------
******************************************************************************/

#include <windows.h>
#include <stdio.h>

#pragma comment(lib, "User32.lib")

int main(int argc, char* argv[])
{
  if (argc < 2)
  {
     printf("Usage:SwitchDesktop <Desktop Name>\n");
  }
  
  HDESK desk = OpenDesktop(argv[1], 0, FALSE, DESKTOP_SWITCHDESKTOP);
  if (desk == NULL)
  {
    printf("�л�����ʧ�ܣ�%d\n",  GetLastError());
    getchar();
    return 1;
  }
  
  if (SwitchDesktop(desk))
  {
    printf("�л�����ɹ�");    
  } 
  else
  {
    printf("�л�����ʧ�ܣ�%d\n",  GetLastError());  
  }
    getchar();
}