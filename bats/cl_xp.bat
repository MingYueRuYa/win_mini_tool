@rem ��vs2012������ƽ̨�ϣ�������xpΪĿ������
@rem SET CL=/D_USING_V140_SDK71_;%CL% 
@rem SET PATH=C:\Program Files (x86)\Microsoft SDKs\Windows\v7.1A\Bin;%PATH%  
@rem SET INCLUDE=C:\Program Files (x86)\Microsoft SDKs\Windows\v7.1A\Include;%INCLUDE%  
@rem SET LIB=C:\Program Files (x86)\Microsoft SDKs\Windows\v7.1A\Lib;%LIB% 

@rem ����ǿ���̨����Ҫ��/subsystem:window,5.01 �ĳ� /subsystem:console,5.01
cl /D_USING_V140_SDK71_ /link /subsystem:window,5.01  %1 %2 %3 %4 %5 %6 %7 %8 %9