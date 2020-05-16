//��ȡ�ļ������ɹ��������͹���������
#include<iostream>
#include<Stdlib.h>
#include"Huffman.h"
using namespace std;


int select(Huffmantree pHT, int nSize)//ѡ��������Ȩֵ��С�Ľڵ�
{
	int minValue = 0x7FFFFFFF;//��Сֵ
	int min = 0;//Ԫ�����

	//�ҵ���СȨֵ��Ԫ�����
	for (int i = 0; i < nSize; i++)
	{
		if (pHT[i].parent == 0 && pHT[i].weight < minValue)
		{
			minValue = pHT[i].weight;
			min = i;
		}
	}
	return min;
}




int creattree(Huffmantree pHT, int weight[], int n)//���ɹ����������ڵ㣬Ȩֵ��Ҷ����,����ż�m
{
	int a1, a2;//���ڵ����
	for (int i = 0; i < n; i++)//���ļ���Ϣ����Ҷ�ӽڵ���
	{
		pHT[i+1].weight = weight[i];
		pHT[i + 1].lchild = 0;
		pHT[i + 1].rchild = 0;
		pHT[i + 1].parent = 0;
	}
					
	int m = 2 * n - 1;	//Huffman������n��Ҷ�ӽڵ�,��2n-1���ڵ�  
	for (int i = n; i <m; i++) {
		a1=select(pHT, i);//ѡ����С��Ȩֵ�ڵ�
		pHT[a1].parent = i;
		pHT[i].lchild = a1;

		a2 = select(pHT, i);//ѡ��ڶ�С��Ȩֵ�ڵ�
		pHT[a2].parent = i;
		pHT[i].rchild = a2;

		pHT[i].weight = pHT[a1].weight + pHT[a2].weight;

	}
	pHT[m - 1].parent = 0;

	return 0;
}




int  creatcoding(Huffmantree pHT, Huffmancode pHC)//���ɹ���������,������һ
{
	int n = 256;
	pHC = new HCNode[n ];//���������룬
	char cd[256]={'\0'};//����

    //��Ҷ�ӵ������������
	for (int i = 0; i < n; i++)
	{
		int f = pHT[i].parent;
		int k = 0;//����
		for (int j = i; f != 0;f=pHT[f].parent)
		{
			if ((int)pHT[f].lchild == j)
			{
				cd[--n] = '0';
				k++;
			}
			else
			{
				cd[--n] = '1';
				k++;
			}
			j = f;
		}
		pHC[i].code = new char[k];
		strcpy(pHC[i].code, cd);

	}
	delete cd;
	return 0;
}




