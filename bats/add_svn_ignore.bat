@echo off
rem �����������;

rem �ο����ӣ�http://stackoverflow.com/questions/17298668/svn-ignore-like-gitignore
rem �ο�������
rem svn propset svn:ignore -RF /root/svn-ignore.txt . [dot for current dir]
rem ������ͨ��

set txt_path=%~dp0%
svn propset svn:global-ignores -F "%txt_path%svn_ignored_common.txt" %cd%

rem java����
svn propset svn:global-ignores -F "%txt_path%\svn_ignored_java.txt" %cd%

rem android studio
svn propset svn:ignore -F "%txt_path%\svn_ignored_android_studio.txt" %cd%
pause
