#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef double DataType;

typedef struct HTNode
{
	DataType weight; //权值
	int parent; //双亲
	int lc, rc; //左右孩子
}*HuffmanTree;

typedef char **HuffmanCode;

//构建哈夫曼树
void CreateHuff(HuffmanTree& HT, DataType* w, int n);
//生成哈夫曼编码
void HuffCoding(HuffmanTree& HT, HuffmanCode& HC, int n);
//typedef char  **HuffmanCode; //动态分配数组存储赫夫曼编码表

//void HuffmanCoding(HuffmanTree &HT, HuffmanCode &HC, int *w, int n);
//
//void select(HuffmanTree t, int i, int& s1, int& s2);
//
//int min(HuffmanTree t, int i);