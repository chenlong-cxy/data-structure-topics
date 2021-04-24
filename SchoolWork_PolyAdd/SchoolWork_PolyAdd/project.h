#pragma once
#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef int SLTDataType;//ָ����ϵ������

typedef struct SListNode
{
	SLTDataType coef;//ϵ��
	SLTDataType expon;//ָ��
	struct SListNode* next;//���ڴ����һ�����ĵ�ַ
}SListNode;

//��ӡ����ʽ
void SListPrint(SListNode* head);
//����һ���½�㣬�����½���ַ
SListNode* BuySLTNode(SLTDataType coef, SLTDataType expon);
//β��
void SListPushBack(SListNode** pHead, SLTDataType coef, SLTDataType expon);
//ѡ������
SListNode* InsertSortList(SListNode* head);
//�Ƚ���������ָ����С
int Compare(SLTDataType e1, SLTDataType e2);
//����ʽ���
SListNode* PolyAdd(SListNode* P1, SListNode* P2);