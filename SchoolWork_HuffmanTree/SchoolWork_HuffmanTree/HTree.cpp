#include "HTree.h"





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


//���±�Ϊ1��i-1�ķ�Χ�ҵ�Ȩ����С������ֵ���±꣬����s1��Ȩ��С��s2��Ȩ��
void Select(HuffmanTree& HT, int n, int& s1, int& s2)
{
	int min;
	//�ҵ�һ����Сֵ
	for (int i = 1; i <= n; i++)
	{
		if (HT[i].parent == 0)
		{
			min = i;
			break;
		}
	}
	for (int i = min + 1; i <= n; i++)
	{
		if (HT[i].parent == 0 && HT[i].weight < HT[min].weight)
			min = i;
	}
	s1 = min;
	//�ҵڶ�����Сֵ
	for (int i = 1; i <= n; i++)
	{
		if (HT[i].parent == 0 && i != s1)
		{
			min = i;
			break;
		}
	}
	for (int i = min + 1; i <= n; i++)
	{
		if (HT[i].parent == 0 && HT[i].weight < HT[min].weight&&i != s1)
			min = i;
	}
	s2 = min;
}

//������������
void CreateHuff(HuffmanTree& HT, DataType* w, int n)
{
	int m = 2 * n - 1; //���������ܽ����
	HT = (HuffmanTree)calloc(m + 1, sizeof(HTNode)); //��m+1��HTNode����Ϊ�±�Ϊ0��HTNode���洢����
	for (int i = 1; i <= n; i++)
	{
		HT[i].weight = w[i - 1]; //��Ȩֵ
	}
	for (int i = n + 1; i <= m; i++)
	{
		int s1, s2;
		Select(HT, i - 1, s1, s2); //���±�Ϊ1��i-1�ķ�Χ�ҵ�Ȩ����С������ֵ���±꣬����s1��Ȩ��С��s2��Ȩ��
		HT[i].weight = HT[s1].weight + HT[s2].weight; //i��Ȩ����s1��s2��Ȩ��֮��
		HT[s1].parent = i; //s1�ĸ�����i
		HT[s2].parent = i; //s2�ĸ�����i
		HT[i].lc = s1; //������s1
		HT[i].rc = s2; //�Һ�����s2
	}
	printf("��������Ϊ:>\n");
	printf("   w      p  lc rc\n");
	printf("0             \n");
	for (int i = 1; i <= m; i++)
	{
		/*printf("%-2d %-2d %-2d %-2d %-2d\n", i, HT[i].weight, HT[i].parent, HT[i].lc, HT[i].rc);*/
		printf("%-2d %-6.2lf %-2d %-2d %-2d\n", i, HT[i].weight, HT[i].parent, HT[i].lc, HT[i].rc);
	}
	printf("\n");
}

//���ɹ���������
void HuffCoding(HuffmanTree& HT, HuffmanCode& HC, int n)
{
	HC = (HuffmanCode)malloc(sizeof(char*)*(n + 1)); //�±�Ϊ0��λ�ò���
	char* code = (char*)malloc(sizeof(char)*n);
	code[n - 1] = '\0';
	for (int i = 1; i <= n; i++)
	{
		int start = n - 1;
		int c = i;
		int p = HT[c].parent;
		while (p)
		{
			if (HT[p].lc == c)
				code[--start] = '0';
			else
				code[--start] = '1';
			c = p;
			p = HT[c].parent;
		}
		HC[i] = (char*)malloc(sizeof(char)*(n - start));
		strcpy(HC[i], &code[start]);
	}
	free(code);
}