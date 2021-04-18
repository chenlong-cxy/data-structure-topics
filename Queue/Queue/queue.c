#include "queue.h"

//初始化队列
void QueueInit(Queue* pq)
{
	assert(pq);

	pq->head = NULL;
	pq->tail = NULL;
}

//销毁队列
void QueueDestroy(Queue* pq)
{
	assert(pq);

	QListNode* cur = pq->head;
	while (cur)
	{
		QListNode* next = cur->next;
		free(cur);
		cur = next;
	}
	pq->head = NULL;
	pq->tail = NULL;
}

//队尾入队列
void QueuePush(Queue* pq, QDataType x)
{
	assert(pq);

	QListNode* newnode = (QListNode*)malloc(sizeof(QListNode));
	if (newnode == NULL)
	{
		printf("malloc fail\n");
		exit(-1);
	}
	newnode->data = x;
	newnode->next = NULL;
	if (pq->head == NULL)
	{
		pq->head = pq->tail = newnode;
	}
	else
	{
		pq->tail->next = newnode;
		pq->tail = newnode;
	}
}

//队头出队列
void QueuePop(Queue* pq)
{
	assert(pq);
	assert(!QueueEmpty(pq));

	if (pq->head->next == NULL)
	{
		free(pq->head);
		pq->head = NULL;
		pq->tail = NULL;
	}
	else
	{
		QListNode* next = pq->head->next;
		free(pq->head);
		pq->head = next;
	}
}

//获取队列头部元素
QDataType QueueFront(Queue* pq)
{
	assert(pq);
	assert(!QueueEmpty(pq));

	return pq->head->data;
}

//获取队列尾部元素
QDataType QueueBack(Queue* pq)
{
	assert(pq);
	assert(!QueueEmpty(pq));

	return pq->tail->data;
}

//检测队列是否为空
bool QueueEmpty(Queue* pq)
{
	assert(pq);

	return pq->head == NULL;
}

//获取队列中有效元素个数
int QueueSize(Queue* pq)
{
	assert(pq);

	QListNode* cur = pq->head;
	int count = 0;
	while (cur)
	{
		count++;
		cur = cur->next;
	}
	return count;
}