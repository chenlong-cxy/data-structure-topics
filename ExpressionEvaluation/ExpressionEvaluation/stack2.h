#pragma once
#define _CRT_SECURE_NO_WARNINGS 1
#define MAX 100
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
typedef double STDataType2;//栈中存储的元素类型

typedef struct Stack2
{
	STDataType2* a;//栈
	int top;//栈顶
	int capacity;//容量，方便增容
}Stack2;

//初始化栈
void StackInit2(Stack2* pst);
//销毁栈
void StackDestroy2(Stack2* pst);

//入栈
void StackPush2(Stack2* pst, STDataType2 x);
//出栈
void StackPop2(Stack2* pst);

//获取栈顶元素
STDataType2 StackTop2(Stack2* pst);
//检测栈是否为空
bool StackEmpty2(Stack2* pst);
//获取栈中有效元素个数
int StackSize2(Stack2* pst);