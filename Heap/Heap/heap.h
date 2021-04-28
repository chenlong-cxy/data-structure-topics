#pragma once
#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

typedef int HPDataType;//���д洢���ݵ�����

typedef struct Heap
{
	HPDataType* a;//���ڴ洢���ݵ�����
	int size;//��¼��������Ԫ�ظ���
	int capacity;//��¼�ѵ�����
}HP;

//HP* HeapInit(HPDataType* a, int n);

//��ʼ����
void HeapInit(HP* php, HPDataType* a, int n);
//���ٶ�
void HeapDestroy(HP* php);
//��ӡ��
void HeapPrint(HP* php);

//�ѵĲ���
void HeapPush(HP* php, HPDataType x);
//�ѵ�ɾ��
void HeapPop(HP* php);

//��ȡ�Ѷ�������
HPDataType HeapTop(HP* php);
//��ȡ�������ݸ���
int HeapSize(HP* php);
//�ѵ��п�
bool HeapEmpty(HP* php);
