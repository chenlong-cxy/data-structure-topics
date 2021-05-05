#include "CirQueue.h"

int main()
{
	CirQueue* pq = CirQueueInit();//��ʼ��ѭ������
	//����1��2��3��4
	CirQueuePush(pq, 1);
	CirQueuePush(pq, 2);
	CirQueuePush(pq, 3);
	CirQueuePush(pq, 4);
	printf("����4�����ݺ�ѭ������Ϊ:>");
	CirQueuePrint(pq);
	printf("tag = %d\n", pq->tag);
	//ɾ��3������
	CirQueuePop(pq);
	CirQueuePop(pq);
	CirQueuePop(pq);
	printf("ɾ��3�����ݺ�ѭ������Ϊ:>");
	CirQueuePrint(pq);
	printf("tag = %d\n", pq->tag);

	CirQueuePush(pq, 7);
	CirQueuePush(pq, 8);
	CirQueuePush(pq, 9);
	CirQueuePush(pq, 10);
	CirQueuePush(pq, 11);
	CirQueuePush(pq, 12);
	CirQueuePush(pq, 13);
	CirQueuePush(pq, 14);
	CirQueuePush(pq, 15);
	printf("�ٲ���9�����ݺ�ѭ������Ϊ:>");
	CirQueuePrint(pq);
	printf("tag = %d\n", pq->tag);

	CirQueueDestroy(pq);//����ѭ������
	return 0;
}