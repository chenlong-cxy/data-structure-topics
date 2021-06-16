#define _CRT_SECURE_NO_WARNINGS 1
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//typedef double DataType;
//
//typedef struct HTNode
//{
//	DataType weight; //权重
//	int parent; //父亲
//	int lc, rc; //左右孩子
//}*HuffmanTree;
//
//typedef char **HuffmanCode;
//
////在下标为1到i-1的范围找到权重最小的两个值的下标，其中s1的权重小于s2的权重
//void Select(HuffmanTree& HT, int n, int& s1, int& s2)
//{
//	int min;
//	//找第一个最小值
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
//	//找第二个最小值
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
////构建哈夫曼树
//void CreateHuff(HuffmanTree& HT, DataType* w, int n)
//{
//	int m = 2 * n - 1; //哈夫曼树总结点数
//	HT = (HuffmanTree)calloc(m + 1, sizeof(HTNode)); //开m+1个HTNode，因为下标为0的HTNode不存储数据
//	for (int i = 1; i <= n; i++)
//	{
//		HT[i].weight = w[i - 1]; //赋权值
//	}
//	for (int i = n + 1; i <= m; i++)
//	{
//		int s1, s2;
//		Select(HT, i - 1, s1, s2); //在下标为1到i-1的范围找到权重最小的两个值的下标，其中s1的权重小于s2的权重
//		HT[i].weight = HT[s1].weight + HT[s2].weight; //i的权重是s1和s2的权重之和
//		HT[s1].parent = i; //s1的父亲是i
//		HT[s2].parent = i; //s2的父亲是i
//		HT[i].lc = s1; //左孩子是s1
//		HT[i].rc = s2; //右孩子是s2
//	}
//	printf("哈夫曼树为:>\n");
//	printf("   w      p  lc rc\n");
//	printf("0             \n");
//	for (int i = 1; i <= m; i++)
//	{
//		printf("%-2d %-6.2lf %-2d %-2d %-2d\n", i, HT[i].weight, HT[i].parent, HT[i].lc, HT[i].rc);
//	}
//	printf("\n");
//}
////生成哈夫曼编码
//void HuffCoding(HuffmanTree& HT, HuffmanCode& HC, int n)
//{
//	HC = (HuffmanCode)malloc(sizeof(char*)*(n + 1)); //下标为0的位置不用
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
//	printf("请输入数据个数:>");
//	scanf("%d", &n);
//	DataType* w = (DataType*)malloc(sizeof(DataType)*n);
//	if (w == NULL)
//	{
//		printf("malloc fail\n");
//		exit(-1);
//	}
//	printf("请输入数据:>");
//	for (int i = 0; i < n; i++)
//	{
//		/*scanf("%d", &w[i]);*/
//		scanf("%lf", &w[i]);
//	}
//	HuffmanTree HT;
//	CreateHuff(HT, w, n); //构建哈夫曼树
//
//	HuffmanCode HC;
//	HuffCoding(HT, HC, n); //构建哈夫曼编码
//
//	for (int i = 1; i <= n; i++)
//	{
//		printf("数据%.2lf的编码为:%s\n", HT[i].weight, HC[i]);
//	}
//	free(w);
//	return 0;
//}


//typedef int BTDataType;//结点中存储的元素类型
//
//typedef struct BTNode
//{
//	BTDataType data;//结点中存储的元素类型
//	struct BTNode* left;//左指针域（指向左孩子）
//	struct BTNode* right;//右指针域（指向右孩子）
//}BTNode;

////叶子结点的个数
//int BinaryTreeLeafSize(BTNode* root)
//{
//	if (root == NULL)//空树无叶子结点
//		return 0;
//	if (root->left == NULL&&root->right == NULL)//是叶子结点
//		return 1;
//	//叶子结点的个数 = 左子树的叶子结点个数 + 右子树的叶子结点个数
//	return BinaryTreeLeafSize(root->left) + BinaryTreeLeafSize(root->right);
//}


////翻转二叉树
//BTNode* invertTree(BTNode* root)
//{
//	if (root == NULL)//根为空，直接返回
//		return NULL;
//	BTNode* left = invertTree(root->left);//翻转左子树
//	BTNode* right = invertTree(root->right);//翻转右子树
//	//左右子树位置交换
//	root->left = right;
//	root->right = left;
//	return root;
//}


//用按层次顺序遍历二叉树的方法，统计树中具有度为1的结点数目
#include "queue.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

typedef char BTDataType;//结点中存储的元素类型（以char为例）

typedef struct BTNode
{
	BTDataType data;//结点中存储的元素类型
	struct BTNode* left;//左指针域（指向左孩子）
	struct BTNode* right;//右指针域（指向右孩子）
}BTNode;

//层序遍历二叉树统计度为1的结点总数
int OneDegreeLeafSize(BTNode* root)
{
	if (root == NULL)
		return 0;
	Queue q;
	QueueInit(&q); //初始化队列
	QueuePush(&q, root); //将根入队列
	int count = 0; //统计度为1的结点
	while (!QueueEmpty(&q))
	{
		BTNode* front = QueueFront(&q); //取队头数据
		QueuePop(&q); //队头出队列
		if ((front->left&&!(front->right)) || (!(front->left) && front->right))
			count++; //度为1的结点
		if (front->left) //不为空则入队列
			QueuePush(&q, front->left);
		if (front->right) //不为空则入队列
			QueuePush(&q, front->right);

	}
	QueueDestroy(&q); //销毁队列
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