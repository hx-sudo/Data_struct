//ѹ���ļ�������ѹ���ļ�

#include <iostream>
#include<stdlib.h>
#include"Compress.h"
#include"Huffman.h"


using namespace std;

HEAD head;//ͷ�ļ�������ԭ�ļ�������Ϣ


#pragma warning(disable : 4996)
int InitHead(const char* filename, HEAD& head)//��ʼ���ļ�ͷ������Ϣ����ȡԭ�ļ���
{
	
	//�Զ�����������ʽ���ļ�

	FILE* in = fopen(filename, "rb");
	if (!in)
	{
		cout << "�ļ���ʧ�ܣ�" << endl;
		return 1;
	}
	int weight[256] = { 0 };//ͳ���ظ��Ĵ���
	int ch;//��ȡ��
	int length = 0;//�ļ�����
		//ɨ���ļ�����ȡȨ��
	while ((ch = getc(in)) != EOF)
	{
		weight[ch]++;
		length++;
	}
	head.length = length;
	memcpy(head.weight, weight, sizeof(weight));
	strcpy(head.type, "huf");

	fclose(in);
	return 0;
}


int Compress(char* filename)//ʵ��ѹ���ļ�
{
	if (InitHead(filename, head) == 1)//��ʼ��ԭ�ļ�
	{
		return 1;//�ļ���ʧ��
	}
	//��ʾȨֵ
	Showweight_(head.weight);

	Huffmantree pHT = new HTNode[511];//Fuffman��
	Huffmancode pHC = new HCNode[256];//Fuffman����
	creattree( pHT,head.weight, 256);//���ɹ�������
	creatcoding( pHT, pHC);//���ɹ���������
	//��ʾHuffman����
	Showcode(pHC);

	//������뻺������С
	int nSize = 0;
	for (int i = 0; i < 256; i++)
	{
		nSize += head.weight[i] * (int)strlen(pHC[i].code);
	}
	nSize = (nSize % 8) ? nSize / 8 + 1 : nSize / 8;//���ֽ���

	//��ԭ�ļ�ѹ������
	char* pBuffer = NULL;
	//���ٻ�����
	pBuffer = (char*)malloc(nSize * sizeof(char));
	if (!pBuffer)
	{
		cerr << "���ٻ�����ʧ��" << endl;
		return 1;
	}

	Encode(filename, pHC, pBuffer, nSize);
//	if (!pBuffer)
//	{
//		cout << "ѹ������һ��" << endl;
//		return 1;
//	}
	
	int len=WriteFile(filename, head, pBuffer, nSize);//������ѹ���ļ�
	cout << head.length << "�ֽڣ�ԭ��" << endl;
	cout << len <<"�ֽڣ��£�" << endl;
	cout << "ѹ�����ʣ�" << (float)(len *100)/ head.length <<"%"<< endl;

	return 0;
}



//���ù���������ԭ�ļ����±��룬���浽����char
int Encode(const char* pFilename, const Huffmancode pHC, char* pBuffer, const int nSize)
{
	FILE* in = fopen(pFilename, "rb");
	char cd[SIZE] = { 0 };//��������ַ���,������
	int pos = 0;//������ָ��
	unsigned char ch;
	//ɨ���ļ������ݹ����������ѹ�����ݴ浽������
	while ((ch = fgetc(in)) != EOF)
	{
		strcat(cd, pHC[ch].code);
		//ѹ������
		while (strlen(cd) >= 8)
		{
			
			//��ȡ���8���ַ�������ֽ�
			if ( pos >nSize * sizeof(char))
			{
				cout << "ѹ���������" << endl;
				return 1;

			}
			else
				pBuffer[pos++] = Str2byte(cd);

			//�ַ�����������8
			for (int i = 0; i < SIZE - 8; i++)
			{
				cd[i] = cd[i + 8];
			}
		}
	}
	if (strlen(cd) > 0)//ʣ��
	{
		pBuffer[pos++] = Str2byte(cd);
	}

	fclose(in);
	return 0;

}

char Str2byte(const char* pBinStr)//���ַ���ת��Ϊ�ֽڣ��õ����ձ��룬���浽*.buf�ļ���
{
	char b = 0x00;
	for (int i = 0; i < 8; i++)
	{
		b = b << 1;
		if (pBinStr[i] == '1')
		{
			b = b | 0x01;
		}
	}
	return b;
}


int WriteFile(const char* Filename, const HEAD shead, const char* pBuffer, const int nSize)//��ѹ���������д�����ļ�
{
	//�����ļ���
	char filename[256] = { 0 };
	strcpy(filename, Filename);
	strcat(filename, ".buf");
	//�Զ����������ļ�
	FILE* out = fopen(filename, "wb");
	//д�ļ�ͷ
	fwrite(&shead, sizeof(HEAD), 1, out);
	//дѹ����ı���
	fwrite(pBuffer, sizeof(char), nSize, out);
	fclose(out);
	out = NULL;

	cout << "����ѹ���ļ���" << filename << endl;
	int len = sizeof(HEAD) + (int)strlen(Filename) + 1 + nSize;//ѹ�����ļ�����
	return len;


}


int Showweight_(int weight[])//չʾȨֵ
{
	cout << "256���ֽڳ��ֵĴ�����" << endl;
	cout << "�ֽ�Ascii��\t\t"<<"Ȩ��\t\t"<<endl;
	for (int i = 0; i < 256; i++)
	{
		cout << i << "\t\t" << weight[i] << endl;
	}
	return 0;
}







