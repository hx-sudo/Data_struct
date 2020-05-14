#pragma once
#ifndef COMPRESS_H
#define COMPRESS_H

typedef struct 
{
	char type[4];//文件类型
	int length;//原文件长度
	int weight[256];//权值数值
}HEAD;//头文件，保存原文件基本信息



int InitHead(const char *filename,HEAD &head);//初始化文件头数据信息，读取原文件，

int Compress( char* filename) ;//实现压缩文件


int Encode();//利用哈夫曼编码实现文件压缩

int WriteFile();//将压缩后的数据写入新文件

int Showweight_(int weight[]);//展示权值




#endif // !COMPRESS_H
