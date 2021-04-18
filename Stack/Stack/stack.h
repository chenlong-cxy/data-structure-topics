#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

typedef int STDataType;//ջ�д洢��Ԫ�����ͣ����������;�����

typedef struct Stack
{
	STDataType* a;//ջ
	int top;//ջ��
	int capacity;//��������������
}Stack;

//��ʼ��ջ
void StackInit(Stack* pst);
//����ջ
void StackDestroy(Stack* pst);

//��ջ
void StackPush(Stack* pst, STDataType x);
//��ջ
void StackPop(Stack* pst);

//��ȡջ��Ԫ��
STDataType StackTop(Stack* pst);
//���ջ�Ƿ�Ϊ��
bool StackEmpty(Stack* pst);
//��ȡջ����ЧԪ�ظ���
int StackSize(Stack* pst);