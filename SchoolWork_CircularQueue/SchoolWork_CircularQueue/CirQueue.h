#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef int ElementType;

typedef struct CirQueue
{
	ElementType* a;//����ģ�⻷�ζ���
	int size;//���пɴ洢����Ч��������
	int front;//��ͷ
	int tail;//��β
	int tag;//��tagΪ1ʱ��������
}CirQueue;

//��ʼ�����ζ���
CirQueue* CirQueueInit();
//���ٻ��ζ���
void CirQueueDestroy(CirQueue* pq);

//����
void CirQueuePush(CirQueue* pq, ElementType x);
//ɾ��
void CirQueuePop(CirQueue* pq);
//��ӡѭ������
void CirQueuePrint(CirQueue* pq);