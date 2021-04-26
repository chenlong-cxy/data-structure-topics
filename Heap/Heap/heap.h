#pragma once
#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>

typedef int HPDataType;

typedef struct Heap
{
	HPDataType* a;
	int size;
	int capacity;
}HP;

//HP* HeapInit(HPDataType* a, int n);

//��ʼ����
void HeapInit(HP* php, HPDataType* a, int n);
//���ٶ�
void HeapDestroy(HP* php);
//��ӡ��
void HeapPrint(HP* php);

//����в���Ԫ��
void HeapPush(HP* php, HPDataType x);
//ɾ���Ѷ�Ԫ��
void HeapPop(HP* php);

//��ȡ�Ѷ�Ԫ��
HPDataType HeapTop(HP* php);
//��ȡ����Ԫ�ظ���
int HeapSize(HP* php);
//�ж϶��Ƿ�Ϊ��
bool HeapEmpty(HP* php);
