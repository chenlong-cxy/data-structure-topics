#pragma once

#include <stdio.h>
#include <stdbool.h>

typedef int SElemType;

typedef struct
{
	int top[2], bot[2];//栈顶和栈底指针
	SElemType *V;//栈数组
	int m;//栈最大可容纳元素个数
}DblStack;

//判断栈空
bool DblStackEmpty(DblStack* pds);
//判断栈满
bool DblStackFull(DblStack* pds);
//进栈
bool DblStackPush(DblStack* pds, int tag, SElemType x);
//出栈
SElemType DblStackPop(DblStack*pds, int tag);