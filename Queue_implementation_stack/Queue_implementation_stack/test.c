//�����ʹ����������ʵ��һ�������ȳ���LIFO����ջ��
//��֧����ͨ���е�ȫ�����ֲ�����push��top��pop �� empty����

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

typedef int QDataType;//�����д洢��Ԫ�����ͣ����������;�����

typedef struct QListNode
{
	struct QListNode* next;//ָ����
	QDataType data;//������
}QListNode;

typedef struct Queue
{
	QListNode* head;//��ͷ
	QListNode* tail;//��β
}Queue;
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

//�������Ƿ�Ϊ��
bool QueueEmpty(Queue* pq)
{
	assert(pq);

	return pq->head == NULL;
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

typedef struct {
	Queue q1;//��һ������
	Queue q2;//�ڶ�������
} MyStack;

/** Initialize your data structure here. */

MyStack* myStackCreate() {
	MyStack* pst = (MyStack*)malloc(sizeof(MyStack));//����һ��MyStack���͵�ջ
	QueueInit(&pst->q1);//��ʼ����һ������
	QueueInit(&pst->q2);//��ʼ���ڶ�������

	return pst;
}

/** Push element x onto stack. */
void myStackPush(MyStack* obj, int x) {
	//����ѹ��ǿյ��Ǹ�����
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
	Queue* pEmpty = &obj->q1;//��¼�ն���
	Queue* pNoEmpty = &obj->q2;//��¼�ǿն���
	if (!QueueEmpty(&obj->q1))
	{
		pEmpty = &obj->q2;
		pNoEmpty = &obj->q1;
	}
	while (QueueSize(pNoEmpty) > 1)
	{
		QueuePush(pEmpty, QueueFront(pNoEmpty));
		QueuePop(pNoEmpty);
	}//���ǿն����е�n-1������ȫ���ŵ��ն���
	int front = QueueFront(pNoEmpty);//��ȡĿ������
	QueuePop(pNoEmpty);//ɾ��Ŀ������
	return front;
}

/** Get the top element. */
int myStackTop(MyStack* obj) {
	//��ȡ�ǿն��еĶ�β����
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
	//�������о�Ϊ�գ���MyStackΪ��
	return QueueEmpty(&obj->q1) && QueueEmpty(&obj->q2);
}

void myStackFree(MyStack* obj) {
	QueueDestroy(&obj->q1);//�ͷŵ�һ������
	QueueDestroy(&obj->q2);//�ͷŵڶ�������
	free(obj);//�ͷ�MyStack
}