#include "CirQueue.h"

//初始化环形队列
CirQueue* CirQueueInit()
{
	CirQueue* pq;
	CirQueue* tmp1 = (CirQueue*)malloc(sizeof(CirQueue));//动态开辟结构体
	if (tmp1 == NULL)
	{
		printf("malloc fail\n");
		exit(-1);
	}
	pq = tmp1;
	//calloc函数开辟空间，空间内容自动置为0
	ElementType* tmp2 = (ElementType*)calloc(sizeof(ElementType), 10);//动态开辟数组（循环队列）
	if (tmp2 == NULL)
	{
		printf("malloc fail\n");
		exit(-1);
	}
	pq->a = tmp2;
	pq->size = 10;//队列可存储的有效数据总数
	pq->front = 0;//队头标记下标为0的位置
	pq->tail = 0;//队尾标记下标为0的位置
	pq->tag = 0;//初始队列不满，tag=0

	return pq;//返回循环队列结构体
}

//销毁环形队列
void CirQueueDestroy(CirQueue* pq)
{
	free(pq->a);//释放数组
	free(pq);//释放结构体
}

//插入
void CirQueuePush(CirQueue* pq, ElementType x)
{
	if (pq->tag == 1)
	{
		printf("队列满\n");
		exit(-1);
	}
	pq->a[pq->tail] = x;//赋值
	pq->tail = (pq->tail + 1) % pq->size;//队尾后移
	if (pq->tail == pq->front)//判断本次插入是否导致队列满
		pq->tag = 1;
}

//删除
void CirQueuePop(CirQueue*pq)
{
	if (pq->tag == 0 && pq->front == pq->tail)
	{
		printf("队列空\n");
		exit(-1);
	}
	pq->a[pq->front] = 0;//删除的位置置0，便于观察
	pq->front = (pq->front + 1) % pq->size;//队头后移
}

//打印循环队列（便于观察）
void CirQueuePrint(CirQueue* pq)
{
	int i = 0;
	for (i = 0; i < pq->size; i++)
	{
		printf("%d ", pq->a[i]);
	}
	printf("\n");
}