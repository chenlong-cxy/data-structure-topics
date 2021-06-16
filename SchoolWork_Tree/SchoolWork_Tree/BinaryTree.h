#pragma once

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

//深度优先
//前序遍历
void BinaryPrevOrder(BTNode* root);
//中序遍历
void BinaryInOrder(BTNode* root);
//后序遍历
void BinaryPostOrder(BTNode* root);
//广度优先
//层序遍历
void BinaryLevelOrder(BTNode* root);

//结点的个数
int BinaryTreeSize(BTNode* root);
//叶子结点的个数
int BinaryTreeLeafSize(BTNode* root);
//第k层结点的个数
int BinaryTreeKLevelSize(BTNode* root, int k);

//查找值为x的结点
BTNode* BinaryTreeFind(BTNode* root, BTDataType x);
//树的最大深度
int BinaryTreeMaxDepth(BTNode* root);

//二叉树销毁
void BinaryTreeDestroy(BTNode* root);
//void BinaryTreeDestroy(BTNode** root);
//void BinaryTreeDestroy(BTNode*& root);//取别名

//判断二叉树是否是完全二叉树
bool isCompleteTree(BTNode* root);
//判断二叉树是否是单值二叉树
bool isUnivalTree(BTNode* root);
//判断两棵二叉树是否相同
bool isSameTree(BTNode* p, BTNode* q);
//判断二叉树是否是平衡二叉树
bool isBalanced(BTNode* root);

//前序遍历
int* preorderTraversal(BTNode* root, int* returnSize);
//中序遍历
int* inorderTraversal(BTNode* root, int* returnSize);
//后序遍历
int* postorderTraversal(BTNode* root, int* returnSize);

//翻转二叉树
BTNode* invertTree(BTNode* root);
//对称二叉树
bool isSymmetric(BTNode* root);
//另一个树的子树
bool isSubtree(BTNode* root, BTNode* subRoot);