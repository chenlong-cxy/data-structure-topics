#pragma once
#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef int SLTDataType;//指数、系数类型

typedef struct SListNode
{
	SLTDataType coef;//系数
	SLTDataType expon;//指数
	struct SListNode* next;//用于存放下一个结点的地址
}SListNode;

//打印多项式
void SListPrint(SListNode* head);
//创建一个新结点，返回新结点地址
SListNode* BuySLTNode(SLTDataType coef, SLTDataType expon);
//尾插
void SListPushBack(SListNode** pHead, SLTDataType coef, SLTDataType expon);
//选择排序
SListNode* InsertSortList(SListNode* head);
//比较两个结点的指数大小
int Compare(SLTDataType e1, SLTDataType e2);
//多项式相加
SListNode* PolyAdd(SListNode* P1, SListNode* P2);