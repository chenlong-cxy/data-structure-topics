#include "HTree.h"







//int min(HuffmanTree t, int i)
//{ // 函数void select()调用
//	int j, flag;
//	unsigned int k = UINT_MAX;  // 取k为不小于可能的值
//	for (j = 1; j <= i; j++)
//	if (t[j].weight<k&&t[j].parent == 0)
//		k = t[j].weight, flag = j;
//	t[flag].parent = 1;
//	return flag;
//}
//
//
//
//void select(HuffmanTree t, int i, int& s1, int& s2)
//{ // s1为最小的两个值中序号小的那个
//	int j;
//	s1 = min(t, i);
//	s2 = min(t, i);
//	if (s1>s2)
//	{
//		j = s1;
//		s1 = s2;
//		s2 = j;
//	}
//} //select
//
//
//void HuffmanCoding(HuffmanTree &HT, HuffmanCode &HC, int *w, int n)
//{
//	if (n <= 1) return;
//	m = 2 * n - 1;
//	HT = (HuffmanTree)malloc((m + 1)*sizeof(HTNode));
//	for (p = HT + 1, i = 1; i <= n; ++i, ++p, ++w)  *p = { *w, 0, 0, 0 };
//	for (; i <= m; ++i, ++p)  *p = { 0, 0, 0, 0 };
//	for (i = n + 1; i <= m; ++i){
//		Select(HT, i - 1, s1, s2);
//		HT[s1].parent = i;  HT[s2].parent = i;
//		HT[i].lchild = s1;  HT[i].rchild = s2;
//		HT[i].weight = HT[s1].weight + HT[s2].weight;
//	}
//	HC = (HuffmanCode)malloc((n + 1)*sizeof(char *));
//	cd = (char *)malloc(n*sizeof(char));
//	cd[n - 1] = '\0';
//	for (i = 1; i <= n; ++i){
//		start = n - 1;
//		for (c = i, f = HT[i].parent; f != 0; c = f, f = HT[f].parent)
//		if (HT[f].lchild == c) cd[--start] = '0';
//		else cd[--start] = '1';
//		HC[i] = (char *)malloc(n - start)*sizeof(char));
//		strcpy(HC[i], &cd[start];
//	}
//	free(cd);
//}//HuffmanCoding 


