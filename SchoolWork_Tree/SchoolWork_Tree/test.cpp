#include "BinaryTree.h"
#include "queue.h"

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
	/*BTNode* G = BuyNode('G');*/
	A->left = B;
	A->right = C;
	B->left = D;
	/*B->right = G;*/
	C->left = E;
	C->right = F;
	//��ͬ������
	BTNode* W = BuyNode('A');
	BTNode* S = BuyNode('B');
	BTNode* N = BuyNode('C');
	BTNode* H = BuyNode('D');
	BTNode* J = BuyNode('E');
	BTNode* X = BuyNode('F');
	W->left = S;
	W->right = N;
	S->left = H;
	//B->right = G;
	N->left = J;
	N->right = X;
	//�Գƶ�����
	BTNode* T = BuyNode('A');
	BTNode* O = BuyNode('C');
	BTNode* P = BuyNode('C');
	BTNode* Q = BuyNode('D');
	BTNode* R = BuyNode('B');
	BTNode* U = BuyNode('B');
	BTNode* V = BuyNode('b');

	//T->left = O;
	//T->right = P;
	//O->left = Q;
	//O->right = R;
	//P->left = U;
	//P->right = V;
	//�ж�ƽ�������
	T->left = O;
	O->left = P;
	P->left = Q;
	Q->left = R;

	printf("ǰ�����:");
	BinaryPrevOrder(A);
	printf("\n");

	printf("�������:");
	BinaryInOrder(A);
	printf("\n");

	printf("�������:");
	BinaryPostOrder(A);
	printf("\n");

	printf("���ĸ���:%d\n", BinaryTreeSize(A));

	printf("Ҷ�ӽ��ĸ���:%d\n", BinaryTreeLeafSize(A));

	printf("��%d����ĸ���:%d\n", 3, BinaryTreeKLevelSize(A, 3));

	printf("ֵΪ%c�Ľ���ַ:%p\n", 'E', BinaryTreeFind(A, 'E'));
	printf("ֵΪ%c�Ľ���ַ:%p\n", 'G', BinaryTreeFind(A, 'G'));

	printf("������:%d\n", BinaryTreeMaxDepth(A));

	printf("�������:");
	BinaryLevelOrder(A);
	printf("\n");

	printf("�Ƿ�����ȫ������:%d\n", isCompleteTree(A));

	printf("�Ƿ��ǵ�ֵ������:%d\n", isUnivalTree(A));

	printf("�������Ƿ����:%d\n", isSameTree(A, W));

	printf("ԭ������:");
	BinaryLevelOrder(A);
	printf("\n");

	printf("��ת������:");
	BTNode* ret = invertTree(A);
	BinaryLevelOrder(ret);
	printf("\n");

	printf("�Ƿ��ǶԳƶ�����:%d\n", isSymmetric(T));

	printf("�Ƿ���ƽ�������:%d\n", isBalanced(T));
	BinaryTreeDestroy(A);
	A = NULL;
	return 0;
}

//#include <stdio.h>
//#include <stdlib.h>
//
//typedef struct TreeNode
//{
//	struct TreeNode* left;
//	struct TreeNode* right;
//	char data;
//}TreeNode;
//
//TreeNode* CreateTree(char* str, int* pi)
//{
//	if (str[*pi] == '#')//
//	{
//		(*pi)++;
//		return NULL;
//	}
//	//����NULL���������
//	TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
//	root->left = NULL;
//	root->right = NULL;
//	root->data = str[*pi];
//	(*pi)++;
//	//�ݹ鹹��������
//	root->left = CreateTree(str, pi);
//	//�ݹ鹹��������
//	root->right = CreateTree(str, pi);
//	return root;
//}
////�������
//void Inorder(TreeNode* root)
//{
//	if (root == NULL)
//		return;
//	Inorder(root->left);
//	printf("%c ", root->data);
//	Inorder(root->right);
//}
//int main()
//{
//	char str[100];
//	scanf("%s", str);
//	int i = 0;
//	TreeNode* root = CreateTree(str, &i);
//	Inorder(root);
//	return 0;
//}