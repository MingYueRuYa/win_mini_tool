#include <stdio.h>
#include <windows.h>
#define FSCTL_SET_SPARSE                CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 49, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)
bool clear_sparse(HANDLE file_handle)
{
	DWORD temp;
	typedef struct _FILE_SET_SPARSE_BUFFER {
	    BOOLEAN SetSparse;
} FILE_SET_SPARSE_BUFFER, *PFILE_SET_SPARSE_BUFFER;
	FILE_SET_SPARSE_BUFFER b;
	b.SetSparse = FALSE;
	if(FALSE == ::DeviceIoControl(file_handle, FSCTL_SET_SPARSE, &b, sizeof(b)
		, 0, 0, &temp, 0))
	{
		DWORD re = GetLastError();
		printf("clear_sparse ʧ�� error code:%d\n", re);
		if (re != ERROR_INVALID_FUNCTION)
		{
		   return false;
		}
	}
	else
	{
		return true;
	}
	return true;
}

bool HasSparseAttribute(HANDLE file)
{
	LARGE_INTEGER fileSize;
	if (!GetFileSizeEx(file, &fileSize))
	{
		return false;
	}

	BY_HANDLE_FILE_INFORMATION fileInfo;
	GetFileInformationByHandle(file, &fileInfo);
	if (fileInfo.dwFileAttributes & FILE_ATTRIBUTE_SPARSE_FILE)
	{
		return true;
	}

	return false;
}


bool is_sparse(HANDLE file)
{
	LARGE_INTEGER file_size;
	if (!GetFileSizeEx(file, &file_size))
		return false;

	typedef struct _FILE_ALLOCATED_RANGE_BUFFER {
		LARGE_INTEGER FileOffset;
		LARGE_INTEGER Length;
	} FILE_ALLOCATED_RANGE_BUFFER, *PFILE_ALLOCATED_RANGE_BUFFER;
#define FSCTL_QUERY_ALLOCATED_RANGES ((0x9 << 16) | (1 << 14) | (51 << 2) | 3)

	FILE_ALLOCATED_RANGE_BUFFER in;
	in.FileOffset.QuadPart = 0;
	in.Length.QuadPart = file_size.QuadPart;

	FILE_ALLOCATED_RANGE_BUFFER out[2];

	DWORD returned_bytes = 0;
	BOOL ret = DeviceIoControl(file, FSCTL_QUERY_ALLOCATED_RANGES, (void*)&in, sizeof(in)
		, out, sizeof(out), &returned_bytes, NULL);

	if (ret == FALSE)
	{
		int error = GetLastError();
		return true;
	}

	// if we only have a single range in the file, we're not sparse
	return returned_bytes != sizeof(FILE_ALLOCATED_RANGE_BUFFER);
}

void main(int argc, char* argv[])
{
	if (argc < 2)
	{
	   printf("error param!!!");
	   return ;
	}
	
   	HANDLE file_handle = CreateFile(argv[1], GENERIC_WRITE | GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (file_handle  == INVALID_HANDLE_VALUE)
	{
		printf("���ļ�ʧ��!!%d\n", GetLastError());
		return;
	}
	
	if (!HasSparseAttribute(file_handle))
	{
		printf("���ļ�û��ϡ������\n");
	}
	else
	{
		printf("���ļ���ϡ���ļ�\n");
		if (is_sparse(file_handle))
		{
			printf("���ļ�����ϡ���\n");
		}
		else
		{
			printf("���ļ�û��ϡ���\n");
		}
	}
	
	printf("ѡ�����:1-����ϡ�� 2-���ϡ��(vistaϵͳǰ��Ч) �������˳�");
	char c = getchar();
	
	if (c == '1')
	{
		printf("����sparse��־!!\n");
		DWORD temp;
		if (FALSE == ::DeviceIoControl(file_handle, FSCTL_SET_SPARSE, 0, 0, 0, 0, &temp, 0))
		{
		   printf("����sparse��־ʧ��:%d!!\n", GetLastError());
		}
		else
		{
		    printf("����sparse��־�ɹ�!!\n");
		}
	}
	else if (c == '2')
	{
		if (!clear_sparse(file_handle))
		{
		   printf("���sparse��־ʧ��!!");
		}
	}
	else
	{
	    return;
	}
	fflush(stdin);
	printf("���⽡�˳�...");
	getchar();
}