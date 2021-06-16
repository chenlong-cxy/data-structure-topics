#define _CRT_SECURE_NO_WARNINGS 1
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//typedef double DataType;
//
//typedef struct HTNode
//{
//	DataType weight; //Ȩ��
//	int parent; //����
//	int lc, rc; //���Һ���
//}*HuffmanTree;
//
//typedef char **HuffmanCode;
//
////���±�Ϊ1��i-1�ķ�Χ�ҵ�Ȩ����С������ֵ���±꣬����s1��Ȩ��С��s2��Ȩ��
//void Select(HuffmanTree& HT, int n, int& s1, int& s2)
//{
//	int min;
//	//�ҵ�һ����Сֵ
//	for (int i = 1; i <= n; i++)
//	{
//		if (HT[i].parent == 0)
//		{
//			min = i;
//			break;
//		}
//	}
//	for (int i = min + 1; i <= n; i++)
//	{
//		if (HT[i].parent == 0 && HT[i].weight < HT[min].weight)
//			min = i;
//	}
//	s1 = min;
//	//�ҵڶ�����Сֵ
//	for (int i = 1; i <= n; i++)
//	{
//		if (HT[i].parent == 0 && i != s1)
//		{
//			min = i;
//			break;
//		}
//	}
//	for (int i = min + 1; i <= n; i++)
//	{
//		if (HT[i].parent == 0 && HT[i].weight < HT[min].weight&&i != s1)
//			min = i;
//	}
//	s2 = min;
//}
////������������
//void CreateHuff(HuffmanTree& HT, DataType* w, int n)
//{
//	int m = 2 * n - 1; //���������ܽ����
//	HT = (HuffmanTree)calloc(m + 1, sizeof(HTNode)); //��m+1��HTNode����Ϊ�±�Ϊ0��HTNode���洢����
//	for (int i = 1; i <= n; i++)
//	{
//		HT[i].weight = w[i - 1]; //��Ȩֵ
//	}
//	for (int i = n + 1; i <= m; i++)
//	{
//		int s1, s2;
//		Select(HT, i - 1, s1, s2); //���±�Ϊ1��i-1�ķ�Χ�ҵ�Ȩ����С������ֵ���±꣬����s1��Ȩ��С��s2��Ȩ��
//		HT[i].weight = HT[s1].weight + HT[s2].weight; //i��Ȩ����s1��s2��Ȩ��֮��
//		HT[s1].parent = i; //s1�ĸ�����i
//		HT[s2].parent = i; //s2�ĸ�����i
//		HT[i].lc = s1; //������s1
//		HT[i].rc = s2; //�Һ�����s2
//	}
//	printf("��������Ϊ:>\n");
//	printf("   w      p  lc rc\n");
//	printf("0             \n");
//	for (int i = 1; i <= m; i++)
//	{
//		printf("%-2d %-6.2lf %-2d %-2d %-2d\n", i, HT[i].weight, HT[i].parent, HT[i].lc, HT[i].rc);
//	}
//	printf("\n");
//}
////���ɹ���������
//void HuffCoding(HuffmanTree& HT, HuffmanCode& HC, int n)
//{
//	HC = (HuffmanCode)malloc(sizeof(char*)*(n + 1)); //�±�Ϊ0��λ�ò���
//	char* code = (char*)malloc(sizeof(char)*n);
//	code[n - 1] = '\0';
//	for (int i = 1; i <= n; i++)
//	{
//		int start = n - 1;
//		int c = i;
//		int p = HT[c].parent;
//		while (p)
//		{
//			if (HT[p].lc == c)
//				code[--start] = '0';
//			else
//				code[--start] = '1';
//			c = p;
//			p = HT[c].parent;
//		}
//		HC[i] = (char*)malloc(sizeof(char)*(n - start));
//		strcpy(HC[i], &code[start]);
//	}
//	free(code);
//}
//int main()
//{
//	int n = 0;
//	printf("���������ݸ���:>");
//	scanf("%d", &n);
//	DataType* w = (DataType*)malloc(sizeof(DataType)*n);
//	if (w == NULL)
//	{
//		printf("malloc fail\n");
//		exit(-1);
//	}
//	printf("����������:>");
//	for (int i = 0; i < n; i++)
//	{
//		/*scanf("%d", &w[i]);*/
//		scanf("%lf", &w[i]);
//	}
//	HuffmanTree HT;
//	CreateHuff(HT, w, n); //������������
//
//	HuffmanCode HC;
//	HuffCoding(HT, HC, n); //��������������
//
//	for (int i = 1; i <= n; i++)
//	{
//		printf("����%.2lf�ı���Ϊ:%s\n", HT[i].weight, HC[i]);
//	}
//	free(w);
//	return 0;
//}


//typedef int BTDataType;//����д洢��Ԫ������
//
//typedef struct BTNode
//{
//	BTDataType data;//����д洢��Ԫ������
//	struct BTNode* left;//��ָ����ָ�����ӣ�
//	struct BTNode* right;//��ָ����ָ���Һ��ӣ�
//}BTNode;

////Ҷ�ӽ��ĸ���
//int BinaryTreeLeafSize(BTNode* root)
//{
//	if (root == NULL)//������Ҷ�ӽ��
//		return 0;
//	if (root->left == NULL&&root->right == NULL)//��Ҷ�ӽ��
//		return 1;
//	//Ҷ�ӽ��ĸ��� = ��������Ҷ�ӽ����� + ��������Ҷ�ӽ�����
//	return BinaryTreeLeafSize(root->left) + BinaryTreeLeafSize(root->right);
//}


////��ת������
//BTNode* invertTree(BTNode* root)
//{
//	if (root == NULL)//��Ϊ�գ�ֱ�ӷ���
//		return NULL;
//	BTNode* left = invertTree(root->left);//��ת������
//	BTNode* right = invertTree(root->right);//��ת������
//	//��������λ�ý���
//	root->left = right;
//	root->right = left;
//	return root;
//}


//�ð����˳������������ķ�����ͳ�����о��ж�Ϊ1�Ľ����Ŀ
#include "queue.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

typedef char BTDataType;//����д洢��Ԫ�����ͣ���charΪ����

typedef struct BTNode
{
	BTDataType data;//����д洢��Ԫ������
	struct BTNode* left;//��ָ����ָ�����ӣ�
	struct BTNode* right;//��ָ����ָ���Һ��ӣ�
}BTNode;

//�������������ͳ�ƶ�Ϊ1�Ľ������
int OneDegreeLeafSize(BTNode* root)
{
	if (root == NULL)
		return 0;
	Queue q;
	QueueInit(&q); //��ʼ������
	QueuePush(&q, root); //���������
	int count = 0; //ͳ�ƶ�Ϊ1�Ľ��
	while (!QueueEmpty(&q))
	{
		BTNode* front = QueueFront(&q); //ȡ��ͷ����
		QueuePop(&q); //��ͷ������
		if ((front->left&&!(front->right)) || (!(front->left) && front->right))
			count++; //��Ϊ1�Ľ��
		if (front->left) //��Ϊ���������
			QueuePush(&q, front->left);
		if (front->right) //��Ϊ���������
			QueuePush(&q, front->right);

	}
	QueueDestroy(&q); //���ٶ���
	return count;
}

BTNode* BuyNode(BTDataType x)
{
	BTNode* newnode = (BTNode*)malloc(sizeof(BTNode));
	if (newnode == NULL)
	{
		printf("malloc fail\n");
		exit(-1);
	}
	newnode->data = x;
	newnode->left = NULL;
	newnode->right = NULL;
	return newnode;
}
int main()
{
	BTNode* A = BuyNode('A');
	BTNode* B = BuyNode('B');
	BTNode* C = BuyNode('C');
	BTNode* D = BuyNode('D');
	BTNode* E = BuyNode('E');
	BTNode* F = BuyNode('F');
	A->left = B;
	A->right = C;
	B->left = D;
	C->left = E;
	D->left = F;
	int count =  OneDegreeLeafSize(A);
	printf("%d\n", count);
	return 0;
}