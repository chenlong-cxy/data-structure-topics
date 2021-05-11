#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef int SLTDataType;

typedef struct SListNode
{
	SLTDataType data;//���������ڴ洢�ý�������
	struct SListNode* next;//ָ�������ڴ����һ�����ĵ�ַ
}SListNode;

//��ӡ����
void SListPrint(SListNode* plist);

//ͷ��
void SListPushFront(SListNode** pplist, SLTDataType x);
//β��
void SListPushBack(SListNode** pplist, SLTDataType x);
//�ڸ���λ��֮�����
void SListInsertAfter(SListNode* pos, SLTDataType x);
//�ڸ���λ��֮ǰ����
void SListInsertBefore(SListNode** pplist, SListNode* pos, SLTDataType x);

//ͷɾ
void SListPopFront(SListNode** pplist);
//βɾ
void SListPopBack(SListNode** pplist);
//ɾ������λ��֮���ֵ
void SListErasetAfter(SListNode* pos);
//ɾ������λ�õ�ֵ
void SListErasetCur(SListNode** pplist, SListNode* pos);

//��������
SListNode* SListFind(SListNode* plist, SLTDataType x);
//�޸�����
void SListModify(SListNode* pos, SLTDataType x);