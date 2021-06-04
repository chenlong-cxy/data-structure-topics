#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

typedef char ElementType;
typedef struct TreeNode
{
	ElementType data;       // ���洢����������
	struct TreeNode* left;  // ָ������
	struct TreeNode* right; // ָ���Һ���
}TreeNode;

//�������
void PreOrderTree(TreeNode* root);
//�������
void InOrderTree(TreeNode* root);
//�������
void PostOrderTree(TreeNode* root);
//���򴴽�������
TreeNode* PreCreateTree(char* arr, int* pi);
//������������
int CountNode(TreeNode* root);
//�������ĸ߶�
int TreeDepth(TreeNode* root);