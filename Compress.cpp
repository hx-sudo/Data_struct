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
	HEAD head;
	InitHead(filename, head);//��ʼ��
	Showweight_(head.weight);//��ʾȨֵ

	Huffmantree pHT = new HTNode[256];//Fuffman��



	return 0;
}

int Encode()//���ù���������ʵ���ļ�ѹ��
{


	return 0;

}


int WriteFile()//��ѹ���������д�����ļ�
{

	return 0;


}


int Showweight_(int weight[])//չʾȨֵ
{
	cout << "256���ֽڳ��ֵĴ�����" << endl;
	cout << "�ֽ�\t"<<"Ȩ��\t"<<endl;
	for (int i = 0; i < 256; i++)
	{
		cout << i << "\t" << weight[i] << endl;
	}
	return 0;
}







