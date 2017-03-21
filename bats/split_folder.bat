@echo off 
rem 
set usage=Usage��split_folder Դ�ļ���(�ɼ�ͨ���) Ŀ���ļ���

rem ����ֵ�Դ�ļ���
set src=%1%

rem ��ֵ�Ŀ���ļ���
set dest=%2%

rem ������
if {%src%} == {} echo "%usage%" && goto end
if {%dest%} == {} echo "%usage%" && goto end

rem ÿһҳ����
set page_count=2

rem ��ʼҳ��
set cur_page=0

rem ��ʼҳ������
set index=0

SETLOCAL ENABLEDELAYEDEXPANSION 

rem ѭ�������оٳ������ļ��������������󣬿ɸ������copy���
for /f "delims=" %%i in ('dir /b /s /a-d %src%') do (
    set /a index = !index! + 1
    set /a cur_page = !index! / %page_count%
    if not exist %dest%\!cur_page! mkdir %dest%\!cur_page!
    
    copy "%%i" "%dest%\!cur_page!\%%~nxi" 
)   

:end
pause