/******************************************************************************
 *  ��Ȩ���У�C��terry.zhao                                                   *
 *  ��������Ȩ����                                                            *
*******************************************************************************
 *  ��Դ : https://github.com/k1988/win_mini_tool
 *  �汾 : 1.0
 *  ����˵������ʾ��ǰϵͳ��session����
******************************************************************************/
/*  �޸ļ�¼: 
      ����       �汾    �޸���             �޸�����
    --------------------------------------------------------------------------
******************************************************************************/

#include <windows.h>   
#include <commctrl.h>   
#include <process.h>   
#include <WtsApi32.h> 
#include <cstdio>
#include <TCHar.h>

#pragma comment(lib, "WtsApi32.lib")
   
int GetSessionNum(DWORD &SessionNum)   
{   
    DWORD i;   
    HANDLE hServer;    
   
    DWORD dwSiCount = 0;    //ͳ�Ƶ�ǰ���е�½ϵͳ�ĻỰ����   
    DWORD dwSiCountbak = 0;    
    DWORD dwSize  =  0;    
    TCHAR *szLogName  =  NULL;  //��¼��ǰ��½ϵͳ���û���   
    PWTS_SESSION_INFO session_info = NULL;   
   
    hServer = WTSOpenServer(NULL);    
    if (hServer)    
    {    
        WTSEnumerateSessions(hServer, 0, 1, &session_info, &dwSiCount);    
   
        dwSiCountbak = dwSiCount;   
        for( i = 0; i < dwSiCountbak; i++ )    
        {     
            if ( WTSQuerySessionInformation( hServer,   
                session_info[i].SessionId,    
                WTSUserName,    
                &szLogName,    
                &dwSize) )    
            {   
                //����û���Ϊ�յģ���ͳ���ڻỰ������   
                if ( strcmp( szLogName,"" ) == 0 )   
                {   
                    dwSiCount--;   
                }   
                printf("ID:%-8luUserName:%s\n", session_info[i].SessionId, szLogName);   
                WTSFreeMemory(szLogName);      
            }   
        }    
    }    
   
    SessionNum = dwSiCount;   
   
    WTSFreeMemory(session_info);    
    WTSCloseServer(hServer);    
    return 0;   
}   
   
int _tmain(int argc, _TCHAR* argv[])   
{   
    DWORD SessionNum;   
    GetSessionNum(SessionNum);   
    printf("SessionCount=%lu\n",SessionNum);   
    getchar();   
    return 0;   
}  