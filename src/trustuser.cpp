/******************************************************************************
 *  ��Ȩ���У�C��terry.zhao                                                   *
 *  ��������Ȩ����                                                            *
*******************************************************************************
 *  ��Դ : https://github.com/k1988/win_mini_tool
 *  �汾 : 1.0
 *  ����˵�������Ȩ��
******************************************************************************/
/*  �޸ļ�¼: 
      ����       �汾    �޸���             �޸�����
    --------------------------------------------------------------------------
******************************************************************************/

#include <windows.h>
#include <Aclapi.h>
#include <cstdio>

#pragma comment(lib, "Advapi32.lib")

//
//bool SetDACL(string filePath, string userName)
//{
//	//��ȡ�ʻ���Ϣ	
//	char sid[100];
//	DWORD sidBufferSize = 100;
//	char domainName[MAX_PATH] = {0};
//	DWORD domainBufferSize = MAX_PATH;
//	SID_NAME_USE sidType = SidTypeUser;
//	bool result = LookupAccountName(null, userName.c_str(), sid, &sidBufferSize, domainName, &domainBufferSize, sidType);
//
//	if (!result)
//	{
//		return false;
//	}
//
//	//��ȡ�ļ�������
//	ManagementPath path = new ManagementPath();
//	path.Server = ".";
//	path.NamespacePath = @"\root\cimv2";
//	path.RelativePath = @"Win32_LogicalFileSecuritySetting.Path='" + filePath + "'";
//	ManagementObject dir = new ManagementObject(path);
//	ManagementBaseObject outParams = dir.InvokeMethod("GetSecurityDescriptor", null, null);
//
//	if (((uint)(outParams.Properties["ReturnValue"].Value)) != 0)
//	{
//		throw new Exception("��ȡ�ļ�������ʧ��");
//	}
//	ManagementBaseObject Descriptor = ((ManagementBaseObject)(outParams.Properties["Descriptor"].Value));
//
//	//��ȡ���ʿ����б�
//	ManagementBaseObject[] DaclObject = ((ManagementBaseObject[])(Descriptor.Properties["Dacl"].Value));
//
//	//����һ�����ʿ�����
//	ManagementBaseObject ace = (ManagementBaseObject)DaclObject[0].Clone();
//
//	//���÷��ʿ���������
//	ManagementBaseObject trustee = (ManagementBaseObject)ace.Properties["Trustee"].Value;
//	//   return ace.Properties["AccessMask"].Value.ToString();
//	trustee.Properties["Domain"].Value = domainName.ToString();
//	trustee.Properties["Name"].Value = userName;
//	trustee.Properties["SID"].Value = userSid;
//	trustee.Properties["SidLength"].Value = 28;//trustee.Properties["SIDString"].Value="S-1-5-21-602162358-708899826-854245398-1005";
//
//	ace.Properties["Trustee"].Value = trustee;
//	ace.Properties["AccessMask"].Value = 1245631;//2032127��ȫ����//1245631�޸�Ȩ��
//	ace.Properties["AceFlags"].Value = 3;//����AccessMaskָ���ķ��ʼ���
//	ace.Properties["AceType"].Value = 0;//����AccessMaskָ���ķ��ʼ���
//
//	//����һ�ݷ��ʿ����б������������ɵķ��ʿ�������ӵ����
//	ManagementBaseObject[] newDacl = new ManagementBaseObject[DaclObject.Length + 1];
//	for (int i = 0; i < DaclObject.Length; i++)
//	{
//		newDacl[i] = DaclObject[i];
//	}
//
//	newDacl[DaclObject.Length] = ace;
//	//����ȫ��������DACL������Ϊ�����ɵķ��ʿ����б�
//	Descriptor.Properties["Dacl"].Value = newDacl;
//
//	//���ð�ȫ������
//	dir.Scope.Options.EnablePrivileges = true;
//
//	ManagementBaseObject inProperties = dir.GetMethodParameters("SetSecurityDescriptor");
//	inProperties["Descriptor"] = Descriptor;
//	outParams = dir.InvokeMethod("SetSecurityDescriptor", inProperties, null);
//}

int step = 0;

//
// ����ĳ���˻���ĳ���ļ�(��)�����в���Ȩ��
// pszPath: �ļ�(��)·��
// pszAccount: �˻�����
//
BOOL EnableFileAccountPrivilege(PCTSTR pszPath, PCTSTR pszAccount)
{
	BOOL bSuccess = TRUE;
	PACL pNewDacl = NULL, pOldDacl = NULL;
	EXPLICIT_ACCESS ea;
	do
	{
		// ��ȡ�ļ�(��)��ȫ�����DACL�б�
		if (ERROR_SUCCESS != ::GetNamedSecurityInfo ((LPTSTR)pszPath, SE_FILE_OBJECT, DACL_SECURITY_INFORMATION, NULL, NULL, &pOldDacl, NULL, NULL))
		{
			step = 1;
			bSuccess = FALSE;
			break;
		}
		// �˴�����ֱ����AddAccessAllowedAce����,��Ϊ���е�DACL�����ǹ̶�,�������´���һ��DACL����
		// ����ָ���û��ʻ��ķ��ʿ�����Ϣ(����ָ������ȫ���ķ���Ȩ��)
		::BuildExplicitAccessWithName (&ea, (LPTSTR)pszAccount, GENERIC_ALL, GRANT_ACCESS, 
SUB_CONTAINERS_AND_OBJECTS_INHERIT);
		step = 2;
		// �����µ�ACL����(�ϲ����е�ACL����͸����ɵ��û��ʻ����ʿ�����Ϣ)
		if (ERROR_SUCCESS != ::SetEntriesInAcl(1, &ea, pOldDacl, &pNewDacl))
		{
			step = 3;
			bSuccess = FALSE;
			break;
		}

		// �����ļ�(��)��ȫ�����DACL�б�
		if (ERROR_SUCCESS != ::SetNamedSecurityInfo ((LPTSTR)pszPath, SE_FILE_OBJECT, DACL_SECURITY_INFORMATION, NULL, NULL, pNewDacl, NULL))
		{
			step = 4;
			printf("����:%d", GetLastError());
			bSuccess = FALSE;
		}
	} while (FALSE);

	// �ͷ���Դ
	if (pNewDacl != NULL)
	{
		::LocalFree(pNewDacl);
	}
	return bSuccess;
}

/*
//ATL��װ�˰�ȫ��������,��ATL��д�ͼ򵥶���: //
// ����ĳ���˻���ĳ���ļ�(��)�����в���Ȩ��(ATL�汾)
// pszPath: �ļ�(��)·��
// pszAccount: �˻�����
//
BOOL AtlEnableFileAccountPrivilege (PCTSTR pszPath, PCTSTR pszAccount)
{
	CDacl dacl;
	CSid sid;
	// ��ȡ�û��ʻ���־��
	if (!sid.LoadAccount (pszAccount))
	{
		return FALSE;
	}
	// ��ȡ�ļ�(��)��DACL
	if (!AtlGetDacl (pszPath, SE_FILE_OBJECT, &dacl))
	{
		return FALSE;
	}
	// ��DACL������µ�ACE��
	dacl.AddAllowedAce (sid, GENERIC_ALL);
	// �����ļ�(��)��DACL
	return AtlSetDacl (pszPath, SE_FILE_OBJECT, dacl) ? TRUE : FALSE;
}
*/

void main()
{
	//FIXME TODO

	// Get and display the user name. 
	DWORD size = MAX_PATH;
	char username[MAX_PATH] = {0};
	if(!GetUserName(username, &size))
	{
		printf("����:%d", GetLastError());
	}

	printf( "\nUser name:%s\n", username);
	if (FALSE == EnableFileAccountPrivilege("C:\\windows\\winsxs\\Manifests", username))
	//if (FALSE == EnableFileAccountPrivilege("D:\\test\\cl\\testdir\\", username))
	{
		printf("step:%d, ����:%d", step, GetLastError());
	}
	getchar();
}
