//读取文件，生成哈夫曼树和哈夫曼编码
#include<iostream>
#include<Stdlib.h>
#include"Huffman.h"
#pragma warning(disable : 4996)
using namespace std;


int select(Huffmantree pHT, int nSize)//选择数组中权值最小的节点
{
	int minValue = 0x7FFFFFFF;//最小值
	int min = 0;//元素序号

	//找到最小权值的元素序号
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




int creattree(Huffmantree pHT, int weight[], int n)//生成哈夫曼树，节点，权值，叶子数,根序号即m
{
	int a1, a2;//两节点序号
	for (int i = 0; i < n; i++)//将文件信息送入叶子节点中
	{
		pHT[i].weight = weight[i];
		pHT[i].lchild = 0;
		pHT[i].rchild = 0;
		pHT[i].parent = 0;
	}
					
	int m = 2 * n - 1;	//Huffman树共有n个叶子节点,有2n-1个节点  
	for (int i = n; i <m; i++) {
		a1=select(pHT, i);//选择最小的权值节点
		pHT[a1].parent = i;
		pHT[i].lchild = a1;

		a2 = select(pHT, i);//选择第二小的权值节点
		pHT[a2].parent = i;
		pHT[i].rchild = a2;

		pHT[i].weight = pHT[a1].weight + pHT[a2].weight;
		pHT[i].parent = 0;
	}

	return 0;
}



int  creatcoding(Huffmantree pHT, Huffmancode pHC)//生成哈夫曼编码,左零右一
{
//	pHC = new HCNode[n ];//哈夫曼编码，
	char *cd=new char[256];//编码
	cd[255] = '\0';

    //从叶子到根逆向求编码
	for (int i = 0; i < 256; i++)
	{
		int f = pHT[i].parent;
		int n = 255;
		int k = 0;//计数
		for (int j = i; f != 0;f=pHT[f].parent)
		{
			if (pHT[f].lchild == j)
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
		strcpy(pHC[i].code, &cd[n]);
	

	}
	delete cd;
	return 0;
}


int Showcode(Huffmancode pHC)//展示Huffman编码
{
	cout << "256中字符对应的Huffman编码：" << endl;
	cout << "字节Ascii码\t\t" << "编码\t\t" << endl;
	for (int i = 0; i < 256; i++)
	{
		cout << i << "\t\t" << pHC[i].code<<endl;
	}
	return 0;
}



