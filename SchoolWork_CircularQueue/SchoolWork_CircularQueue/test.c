#include "CirQueue.h"

int main()
{
	CirQueue* pq = CirQueueInit();//初始化循环队列
	//插入1，2，3，4
	CirQueuePush(pq, 1);
	CirQueuePush(pq, 2);
	CirQueuePush(pq, 3);
	CirQueuePush(pq, 4);
	printf("插入4个数据后循环队列为:>");
	CirQueuePrint(pq);
	printf("tag = %d\n", pq->tag);
	//删除3个数据
	CirQueuePop(pq);
	CirQueuePop(pq);
	CirQueuePop(pq);
	printf("删除3个数据后循环队列为:>");
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
	printf("再插入9个数据后循环队列为:>");
	CirQueuePrint(pq);
	printf("tag = %d\n", pq->tag);

	CirQueueDestroy(pq);//销毁循环队列
	return 0;
}