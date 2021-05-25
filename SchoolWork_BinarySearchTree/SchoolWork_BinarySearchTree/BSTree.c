#include "BSTree.h"
#include "queue.h"

//新建一个结点
BTNode* CreateNode(BTDataType x)
{
	BTNode* Node = (BTNode*)malloc(sizeof(BTNode));
	if (Node == NULL)
	{
		printf("malloc fail\n");
		exit(-1);
	}
	Node->data = x;
	Node->left = Node->right = NULL;

	return Node;
}
//插入
BTNode* Insert(BTNode* root, BTDataType x)
{
	if (root == NULL)//空树
	{
		BTNode* newNode = CreateNode(x);
		return newNode;
	}
	else
	{
		if (x < root->data)
		{
			root->left = Insert(root->left, x);
		}
		else if (x>root->data)
		{
			root->right = Insert(root->right, x);
		}
		return root;
	}
}
//删除
void Delet(BTNode* root, BTDataType x)
{

}

//查找（递归）
BTNode* Find(BTNode* root, BTDataType x)
{
	if (root == NULL)
		return NULL;
	if (x > root->data)//右子树找
		return Find(root->right, x);
	else if (x < root->data)//左子树找
		return Find(root->left, x);
	return root;
}

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

////层序遍历
//void BinaryLevelOrder(BTNode* root)
//{
//	Queue q;
//	QueueInit(&q);//初始化队列
//	if (root != NULL)
//		QueuePush(&q, root);
//	while (!QueueEmpty(&q))//当队列不为空时，循环继续
//	{
//		BTNode* front = QueueFront(&q);//读取队头元素
//		QueuePop(&q);//删除队头元素
//		printf("%d ", front->data);//打印出队的元素
//		if (front->left)
//		{
//			QueuePush(&q, front->left);//出队元素的左孩子入队列
//		}
//		if (front->right)
//		{
//			QueuePush(&q, front->right);//出队元素的右孩子入队列
//		}
//	}
//	QueueDestroy(&q);//销毁队列
//}

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
		if (front == NULL)
		{
			printf("NULL ");
		}
		else
		{
			printf("%d ", front->data);//打印出队的元素
		}
		if (front)
		{
			QueuePush(&q, front->left);//出队元素的左孩子入队列
			QueuePush(&q, front->right);//出队元素的右孩子入队列
		}
	}
	QueueDestroy(&q);//销毁队列
}