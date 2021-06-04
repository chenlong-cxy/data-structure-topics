#include "BinaryTree.h"

//结点访问
void visit(TreeNode* root) 
{
	printf("%-5c", root->data);
}
//先序遍历
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
//中序遍历
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
//后序遍历
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
//先序创建二叉树
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
//二叉树结点个数
int CountNode(TreeNode* root)
{
	return root == NULL ? 0 : CountNode(root->left) + CountNode(root->right) + 1;
}
//两者的较大值
int Max(int x, int y)
{
	return x > y ? x : y;
}
//二叉树的高度
int TreeDepth(TreeNode* root)
{
	if (root == NULL)
	{
		return 0;
	}
	return Max(TreeDepth(root->left), TreeDepth(root->right)) + 1;
}