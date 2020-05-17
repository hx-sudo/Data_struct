#pragma once
#ifndef COMPRESS_H
#define COMPRESS_H
#include "Huffman.h"

const int SIZE = 256;

typedef struct 
{
	char type[4];//�ļ�����
	int length;//ԭ�ļ�����
	int weight[256];//Ȩֵ��ֵ
	int sort;//����
}HEAD;//ͷ�ļ�������ԭ�ļ�������Ϣ



int InitHead(const char *filename,HEAD &head);//��ʼ���ļ�ͷ������Ϣ����ȡԭ�ļ���

int Compress( char* filename) ;//ʵ��ѹ���ļ�


int WriteFile(const char *Filename,const HEAD shead,const char *pBuffer,const int nSize );//��ѹ���������д�����ļ�

int Showweight_(int weight[]);//չʾȨֵ

char Str2byte(const char *pBinStr);//���ַ���ת��Ϊ�ֽڣ��õ����ձ��룬���浽*.buf�ļ���




#endif // !COMPRESS_H
