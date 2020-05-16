//ѹ���ļ�������ѹ���ļ�

#include <iostream>
#include<stdlib.h>
#include"Compress.h"
#include"Huffman.h"
using namespace std;

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
	HEAD head;//ͷ�ļ�������ԭ�ļ�������Ϣ
	if (InitHead(filename, head) == 1)//��ʼ��ԭ�ļ�
	{
		return 1;//�ļ���ʧ��
	}
	//��ʾȨֵ
	//Showweight_(head.weight);

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
		nSize += head.weight[i] * strlen(pHC[i].code);
	}





	Encode();

	return 0;
}

int Encode(const char* pFilename, const Huffmancode pHC, char* pBuffer, const int nSize)//���ù���������ԭ�ļ����±��룬���浽����char
{
	FILE* in = fopen(pFilename, "rb");
	char ch;//���ֽڶ�ȡ

	return 0;

}

int Str2byte(const char* pBinStr)//���ַ���ת��Ϊ�ֽڣ��õ����ձ��룬���浽*.buf�ļ���
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


int WriteFile()//��ѹ���������д�����ļ�
{

	return 0;


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







