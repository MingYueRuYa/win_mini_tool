@echo off
rem AndroidĬ�ϵ��ĵ�����fileЭ��򿪵ģ���Щ�ط���̫���㣬��ʹ��php�����������������������
cd %ANDROID_HOME%\docs
D:
start cmd.exe /c php.exe -S 0.0.0.0:81
start http://127.0.0.1:81/reference/