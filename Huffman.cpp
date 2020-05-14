//读取文件，生成哈夫曼树和哈夫曼编码
#include<iostream>
#include<Stdlib.h>
#include"Huffman.h"
using namespace std;



int creattree(Huffmantree pHT, int weight[], int n)//生成哈夫曼树，叶子数
{
	int a1, a2;
	for (int i = 0; i < n; i++)//将文件信息送入叶子节点中
	{
		pHT[i+1].weight = weight[i];
		pHT[i + 1].lchild = 0;
		pHT[i + 1].rchild = 0;
		pHT[i + 1].parent = 0;
	}
					
	int m = 2 * n - 1;	//Huffman树共有n个叶子节点,有2n-1个节点  

	return 0;
}

int select(Huffmantree pHT, int nSize)//选择数组中权值最小的节点
{
	int minValue = 0x7FFFFFFF;//最小值
	int min = 0;//元素序号

	//找到最小权值的元素序号
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



