#include "queue.h"

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

	QListNode* cur = pq->head;//接收队头
	int count = 0;//记录结点个数
	while (cur)//遍历队列
	{
		count++;
		cur = cur->next;
	}
	return count;//返回队列中的结点数
}