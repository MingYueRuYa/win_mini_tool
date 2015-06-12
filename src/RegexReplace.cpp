/******************************************************************************
 *  ��Ȩ���У�C��zhaohaiyang_1988@163.com                                                 *
 *  ��������Ȩ����                                                            *
*******************************************************************************
 *  ��Դ : https://github.com/k1988/win_mini_tool
 *  �汾 : 1.0
 *  ����˵��������ʽ�滻�ı��ļ�
******************************************************************************/
/*  �޸ļ�¼: 
      ����       �汾    �޸���             �޸�����
    --------------------------------------------------------------------------
******************************************************************************/

#include <iostream>
#include <string>
#include "boost/regex.hpp"

void Usage()
{
	std::cout << "������\n" << "������ file srcRegex destRegex" << std::endl;
}

int main(int argc, char* argv[])
{
	if (argc < 4)
	{
		Usage();
		return 0;
	}

	//D:\\predev\\�Զ����\\GMProductVersion.h -> (GM_VER_REVISION )([0-9]*) -> GM_VER_REVISION xxxx
	//D:\\predev\\�Զ����\\GMProductVersion.h -> (VER_REVISION=)([0-9]*) -> VER_REVISION=xxxx
	FILE* inFile = fopen(argv[1], "r+");
	if (!inFile)
	{
		std::cerr << "���ļ�ʧ��" << std::endl;
		return 1;
	}
//boost::regex reg("(VER_REVISION=)([0-9]*)",

	boost::regex reg(argv[2], boost::regex::icase|boost::regex::perl);

	char buffer[4096];
	size_t count = fread(buffer, 1, 4096, inFile);
	if ((count ) > 0)
	{
		std::string s(buffer, count);
		s = boost::regex_replace(s,reg, argv[3]);
		int re = fseek(inFile, 0, SEEK_SET);
		size_t count_write = fwrite(s.c_str(), 1, s.length(), inFile);
		if (count_write != count)
		{
			std::cerr << "��д��һ" << std::endl;
			return 3;
		}
		//std::cout << s;
	}	
	return 0;
}

