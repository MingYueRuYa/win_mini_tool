#coding=gbk
# ʹ��ָ��·�����·������
import winreg
winreg.SetValueEx(winreg.CreateKey(winreg.HKEY_LOCAL_MACHINE,r"Software\xxx"),'First', None, winreg.REG_DWORD, 1)