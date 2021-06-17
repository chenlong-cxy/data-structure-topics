#include "HTree.h"

//���±�Ϊ1��i-1�ķ�Χ�ҵ�Ȩֵ��С������ֵ���±꣬����s1��ȨֵС��s2��Ȩֵ
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
	s1 = min; //��һ����Сֵ��s1
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
	s2 = min; //�ڶ�����Сֵ��s2
}

//������������
void CreateHuff(HuffmanTree& HT, DataType* w, int n)
{
	int m = 2 * n - 1; //���������ܽ����
	HT = (HuffmanTree)calloc(m + 1, sizeof(HTNode)); //��m+1��HTNode����Ϊ�±�Ϊ0��HTNode���洢����
	for (int i = 1; i <= n; i++)
	{
		HT[i].weight = w[i - 1]; //��Ȩֵ��n��Ҷ�ӽ��
	}
	for (int i = n + 1; i <= m; i++) //������������
	{
		//ѡ��Ȩֵ��С��s1��s2���������ǵĸ����
		int s1, s2;
		Select(HT, i - 1, s1, s2); //���±�Ϊ1��i-1�ķ�Χ�ҵ�Ȩֵ��С������ֵ���±꣬����s1��ȨֵС��s2��Ȩֵ
		HT[i].weight = HT[s1].weight + HT[s2].weight; //i��Ȩ����s1��s2��Ȩ��֮��
		HT[s1].parent = i; //s1�ĸ�����i
		HT[s2].parent = i; //s2�ĸ�����i
		HT[i].lc = s1; //������s1
		HT[i].rc = s2; //�Һ�����s2
	}
	//��ӡ���������и����֮��Ĺ�ϵ
	printf("��������Ϊ:>\n");
	printf("�±�   Ȩֵ     �����   ����   �Һ���\n");
	printf("0                                  \n");
	for (int i = 1; i <= m; i++)
	{
		/*printf("%-2d %-2d %-2d %-2d %-2d\n", i, HT[i].weight, HT[i].parent, HT[i].lc, HT[i].rc);*/
		printf("%-4d   %-6.2lf   %-6d   %-6d   %-6d\n", i, HT[i].weight, HT[i].parent, HT[i].lc, HT[i].rc);
	}
	printf("\n");
}

//���ɹ���������
void HuffCoding(HuffmanTree& HT, HuffmanCode& HC, int n)
{
	HC = (HuffmanCode)malloc(sizeof(char*)*(n + 1)); //��n+1���ַ�ָ�룬��Ϊ�±�Ϊ0���ַ�����
	char* code = (char*)malloc(sizeof(char)*n); //�����ռ䣬�����Ϊn(�ʱ��ǰn-1�����ڴ洢���ݣ����1�����ڴ��'\0')
	code[n - 1] = '\0'; //�����ռ����һ��λ��Ϊ'\0'
	for (int i = 1; i <= n; i++)
	{
		int start = n - 1; //�Ӹ����ռ��±�Ϊstart��λ�ÿ�ʼΪ��Ч����
		int c = i; //���ڽ��еĵ�i�����ݵı���
		int p = HT[c].parent; //�ҵ������ݵĸ����
		while (p) //ֱ�������Ϊ0���������Ϊ�����ʱ��ֹͣ
		{
			if (HT[p].lc == c) //����ý�����丸�������ӣ������Ϊ0������Ϊ1
				code[--start] = '0';
			else
				code[--start] = '1';
			c = p; //�������Ͻ��б���
			p = HT[c].parent; //c�ĸ����
		}
		HC[i] = (char*)malloc(sizeof(char)*(n - start)); //�������ڴ洢������ڴ�ռ�
		strcpy(HC[i], &code[start]); //�����뿽������Ӧ���ڴ�ռ���
	}
	free(code); //�ͷŸ����ռ�
}