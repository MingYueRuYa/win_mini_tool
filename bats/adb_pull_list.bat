@rem ʹ��adb pull list��ÿ��·����Ӧ���ļ�
@rem ��ʽ��list.example.txt
@echo off
for /F "eol=#" %%i  in (list.txt) do (
echo %%i
adb pull /system/bin/%%i .
)
pause