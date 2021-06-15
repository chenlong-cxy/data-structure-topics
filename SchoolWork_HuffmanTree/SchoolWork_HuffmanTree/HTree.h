#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef double DataType;

typedef struct HTNode
{
	DataType weight; //Ȩֵ
	int parent; //˫��
	int lc, rc; //���Һ���
}*HuffmanTree;

typedef char **HuffmanCode;

//������������
void CreateHuff(HuffmanTree& HT, DataType* w, int n);
//���ɹ���������
void HuffCoding(HuffmanTree& HT, HuffmanCode& HC, int n);
//typedef char  **HuffmanCode; //��̬��������洢�շ��������

//void HuffmanCoding(HuffmanTree &HT, HuffmanCode &HC, int *w, int n);
//
//void select(HuffmanTree t, int i, int& s1, int& s2);
//
//int min(HuffmanTree t, int i);