#include "pch.h"
#include "CTest.h"
#include"global.h"

//������ͼ�ṹ�Ķ���ͱ����ݱ��浽Ŀ¼log.txt�ļ�
void CTest::OutPut(CGraph& g)
{
	//�½���־�ļ�����
	CStdioFile file(_T("log.txt"),CFile::modeCreate|CFile::modeReadWrite);
	
	CString strTmp;
	//���������Ϣ
	for (int i = 0; i < NUMELEMENT; i++)
	{
		strTmp.Format(_T("%d\t"), g.GetVertex(i));
		file.WriteString(strTmp);
	}

	//�����ϵ����
	for (int i = 0; i < NUMELEMENT; i++)
	{
		for (int j = 0; j < NUMELEMENT; j++)
		{
			strTmp.Format(_T("%d\t"), g.GetVertex(i));
			file.WriteString(strTmp);
		}

	}
	file.Flush();

	//�ر��ļ�
	file.Close();

}