#include "queue.h"

//��ʼ������
void QueueInit(Queue* pq)
{
	assert(pq);

	pq->head = NULL;
	pq->tail = NULL;
}

//���ٶ���
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

//��β�����
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

//��ͷ������
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

//��ȡ����ͷ��Ԫ��
QDataType QueueFront(Queue* pq)
{
	assert(pq);
	assert(!QueueEmpty(pq));

	return pq->head->data;
}

//��ȡ����β��Ԫ��
QDataType QueueBack(Queue* pq)
{
	assert(pq);
	assert(!QueueEmpty(pq));

	return pq->tail->data;
}

//�������Ƿ�Ϊ��
bool QueueEmpty(Queue* pq)
{
	assert(pq);

	return pq->head == NULL;
}

//��ȡ��������ЧԪ�ظ���
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