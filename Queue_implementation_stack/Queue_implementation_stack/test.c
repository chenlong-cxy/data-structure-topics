//请你仅使用两个队列实现一个后入先出（LIFO）的栈，
//并支持普通队列的全部四种操作（push、top、pop 和 empty）。

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

typedef int QDataType;//队列中存储的元素类型（这里用整型举例）

typedef struct QListNode
{
	struct QListNode* next;//指针域
	QDataType data;//数据域
}QListNode;

typedef struct Queue
{
	QListNode* head;//队头
	QListNode* tail;//队尾
}Queue;
//初始化队列
void QueueInit(Queue* pq)
{
	assert(pq);
	//起始时队列为空
	pq->head = NULL;
	pq->tail = NULL;
}

//销毁队列
void QueueDestroy(Queue* pq)
{
	assert(pq);

	QListNode* cur = pq->head;//接收队头
	//遍历链表，逐个释放结点
	while (cur)
	{
		QListNode* next = cur->next;
		free(cur);
		cur = next;
	}
	pq->head = NULL;//队头置空
	pq->tail = NULL;//队尾置空
}

//队尾入队列
void QueuePush(Queue* pq, QDataType x)
{
	assert(pq);

	QListNode* newnode = (QListNode*)malloc(sizeof(QListNode));//申请新结点
	if (newnode == NULL)
	{
		printf("malloc fail\n");
		exit(-1);
	}
	newnode->data = x;//新结点赋值
	newnode->next = NULL;//新结点指针域置空
	if (pq->head == NULL)//队列中原本无结点
	{
		pq->head = pq->tail = newnode;//队头、队尾直接指向新结点
	}
	else//队列中原本有结点
	{
		pq->tail->next = newnode;//最后一个结点指向新结点
		pq->tail = newnode;//改变队尾指针指向
	}
}

//队头出队列
void QueuePop(Queue* pq)
{
	assert(pq);
	assert(!QueueEmpty(pq));//检测队列是否为空

	if (pq->head->next == NULL)//队列中只有一个结点
	{
		free(pq->head);
		pq->head = NULL;
		pq->tail = NULL;
	}
	else//队列中有多个结点
	{
		QListNode* next = pq->head->next;
		free(pq->head);
		pq->head = next;//改变队头指针指向
	}
}

//检测队列是否为空
bool QueueEmpty(Queue* pq)
{
	assert(pq);

	return pq->head == NULL;
}

//获取队列头部元素
QDataType QueueFront(Queue* pq)
{
	assert(pq);
	assert(!QueueEmpty(pq));//检测队列是否为空

	return pq->head->data;//返回队头指针指向的数据
}

//获取队列尾部元素
QDataType QueueBack(Queue* pq)
{
	assert(pq);
	assert(!QueueEmpty(pq));//检测队列是否为空

	return pq->tail->data;//返回队尾指针指向的数据
}

//获取队列中有效元素个数
int QueueSize(Queue* pq)
{
	assert(pq);

	QListNode* cur = pq->head;//接收队头
	int count = 0;//记录结点个数
	while (cur)//遍历队列
	{
		count++;
		cur = cur->next;
	}
	return count;//返回队列中的结点数
}

typedef struct {
	Queue q1;//第一个队列
	Queue q2;//第二个队列
} MyStack;

/** Initialize your data structure here. */

MyStack* myStackCreate() {
	MyStack* pst = (MyStack*)malloc(sizeof(MyStack));//申请一个MyStack类型的栈
	QueueInit(&pst->q1);//初始化第一个队列
	QueueInit(&pst->q2);//初始化第二个队列

	return pst;
}

/** Push element x onto stack. */
void myStackPush(MyStack* obj, int x) {
	//数据压入非空的那个队列
	if (!QueueEmpty(&obj->q1))
	{
		QueuePush(&obj->q1, x);
	}
	else
	{
		QueuePush(&obj->q2, x);
	}
}

/** Removes the element on top of the stack and returns that element. */
int myStackPop(MyStack* obj) {
	Queue* pEmpty = &obj->q1;//记录空队列
	Queue* pNoEmpty = &obj->q2;//记录非空队列
	if (!QueueEmpty(&obj->q1))
	{
		pEmpty = &obj->q2;
		pNoEmpty = &obj->q1;
	}
	while (QueueSize(pNoEmpty) > 1)
	{
		QueuePush(pEmpty, QueueFront(pNoEmpty));
		QueuePop(pNoEmpty);
	}//将非空队列中的n-1个数据全部放到空队列
	int front = QueueFront(pNoEmpty);//获取目标数据
	QueuePop(pNoEmpty);//删除目标数据
	return front;
}

/** Get the top element. */
int myStackTop(MyStack* obj) {
	//获取非空队列的队尾数据
	if (!QueueEmpty(&obj->q1))
	{
		return QueueBack(&obj->q1);
	}
	else
	{
		return QueueBack(&obj->q2);
	}
}

/** Returns whether the stack is empty. */
bool myStackEmpty(MyStack* obj) {
	//两个队列均为空，则MyStack为空
	return QueueEmpty(&obj->q1) && QueueEmpty(&obj->q2);
}

void myStackFree(MyStack* obj) {
	QueueDestroy(&obj->q1);//释放第一个队列
	QueueDestroy(&obj->q2);//释放第二个队列
	free(obj);//释放MyStack
}