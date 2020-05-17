#pragma once
#ifndef COMPRESS_H
#define COMPRESS_H
#include "Huffman.h"

const int SIZE = 256;

typedef struct 
{
	char type[4];//文件类型
	int length;//原文件长度
	int weight[256];//权值数值
	int sort;//种类
}HEAD;//头文件，保存原文件基本信息



int InitHead(const char *filename,HEAD &head);//初始化文件头数据信息，读取原文件，

int Compress( char* filename) ;//实现压缩文件


int WriteFile(const char *Filename,const HEAD shead,const char *pBuffer,const int nSize );//将压缩后的数据写入新文件

int Showweight_(int weight[]);//展示权值

char Str2byte(const char *pBinStr);//将字符串转化为字节，得到最终编码，保存到*.buf文件中




#endif // !COMPRESS_H
