#pragma once

#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>

typedef int SElemType;

typedef struct
{
	int top[2], bot[2];//ջ����ջ��ָ��
	SElemType *V;//ջ����
	int m;//ջ��������Ԫ�ظ���
}DblStack;

//˫ջ��ʼ��
void DblStackInit(DblStack* pds);
//�ж�ջ��
void DblStackEmpty(DblStack* pds);
//�ж�ջ��
bool DblStackFull(DblStack* pds);
//��ջ
void DblStackPush(DblStack* pds, int tag, SElemType x);
//��ջ
SElemType DblStackPop(DblStack*pds, int tag);
//��ӡ
void DblStackPrint(DblStack* pds);