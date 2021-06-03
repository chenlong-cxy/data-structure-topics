#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct{
	int   weight;   //权值
	int   parent;    //双亲
	int   lchild, rchild; //左右孩子
}HTNode, *HuffmanTree;

void CreateHuff()

//typedef char  **HuffmanCode; //动态分配数组存储赫夫曼编码表

//void HuffmanCoding(HuffmanTree &HT, HuffmanCode &HC, int *w, int n);
//
//void select(HuffmanTree t, int i, int& s1, int& s2);
//
//int min(HuffmanTree t, int i);