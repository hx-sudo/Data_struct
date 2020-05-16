//压缩文件，保存压缩文件

#include <iostream>
#include<stdlib.h>
#include"Compress.h"
#include"Huffman.h"
using namespace std;

#pragma warning(disable : 4996)
int InitHead(const char* filename, HEAD& head)//初始化文件头数据信息，读取原文件，
{
	
	//以二进制流的形式打开文件

	FILE* in = fopen(filename, "rb");
	if (!in)
	{
		cout << "文件打开失败！" << endl;
		return 1;
	}
	int weight[256] = { 0 };//统计重复的次数
	int ch;//读取字
	int length = 0;//文件长度
		//扫描文件，获取权重
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


int Compress(char* filename)//实现压缩文件
{
	HEAD head;//头文件，保存原文件基本信息
	if (InitHead(filename, head) == 1)//初始化原文件
	{
		return 1;//文件打开失败
	}
	//显示权值
	//Showweight_(head.weight);

	Huffmantree pHT = new HTNode[511];//Fuffman树
	Huffmancode pHC = new HCNode[256];//Fuffman编码
	creattree( pHT,head.weight, 256);//生成哈夫曼树
	creatcoding( pHT, pHC);//生成哈夫曼编码
	//显示Huffman编码
	Showcode(pHC);

	//计算编码缓冲区大小
	int nSize = 0;
	for (int i = 0; i < 256; i++)
	{
		nSize += head.weight[i] * strlen(pHC[i].code);
	}





	Encode();

	return 0;
}

int Encode(const char* pFilename, const Huffmancode pHC, char* pBuffer, const int nSize)//利用哈夫曼编码原文件重新编码，保存到数组char
{
	FILE* in = fopen(pFilename, "rb");
	char ch;//逐字节读取

	return 0;

}

int Str2byte(const char* pBinStr)//将字符串转化为字节，得到最终编码，保存到*.buf文件中
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


int WriteFile()//将压缩后的数据写入新文件
{

	return 0;


}


int Showweight_(int weight[])//展示权值
{
	cout << "256种字节出现的次数：" << endl;
	cout << "字节Ascii码\t\t"<<"权重\t\t"<<endl;
	for (int i = 0; i < 256; i++)
	{
		cout << i << "\t\t" << weight[i] << endl;
	}
	return 0;
}







