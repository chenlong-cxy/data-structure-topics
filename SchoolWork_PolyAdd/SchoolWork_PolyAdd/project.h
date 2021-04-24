#pragma once
#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef int SLTDataType;

typedef struct SListNode
{
	SLTDataType coef;//ϵ��
	SLTDataType expon;//ָ��
	struct SListNode* next;//���ڴ����һ�����ĵ�ַ
}SListNode;

//��ӡ����
void SListPrint(SListNode* plist);

//β��
void SListPushBack(SListNode** pplist, SLTDataType coef, SLTDataType expon);

SListNode* PolyAdd(SListNode* P1, SListNode* P2);