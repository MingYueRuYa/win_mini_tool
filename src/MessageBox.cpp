#include <windows.h>

#pragma comment(lib, "User32.lib")

void main()
{
    MessageBox(NULL, "����һ����Ϣ��ʾ��","��Ϣ��ʾ��", MB_OK | MB_ICONINFORMATION);
    MessageBox(NULL, "����һ��������ʾ��!","������ʾ��", MB_OK | MB_ICONWARNING);    
	MessageBox(NULL, "����һ��ѯ����ʾ��","ѯ����ʾ��", MB_YESNO | MB_ICONQUESTION);
	MessageBox(NULL, "����һ��������ʾ��","������ʾ��", MB_OK | MB_ICONERROR);
}