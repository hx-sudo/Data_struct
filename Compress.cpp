//压缩文件，保存压缩文件

#include <iostream>
#include<stdlib.h>
#include"Compress.h"
#include"Huffman.h"


using namespace std;

HEAD head;//头文件，保存原文件基本信息


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
	if (InitHead(filename, head) == 1)//初始化原文件
	{
		return 1;//文件打开失败
	}
	//显示权值
	Showweight_(head.weight);

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
		nSize += head.weight[i] * (int)strlen(pHC[i].code);
	}
	nSize = (nSize % 8) ? nSize / 8 + 1 : nSize / 8;//总字节数

	//对原文件压缩编码
	char* pBuffer = NULL;
	//开辟缓冲区
	pBuffer = (char*)malloc(nSize * sizeof(char));
	if (!pBuffer)
	{
		cerr << "开辟缓冲区失败" << endl;
		return 1;
	}

	Encode(filename, pHC, pBuffer, nSize);
//	if (!pBuffer)
//	{
//		cout << "压缩错误一！" << endl;
//		return 1;
//	}
	
	int len=WriteFile(filename, head, pBuffer, nSize);//存入新压缩文件
	cout << head.length << "字节（原）" << endl;
	cout << len <<"字节（新）" << endl;
	cout << "压缩比率：" << (float)(len *100)/ head.length <<"%"<< endl;

	return 0;
}



//利用哈夫曼编码原文件重新编码，保存到数组char
int Encode(const char* pFilename, const Huffmancode pHC, char* pBuffer, const int nSize)
{
	FILE* in = fopen(pFilename, "rb");
	char cd[SIZE] = { 0 };//保存编码字符串,工作区
	int pos = 0;//缓冲区指针
	unsigned char ch;
	//扫描文件，根据哈夫曼编码表压缩，暂存到缓冲区
	while ((ch = fgetc(in)) != EOF)
	{
		strcat(cd, pHC[ch].code);
		//压缩编码
		while (strlen(cd) >= 8)
		{
			
			//截取左边8个字符编码成字节
			if ( pos >nSize * sizeof(char))
			{
				cout << "压缩错误二！" << endl;
				return 1;

			}
			else
				pBuffer[pos++] = Str2byte(cd);

			//字符串整体左移8
			for (int i = 0; i < SIZE - 8; i++)
			{
				cd[i] = cd[i + 8];
			}
		}
	}
	if (strlen(cd) > 0)//剩余
	{
		pBuffer[pos++] = Str2byte(cd);
	}

	fclose(in);
	return 0;

}

char Str2byte(const char* pBinStr)//将字符串转化为字节，得到最终编码，保存到*.buf文件中
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


int WriteFile(const char* Filename, const HEAD shead, const char* pBuffer, const int nSize)//将压缩后的数据写入新文件
{
	//生成文件名
	char filename[256] = { 0 };
	strcpy(filename, Filename);
	strcat(filename, ".buf");
	//以二进制流打开文件
	FILE* out = fopen(filename, "wb");
	//写文件头
	fwrite(&shead, sizeof(HEAD), 1, out);
	//写压缩后的编码
	fwrite(pBuffer, sizeof(char), nSize, out);
	fclose(out);
	out = NULL;

	cout << "生成压缩文件：" << filename << endl;
	int len = sizeof(HEAD) + (int)strlen(Filename) + 1 + nSize;//压缩后文件长度
	return len;


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







