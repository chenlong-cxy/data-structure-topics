#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef double DataType; //���Ȩֵ����������

typedef struct HTNode //����������Ϣ
{
	DataType weight; //Ȩֵ
	int parent; //���ڵ�
	int lc, rc; //���Һ���
}*HuffmanTree;

typedef char **HuffmanCode;

//������������
void CreateHuff(HuffmanTree& HT, DataType* w, int n);
//���ɹ���������
void HuffCoding(HuffmanTree& HT, HuffmanCode& HC, int n);