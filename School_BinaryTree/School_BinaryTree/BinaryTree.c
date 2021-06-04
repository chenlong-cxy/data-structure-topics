#include "BinaryTree.h"

//������
void visit(TreeNode* root) 
{
	printf("%-5c", root->data);
}
//�������
void PreOrderTree(TreeNode* root)
{
	if (root == NULL)
		return;
	else
	{
		visit(root);
		PreOrderTree(root->left);
		PreOrderTree(root->right);
	}
}
//�������
void InOrderTree(TreeNode* root) 
{
	if (root == NULL)
		return;
	else 
	{
		InOrderTree(root->left);
		visit(root);
		InOrderTree(root->right);
	}
}
//�������
void PostOrderTree(TreeNode* root)
{
	if (root == NULL)
		return;
	else
	{
		PostOrderTree(root->left);
		PostOrderTree(root->right);
		visit(root);
	}
}
//���򴴽�������
TreeNode* PreCreateTree(char* arr, int* pi)
{
	if (arr[*pi] == '#')
	{
		(*pi)++;
		return NULL;
	}
	TreeNode* root = malloc(sizeof(TreeNode));
	if (root == NULL)
	{
		printf("malloc fail\n");
		exit(-1);
	}
	root->data = arr[(*pi)++];
	//root->left = root->right = NULL;
	root->left = PreCreateTree(arr, pi);
	root->right = PreCreateTree(arr, pi);
	return root;
}
//������������
int CountNode(TreeNode* root)
{
	return root == NULL ? 0 : CountNode(root->left) + CountNode(root->right) + 1;
}
//���ߵĽϴ�ֵ
int Max(int x, int y)
{
	return x > y ? x : y;
}
//�������ĸ߶�
int TreeDepth(TreeNode* root)
{
	if (root == NULL)
	{
		return 0;
	}
	return Max(TreeDepth(root->left), TreeDepth(root->right)) + 1;
}