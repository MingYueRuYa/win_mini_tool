@echo off
@cd %~dp0%
@%~d0%
@set regpath="HKEY_CURRENT_USER\Environment"

for,/f,"skip=2 tokens=1,2,*",%%a,in,('reg query %regpath% /v Path'),do,(
        echo ԭ��������:
        :echo %%a :path
        :echo %%b :ע�������
        echo %%c
	echo;
	:FIXME TODO ����жϵ�ǰpath�Ƿ��Ѿ����˵�ǰĿ¼
	echo ���ĺ󻷾�����
	echo %%c;%CD%;%CD%\bin;%CD%\bats;%CD%\scripts
        reg add %regpath% /v Path /t REG_EXPAND_SZ /d "%%c;%CD%;%CD%\bin;%CD%\bats;%CD%\scripts;" /f
	goto :eof
)

:eof
pause