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
	HEAD head;
	InitHead(filename, head);//初始化
	Showweight_(head.weight);//显示权值

	Huffmantree pHT = new HTNode[256];//Fuffman树



	return 0;
}

int Encode()//利用哈夫曼编码实现文件压缩
{


	return 0;

}


int WriteFile()//将压缩后的数据写入新文件
{

	return 0;


}


int Showweight_(int weight[])//展示权值
{
	cout << "256种字节出现的次数：" << endl;
	cout << "字节\t"<<"权重\t"<<endl;
	for (int i = 0; i < 256; i++)
	{
		cout << i << "\t" << weight[i] << endl;
	}
	return 0;
}







