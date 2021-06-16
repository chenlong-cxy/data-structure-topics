#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

//ǰ������
struct BTNode;

typedef struct BTNode* QDataType;//�����д洢��Ԫ������

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
void QueueInit(Queue* pq);
//���ٶ���
void QueueDestroy(Queue* pq);

//��β�����
void QueuePush(Queue* pq, QDataType x);
//��ͷ������
void QueuePop(Queue* pq);

//��ȡ����ͷ��Ԫ��
QDataType QueueFront(Queue* pq);
//��ȡ����β��Ԫ��
QDataType QueueBack(Queue* pq);

//�������Ƿ�Ϊ��
bool QueueEmpty(Queue* pq);
//��ȡ��������ЧԪ�ظ���
int QueueSize(Queue* pq);