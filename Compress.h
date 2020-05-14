#pragma once
#ifndef COMPRESS_H
#define COMPRESS_H

typedef struct 
{
	char type[4];//�ļ�����
	int length;//ԭ�ļ�����
	int weight[256];//Ȩֵ��ֵ
}HEAD;//ͷ�ļ�������ԭ�ļ�������Ϣ



int InitHead(const char *filename,HEAD &head);//��ʼ���ļ�ͷ������Ϣ����ȡԭ�ļ���

int Compress( char* filename) ;//ʵ��ѹ���ļ�


int Encode();//���ù���������ʵ���ļ�ѹ��

int WriteFile();//��ѹ���������д�����ļ�

int Showweight_(int weight[]);//չʾȨֵ




#endif // !COMPRESS_H
