#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef int ElementType;

typedef struct CirQueue
{
	ElementType* a;//数组模拟环形队列
	int size;//队列可存储的有效数据总数
	int front;//队头
	int tail;//队尾
	int tag;//当tag为1时，队列满
}CirQueue;

//初始化环形队列
CirQueue* CirQueueInit();
//销毁环形队列
void CirQueueDestroy(CirQueue* pq);

//插入
void CirQueuePush(CirQueue* pq, ElementType x);
//删除
void CirQueuePop(CirQueue* pq);
//打印循环队列
void CirQueuePrint(CirQueue* pq);