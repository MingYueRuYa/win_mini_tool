:@echo off
@if {%1}=={} (set /p processName=����Ҫ��ֹ�Ľ������ƣ�����ʹ��ͨ���) ELSE (set processName=%1%)
@if {%processName%}=={} exit
TASKKILL /F /FI "IMAGENAME eq %processName%"
pause