#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

typedef char ElementType;
typedef struct TreeNode
{
	ElementType data;       // 结点存储的数据类型
	struct TreeNode* left;  // 指向左孩子
	struct TreeNode* right; // 指向右孩子
}TreeNode;

//先序遍历
void PreOrderTree(TreeNode* root);
//中序遍历
void InOrderTree(TreeNode* root);
//后序遍历
void PostOrderTree(TreeNode* root);
//先序创建二叉树
TreeNode* PreCreateTree(char* arr, int* pi);
//二叉树结点个数
int CountNode(TreeNode* root);
//二叉树的高度
int TreeDepth(TreeNode* root);