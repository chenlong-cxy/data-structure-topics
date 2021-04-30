#pragma once

#include <stdio.h>
#include <stdbool.h>

typedef int SElemType;

typedef struct
{
	int top[2], bot[2];//ջ����ջ��ָ��
	SElemType *V;//ջ����
	int m;//ջ��������Ԫ�ظ���
}DblStack;

//�ж�ջ��
bool DblStackEmpty(DblStack* pds);
//�ж�ջ��
bool DblStackFull(DblStack* pds);
//��ջ
bool DblStackPush(DblStack* pds, int tag, SElemType x);
//��ջ
SElemType DblStackPop(DblStack*pds, int tag);