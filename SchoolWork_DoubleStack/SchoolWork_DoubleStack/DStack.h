#pragma once

#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>

typedef int SElemType;

typedef struct
{
	int top[2], bot[2];//栈顶和栈底指针
	SElemType *V;//栈数组
	int m;//栈最大可容纳元素个数
}DblStack;

//双栈初始化
void DblStackInit(DblStack* pds);
//判断栈空
void DblStackEmpty(DblStack* pds);
//判断栈满
bool DblStackFull(DblStack* pds);
//进栈
void DblStackPush(DblStack* pds, int tag, SElemType x);
//出栈
SElemType DblStackPop(DblStack*pds, int tag);
//打印
void DblStackPrint(DblStack* pds);