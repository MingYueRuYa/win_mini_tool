#include <stdio.h>
#include <TChar.h>
#include <windows.h>
#include <locale.h>

int main(int argc, char* argv[]){
    setlocale(LC_ALL, "");//���ñ�������,���������ٿ���̨�������ֿ��ַ�    
    printf("test printf��\n");
    printf("%.32hs","����һ��%%.32hs��ʽ���ַ���12345678912345678912345678945613123\n");
    printf("\n");
    printf("%.32Ls",L"12321һ��%%.32ls��ʽ���ַ���");//result: 1
    printf("%.32LS",L"12321һ��%%.32ls��ʽ���ַ���");//<���û��setlocale��������ֻ��ӡ��12321


    return 0;
}