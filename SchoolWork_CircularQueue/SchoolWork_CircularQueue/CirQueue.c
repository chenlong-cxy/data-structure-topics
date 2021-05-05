#include "CirQueue.h"

//��ʼ�����ζ���
CirQueue* CirQueueInit()
{
	CirQueue* pq;
	CirQueue* tmp1 = (CirQueue*)malloc(sizeof(CirQueue));//��̬���ٽṹ��
	if (tmp1 == NULL)
	{
		printf("malloc fail\n");
		exit(-1);
	}
	pq = tmp1;
	//calloc�������ٿռ䣬�ռ������Զ���Ϊ0
	ElementType* tmp2 = (ElementType*)calloc(sizeof(ElementType), 10);//��̬�������飨ѭ�����У�
	if (tmp2 == NULL)
	{
		printf("malloc fail\n");
		exit(-1);
	}
	pq->a = tmp2;
	pq->size = 10;//���пɴ洢����Ч��������
	pq->front = 0;//��ͷ����±�Ϊ0��λ��
	pq->tail = 0;//��β����±�Ϊ0��λ��
	pq->tag = 0;//��ʼ���в�����tag=0

	return pq;//����ѭ�����нṹ��
}

//���ٻ��ζ���
void CirQueueDestroy(CirQueue* pq)
{
	free(pq->a);//�ͷ�����
	free(pq);//�ͷŽṹ��
}

//����
void CirQueuePush(CirQueue* pq, ElementType x)
{
	if (pq->tag == 1)
	{
		printf("������\n");
		exit(-1);
	}
	pq->a[pq->tail] = x;//��ֵ
	pq->tail = (pq->tail + 1) % pq->size;//��β����
	if (pq->tail == pq->front)//�жϱ��β����Ƿ��¶�����
		pq->tag = 1;
}

//ɾ��
void CirQueuePop(CirQueue*pq)
{
	if (pq->tag == 0 && pq->front == pq->tail)
	{
		printf("���п�\n");
		exit(-1);
	}
	pq->a[pq->front] = 0;//ɾ����λ����0�����ڹ۲�
	pq->front = (pq->front + 1) % pq->size;//��ͷ����
}

//��ӡѭ�����У����ڹ۲죩
void CirQueuePrint(CirQueue* pq)
{
	int i = 0;
	for (i = 0; i < pq->size; i++)
	{
		printf("%d ", pq->a[i]);
	}
	printf("\n");
}