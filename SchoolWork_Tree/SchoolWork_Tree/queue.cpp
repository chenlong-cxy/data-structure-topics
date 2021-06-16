#include "queue.h"

//��ʼ������
void QueueInit(Queue* pq)
{
	assert(pq);
	//��ʼʱ����Ϊ��
	pq->head = NULL;
	pq->tail = NULL;
}

//���ٶ���
void QueueDestroy(Queue* pq)
{
	assert(pq);

	QListNode* cur = pq->head;//���ն�ͷ
	//������������ͷŽ��
	while (cur)
	{
		QListNode* next = cur->next;
		free(cur);
		cur = next;
	}
	pq->head = NULL;//��ͷ�ÿ�
	pq->tail = NULL;//��β�ÿ�
}

//��β�����
void QueuePush(Queue* pq, QDataType x)
{
	assert(pq);

	QListNode* newnode = (QListNode*)malloc(sizeof(QListNode));//�����½��
	if (newnode == NULL)
	{
		printf("malloc fail\n");
		exit(-1);
	}
	newnode->data = x;//�½�㸳ֵ
	newnode->next = NULL;//�½��ָ�����ÿ�
	if (pq->head == NULL)//������ԭ���޽��
	{
		pq->head = pq->tail = newnode;//��ͷ����βֱ��ָ���½��
	}
	else//������ԭ���н��
	{
		pq->tail->next = newnode;//���һ�����ָ���½��
		pq->tail = newnode;//�ı��βָ��ָ��
	}
}

//��ͷ������
void QueuePop(Queue* pq)
{
	assert(pq);
	assert(!QueueEmpty(pq));//�������Ƿ�Ϊ��

	if (pq->head->next == NULL)//������ֻ��һ�����
	{
		free(pq->head);
		pq->head = NULL;
		pq->tail = NULL;
	}
	else//�������ж�����
	{
		QListNode* next = pq->head->next;
		free(pq->head);
		pq->head = next;//�ı��ͷָ��ָ��
	}
}

//��ȡ����ͷ��Ԫ��
QDataType QueueFront(Queue* pq)
{
	assert(pq);
	assert(!QueueEmpty(pq));//�������Ƿ�Ϊ��

	return pq->head->data;//���ض�ͷָ��ָ�������
}

//��ȡ����β��Ԫ��
QDataType QueueBack(Queue* pq)
{
	assert(pq);
	assert(!QueueEmpty(pq));//�������Ƿ�Ϊ��

	return pq->tail->data;//���ض�βָ��ָ�������
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

	QListNode* cur = pq->head;//���ն�ͷ
	int count = 0;//��¼������
	while (cur)//��������
	{
		count++;
		cur = cur->next;
	}
	return count;//���ض����еĽ����
}