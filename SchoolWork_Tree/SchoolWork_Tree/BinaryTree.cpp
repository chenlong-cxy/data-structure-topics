#include "BinaryTree.h"
#include "queue.h"

//深度优先
//前序遍历
void BinaryPrevOrder(BTNode* root)
{
	if (root == NULL)
	{
		printf("NULL ");
		return;
	}
	//根->左子树->右子树
	printf("%c ", root->data);
	BinaryPrevOrder(root->left);
	BinaryPrevOrder(root->right);
}

//中序遍历
void BinaryInOrder(BTNode* root)
{
	if (root == NULL)
	{
		printf("NULL ");
		return;
	}
	//左子树->根->右子树
	BinaryInOrder(root->left);
	printf("%c ", root->data);
	BinaryInOrder(root->right);
}

//后序遍历
void BinaryPostOrder(BTNode* root)
{
	if (root == NULL)
	{
		printf("NULL ");
		return;
	}
	//左子树->右子树->根
	BinaryPostOrder(root->left);
	BinaryPostOrder(root->right);
	printf("%c ", root->data);
}

//广度优先
//层序遍历
void BinaryLevelOrder(BTNode* root)
{
	Queue q;
	QueueInit(&q);//初始化队列
	if (root != NULL)
		QueuePush(&q, root);
	while (!QueueEmpty(&q))//当队列不为空时，循环继续
	{
		BTNode* front = QueueFront(&q);//读取队头元素
		QueuePop(&q);//删除队头元素
		printf("%c ", front->data);//打印出队的元素
		if (front->left)
		{
			QueuePush(&q, front->left);//出队元素的左孩子入队列
		}
		if (front->right)
		{
			QueuePush(&q, front->right);//出队元素的右孩子入队列
		}
	}
	QueueDestroy(&q);//销毁队列
}

//结点的个数
int BinaryTreeSize(BTNode* root)
{
	//if (root == NULL)
	//{
	//	return 0;
	//}
	//return BinaryTreeSize(root->left) + BinaryTreeSize(root->right) + 1;
	
	//结点个数 = 左子树的结点个数 + 右子树的结点个数 + 自己
	return root == NULL ? 0 : BinaryTreeSize(root->left) + BinaryTreeSize(root->right) + 1;
}

//叶子结点的个数
int BinaryTreeLeafSize(BTNode* root)
{
	if (root == NULL)//空树无叶子结点
		return 0;
	if (root->left == NULL&&root->right == NULL)//是叶子结点
		return 1;
	//叶子结点的个数 = 左子树的叶子结点个数 + 右子树的叶子结点个数
	return BinaryTreeLeafSize(root->left) + BinaryTreeLeafSize(root->right);
}

//第k层结点的个数
int BinaryTreeKLevelSize(BTNode* root, int k)
{
	if (k < 1 || root == NULL)//空树或输入k值不合法
		return 0;
	if (k == 1)//第一层结点个数
		return 1;
	//相对于父结点的第k层的结点个数 = 相对于两个孩子结点的第k-1层的结点个数之和
	return BinaryTreeKLevelSize(root->left, k - 1) + BinaryTreeKLevelSize(root->right, k - 1);
}

//查找值为x的结点
BTNode* BinaryTreeFind(BTNode* root, BTDataType x)
{
	if (root == NULL)//空树
		return NULL;
	if (root->data == x)//在根结点处找
		return root;
	BTNode* lret = BinaryTreeFind(root->left, x);//在左子树中找
	if (lret)
		return lret;
	BTNode* rret = BinaryTreeFind(root->right, x);//在右子树中找
	if (rret)
		return rret;
	return NULL;//根结点和左右子树中均没有找到
}

//求较大值
int Max(int a, int b)
{
	return a > b ? a : b;
}
//树的最大深度
int BinaryTreeMaxDepth(BTNode* root)
{
	if (root == NULL)//空树，深度为0
		return 0;
	//树的最大深度 = 左右子树中深度较大的值 + 1
	return Max(BinaryTreeMaxDepth(root->left), BinaryTreeMaxDepth(root->right)) + 1;
}

//二叉树销毁
void BinaryTreeDestroy(BTNode* root)
{
	if (root == NULL)
		return;

	BinaryTreeDestroy(root->left);//销毁左子树
	BinaryTreeDestroy(root->right);//销毁右子树
	free(root);//释放根结点
}

//void BinaryTreeDestroy(BTNode** root)
//{
//	if (*root == NULL)
//		return;
//
//	BinaryTreeDestroy(&(*root)->left);
//	BinaryTreeDestroy(&(*root)->right);
//	free(*root);
//	*root = NULL;
//}

//void BinaryTreeDestroy(BTNode*& root)//取别名
//{
//	if (root == NULL)
//		return;
//
//	BinaryTreeDestroy(root->left);
//	BinaryTreeDestroy(root->right);
//	free(root);
//	root = NULL;
//}

//判断二叉树是否是完全二叉树
bool isCompleteTree(BTNode* root)
{
	Queue q;
	QueueInit(&q);//初始化队列
	if (root != NULL)
		QueuePush(&q, root);
	while (!QueueEmpty(&q))//当队列不为空时，循环继续
	{
		BTNode* front = QueueFront(&q);//读取队头元素
		QueuePop(&q);//删除队头元素
		if (front == NULL)//当读取到空指针时，停止入队操作
			break;
		QueuePush(&q, front->left);//出队元素的左孩子入队列
		QueuePush(&q, front->right);//出队元素的右孩子入队列
	}
	while (!QueueEmpty(&q))//读取队列中剩余的数据
	{
		BTNode* front = QueueFront(&q);
		QueuePop(&q);
		if (front != NULL)//若队列中存在非空指针，则不是完全二叉树
		{
			QueueDestroy(&q);//销毁队列
			return false;
		}
	}
	QueueDestroy(&q);//销毁队列
	return true;//若队列中全是空指针，则是完全二叉树
}

//判断二叉树是否是单值二叉树
bool isUnivalTree(BTNode* root)
{
	if (root == NULL)//根为空，是单值二叉树
		return true;
	if (root->left && root->left->data != root->data)//左孩子存在，但左孩子的值不等于根的值
		return false;
	if (root->right && root->right->data != root->data)//右孩子存在，但右孩子的值不等于根的值
		return false;
	return isUnivalTree(root->left) && isUnivalTree(root->right);//左子树是单值二叉树并且右子树是单值二叉树
}

//判断两棵二叉树是否相同
bool isSameTree(BTNode* p, BTNode* q)
{
	if (p == NULL&&q == NULL)//两棵树均为空，则相同
		return true;
	if (p == NULL || q == NULL)//两棵树中只有一棵树为空，则不相同
		return false;
	if (p->data != q->data)//两棵树根的值不同，则不相同
		return false;
	return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);//两棵树的左子树相同并且右子树相同，则这两棵树相同
}

//求树的结点个数
int TreeSize(BTNode* root)
{
	return root == NULL ? 0 : TreeSize(root->left) + TreeSize(root->right) + 1;
}
//将树中结点的值放入数组
void preorder(BTNode* root, int* arr, int* pi)
{
	if (root == NULL)//根结点为空，直接返回
		return;
	arr[(*pi)++] = root->data;//先将根结点的值放入数组
	//printf("%d ",root->val);
	preorder(root->left, arr, pi);//再将左子树中结点的值放入数组
	preorder(root->right, arr, pi);//最后将右子树中结点的值放入数组
}
//前序遍历
int* preorderTraversal(BTNode* root, int* returnSize)
{
	*returnSize = TreeSize(root);//值的个数等于结点的个数
	int* arr = (int*)malloc(sizeof(int)*(*returnSize));
	int i = 0;
	preorder(root, arr, &i);//将树中结点的值放入数组
	return arr;
}

////求树的结点个数
//int TreeSize(BTNode* root)
//{
//	return root == NULL ? 0 : TreeSize(root->left) + TreeSize(root->right) + 1;
//}
//将树中结点的值放入数组
void inorder(BTNode* root, int* arr, int* pi)
{
	if (root == NULL)//根结点为空，直接返回
		return;
	inorder(root->left, arr, pi);//先将左子树中结点的值放入数组
	arr[(*pi)++] = root->data;//再将根结点的值放入数组
	inorder(root->right, arr, pi);//最后将右子树中结点的值放入数组
}
//中序遍历
int* inorderTraversal(BTNode* root, int* returnSize)
{
	*returnSize = TreeSize(root);//值的个数等于结点的个数
	int* arr = (int*)malloc(sizeof(int)*(*returnSize));
	int i = 0;
	preorder(root, arr, &i);//将树中结点的值放入数组
	return arr;
}

////求树的结点个数
//int TreeSize(BTNode* root)
//{
//	return root == NULL ? 0 : TreeSize(root->left) + TreeSize(root->right) + 1;
//}
//将树中结点的值放入数组
void postorder(BTNode* root, int* arr, int* pi)
{
	if (root == NULL)//根结点为空，直接返回
		return;
	postorder(root->left, arr, pi);//先将左子树中结点的值放入数组
	postorder(root->right, arr, pi);//再将右子树中结点的值放入数组
	arr[(*pi)++] = root->data;//最后将根结点的值放入数组
}
//后序遍历
int* postorderTraversal(BTNode* root, int* returnSize)
{
	*returnSize = TreeSize(root);//值的个数等于结点的个数
	int* arr = (int*)malloc(sizeof(int)*(*returnSize));
	int i = 0;
	preorder(root, arr, &i);//将树中结点的值放入数组
	return arr;
}

//翻转二叉树
BTNode* invertTree(BTNode* root)
{
	if (root == NULL)//根为空，直接返回
		return NULL;
	BTNode* left = invertTree(root->left);//翻转左子树
	BTNode* right = invertTree(root->right);//翻转右子树
	//左右子树位置交换
	root->left = right;
	root->right = left;
	return root;
}

//判断对称位置是否存在且相等
bool travel(BTNode* left, BTNode* right)
{
	if (left == NULL&&right == NULL)//遍历到叶子结点都相同，是对称二叉树
		return true;
	if (left == NULL || right == NULL)//左右对应的指针一个存在一个不存在，不是对称二叉树
		return false;
	if (left->data != right->data)//左右对应结点的值不同，不是对称二叉树
		return false;
	//先一直往左子树遍历，再一直往右子树遍历，若都相同，则是对称二叉树
	return travel(left->left, right->right) && travel(left->right, right->left);
}
//对称二叉树
bool isSymmetric(BTNode* root)
{
	if (root == NULL)//空树是对称二叉树
		return true;
	return travel(root->left, root->right);//判断对称位置是否存在且相等
}

//比较以root和subRoot为根结点的两棵树是否相等
bool Compare(BTNode* root, BTNode* subRoot)
{
	if (root == NULL&&subRoot == NULL)//均为空树，相等
		return true;
	if (root == NULL || subRoot == NULL)//一个为空另一个不为空，不相等
		return false;
	if (root->data != subRoot->data)//结点的值不同，不相等
		return false;
	//比较两棵树的子结点
	return Compare(root->left, subRoot->left) && Compare(root->right, subRoot->right);
}
//另一个树的子树
bool isSubtree(BTNode* root, BTNode* subRoot)
{
	if (root == NULL)//第一棵树遍历完，没有找到与第二棵树相同的子树
		return false;
	if (Compare(root, subRoot))//以root和subRoot为根，开始比较两棵树是否相同
		return true;
	//判断root的左子树或右子树中是否有某一棵子树与subRoot相同
	return isSubtree(root->left, subRoot) || isSubtree(root->right,subRoot);
}

//判断二叉树是否是平衡二叉树
bool isBalanced(BTNode* root)
{
	if (root == NULL)//空树是平衡二叉树
		return true;

	int leftDepth = BinaryTreeMaxDepth(root->left);//求左子树的深度
	int rightDepth = BinaryTreeMaxDepth(root->right);//求右子树的深度
	//左右子树高度差的绝对值不超过1 && 其左子树是平衡二叉树 && 其右子树是平衡二叉树
	return abs(leftDepth - rightDepth) < 2 && isBalanced(root->left) && isBalanced(root->right);
}


bool _isBalanced(BTNode* root, int* ph)
{
	if (root == NULL)//空树是平衡二叉树
	{
		*ph = 0;//空树返回高度为0
		return true;
	}
	//先判断左子树
	int leftHight = 0;
	if (_isBalanced(root->left, &leftHight) == false)
		return false;
	//再判断右子树
	int rightHight = 0;
	if (_isBalanced(root->right, &rightHight) == false)
		return false;
	//把左右子树的高度中的较大值+1作为当前树的高度返回给上一层
	*ph = Max(leftHight, rightHight) + 1;

	return abs(leftHight - rightHight) < 2;//平衡二叉树的条件
}
//判断二叉树是否是平衡二叉树
bool isBalanced(BTNode* root)
{
	int hight = 0;
	return _isBalanced(root, &hight);
}


//#include <stdio.h>
//#include <stdlib.h>
//
//typedef struct TreeNode
//{
//    struct TreeNode* left;
//    struct TreeNode* right;
//    char data;
//}TreeNode;
//
//TreeNode* CreateTree(char* str, int* pi)
//{
//    if(str[*pi] == '#')//
//    {
//        (*pi)++;
//        return NULL;
//    }
//    //不是NULL，构建结点
//    TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
//    root->left = NULL;
//    root->right = NULL;
//    root->data = str[*pi];
//    (*pi)++;
//    //递归构建左子树
//    root->left = CreateTree(str, pi);
//    //递归构建右子树
//    root->right = CreateTree(str, pi);
//    return root;
//}
////中序遍历
//void Inorder(TreeNode* root)
//{
//    if(root == NULL)
//        return;
//    Inorder(root->left);
//    printf("%c ", root->data);
//    Inorder(root->right);
//}
//int main()
//{
//    char str[100];
//    scanf("%s", str);
//    int i = 0;
//    TreeNode* root = CreateTree(str, &i);
//    Inorder(root);
//    return 0;
//}