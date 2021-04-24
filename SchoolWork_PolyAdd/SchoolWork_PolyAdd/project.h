#pragma once
#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef int SLTDataType;

typedef struct SListNode
{
	SLTDataType coef;//系数
	SLTDataType expon;//指数
	struct SListNode* next;//用于存放下一个结点的地址
}SListNode;

//打印链表
void SListPrint(SListNode* plist);

//尾插
void SListPushBack(SListNode** pplist, SLTDataType coef, SLTDataType expon);

SListNode* PolyAdd(SListNode* P1, SListNode* P2);