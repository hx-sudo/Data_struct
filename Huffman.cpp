//��ȡ�ļ������ɹ��������͹���������
#include<iostream>
#include<Stdlib.h>
#include"Huffman.h"
using namespace std;



int creattree(Huffmantree pHT, int weight[], int n)//���ɹ���������Ҷ����
{
	int a1, a2;
	for (int i = 0; i < n; i++)//���ļ���Ϣ����Ҷ�ӽڵ���
	{
		pHT[i+1].weight = weight[i];
		pHT[i + 1].lchild = 0;
		pHT[i + 1].rchild = 0;
		pHT[i + 1].parent = 0;
	}
					
	int m = 2 * n - 1;	//Huffman������n��Ҷ�ӽڵ�,��2n-1���ڵ�  

	return 0;
}

int select(Huffmantree pHT, int nSize)//ѡ��������Ȩֵ��С�Ľڵ�
{
	int minValue = 0x7FFFFFFF;//��Сֵ
	int min = 0;//Ԫ�����

	//�ҵ���СȨֵ��Ԫ�����
	for (int i = 1; i <= nSize; i++)
	{
		if (pHT[i].parent == 0 && pHT[i].weight < minValue)
		{
			minValue = pHT[i].weight;
			min = i;
		}
	}
	return min;
}



