#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

//前置声明
struct BTNode;

typedef struct BTNode* QDataType;//队列中存储的元素类型

typedef struct QListNode
{
	struct QListNode* next;//指针域
	QDataType data;//数据域
}QListNode;

typedef struct Queue
{
	QListNode* head;//队头
	QListNode* tail;//队尾
}Queue;

//初始化队列
void QueueInit(Queue* pq);
//销毁队列
void QueueDestroy(Queue* pq);

//队尾入队列
void QueuePush(Queue* pq, QDataType x);
//队头出队列
void QueuePop(Queue* pq);

//获取队列头部元素
QDataType QueueFront(Queue* pq);
//获取队列尾部元素
QDataType QueueBack(Queue* pq);

//检测队列是否为空
bool QueueEmpty(Queue* pq);
//获取队列中有效元素个数
int QueueSize(Queue* pq);