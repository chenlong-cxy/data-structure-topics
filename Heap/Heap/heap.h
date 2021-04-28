#pragma once
#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

typedef int HPDataType;//堆中存储数据的类型

typedef struct Heap
{
	HPDataType* a;//用于存储数据的数组
	int size;//记录堆中已有元素个数
	int capacity;//记录堆的容量
}HP;

//HP* HeapInit(HPDataType* a, int n);

//初始化堆
void HeapInit(HP* php, HPDataType* a, int n);
//销毁堆
void HeapDestroy(HP* php);
//打印堆
void HeapPrint(HP* php);

//堆的插入
void HeapPush(HP* php, HPDataType x);
//堆的删除
void HeapPop(HP* php);

//获取堆顶的数据
HPDataType HeapTop(HP* php);
//获取堆中数据个数
int HeapSize(HP* php);
//堆的判空
bool HeapEmpty(HP* php);
