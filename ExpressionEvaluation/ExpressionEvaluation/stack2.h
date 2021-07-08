#pragma once
#define _CRT_SECURE_NO_WARNINGS 1
#define MAX 100
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
typedef double STDataType2;//ջ�д洢��Ԫ������

typedef struct Stack2
{
	STDataType2* a;//ջ
	int top;//ջ��
	int capacity;//��������������
}Stack2;

//��ʼ��ջ
void StackInit2(Stack2* pst);
//����ջ
void StackDestroy2(Stack2* pst);

//��ջ
void StackPush2(Stack2* pst, STDataType2 x);
//��ջ
void StackPop2(Stack2* pst);

//��ȡջ��Ԫ��
STDataType2 StackTop2(Stack2* pst);
//���ջ�Ƿ�Ϊ��
bool StackEmpty2(Stack2* pst);
//��ȡջ����ЧԪ�ظ���
int StackSize2(Stack2* pst);