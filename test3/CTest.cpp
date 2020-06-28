#include "pch.h"
#include "CTest.h"
#include"global.h"

//将生成图结构的顶点和边数据保存到目录log.txt文件
void CTest::OutPut(CGraph& g)
{
	//新建日志文件，打开
	CStdioFile file(_T("log.txt"),CFile::modeCreate|CFile::modeReadWrite);
	
	CString strTmp;
	//输出顶点信息
	for (int i = 0; i < NUMELEMENT; i++)
	{
		strTmp.Format(_T("%d\t"), g.GetVertex(i));
		file.WriteString(strTmp);
	}

	//输出关系矩阵
	for (int i = 0; i < NUMELEMENT; i++)
	{
		for (int j = 0; j < NUMELEMENT; j++)
		{
			strTmp.Format(_T("%d\t"), g.GetVertex(i));
			file.WriteString(strTmp);
		}

	}
	file.Flush();

	//关闭文件
	file.Close();

}