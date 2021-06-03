#include <stdio.h>
#include <stdlib.h>

typedef int BTDataType;

typedef struct BTNode
{
	BTDataType data;
	struct BTNode* left;
	struct BTNode* right;
}BTNode;

//插入
BTNode* Insert(BTNode* root, BTDataType x);
//删除
BTNode* Delete(BTNode* root, BTDataType x);

//查找（递归）
BTNode* Find(BTNode* root, BTDataType x);
//查找（非递归）
BTNode* FindNonR(BTNode* root, BTDataType x);

//查找最大元素（递归）
BTNode* FindMax(BTNode* root);
//查找最大元素（非递归）
BTNode* FindMaxNonR(BTNode* root);

//查找最小元素（递归）
BTNode* FindMin(BTNode* root);
//查找最小元素（非递归）
BTNode* FindMinNonR(BTNode* root);

//层序遍历
void BinaryLevelOrder(BTNode* root);