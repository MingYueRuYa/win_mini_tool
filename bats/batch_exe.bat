@echo off
cd %~dp0%
%~d0%
echo --------------------------------------------------  >> log.txt
echo %date% >> log.txt
for %%i in (*.exe) do (
"%%i" >> log.txt
if %errorlevel%==0 (
echo "ִ�� %%i �ɹ�" >> log.txt
) else (
echo "ִ�� %%i ʧ��" >> log.txt
goto error
)
)
goto ok

:error
pause

:ok
