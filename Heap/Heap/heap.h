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

//初始化堆
void HeapInit(HP* php, HPDataType* a, int n);
//销毁堆
void HeapDestroy(HP* php);
//打印堆
void HeapPrint(HP* php);

//向堆中插入元素
void HeapPush(HP* php, HPDataType x);
//删除堆顶元素
void HeapPop(HP* php);

//获取堆顶元素
HPDataType HeapTop(HP* php);
//获取堆中元素个数
int HeapSize(HP* php);
//判断堆是否为空
bool HeapEmpty(HP* php);
