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
	//相同二叉树
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
	//对称二叉树
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
	//判断平衡二叉树
	T->left = O;
	O->left = P;
	P->left = Q;
	Q->left = R;

	printf("前序遍历:");
	BinaryPrevOrder(A);
	printf("\n");

	printf("中序遍历:");
	BinaryInOrder(A);
	printf("\n");

	printf("后序遍历:");
	BinaryPostOrder(A);
	printf("\n");

	printf("结点的个数:%d\n", BinaryTreeSize(A));

	printf("叶子结点的个数:%d\n", BinaryTreeLeafSize(A));

	printf("第%d层结点的个数:%d\n", 3, BinaryTreeKLevelSize(A, 3));

	printf("值为%c的结点地址:%p\n", 'E', BinaryTreeFind(A, 'E'));
	printf("值为%c的结点地址:%p\n", 'G', BinaryTreeFind(A, 'G'));

	printf("最大深度:%d\n", BinaryTreeMaxDepth(A));

	printf("层序遍历:");
	BinaryLevelOrder(A);
	printf("\n");

	printf("是否是完全二叉树:%d\n", isCompleteTree(A));

	printf("是否是单值二叉树:%d\n", isUnivalTree(A));

	printf("两棵树是否相等:%d\n", isSameTree(A, W));

	printf("原二叉树:");
	BinaryLevelOrder(A);
	printf("\n");

	printf("翻转二叉树:");
	BTNode* ret = invertTree(A);
	BinaryLevelOrder(ret);
	printf("\n");

	printf("是否是对称二叉树:%d\n", isSymmetric(T));

	printf("是否是平衡二叉树:%d\n", isBalanced(T));
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
//	//不是NULL，构建结点
//	TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
//	root->left = NULL;
//	root->right = NULL;
//	root->data = str[*pi];
//	(*pi)++;
//	//递归构建左子树
//	root->left = CreateTree(str, pi);
//	//递归构建右子树
//	root->right = CreateTree(str, pi);
//	return root;
//}
////中序遍历
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