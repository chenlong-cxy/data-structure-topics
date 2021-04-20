//设计你的循环队列实现。 
//循环队列是一种线性数据结构，其操作表现基于 FIFO（先进先出）原则
//并且队尾被连接在队首之后以形成一个循环。它也被称为“环形缓冲器”。

//循环队列的一个好处是我们可以利用这个队列之前用过的空间。
//在一个普通队列里，一旦一个队列满了，我们就不能插入下一个元素，即使在队列前面仍有空间。
//但是使用循环队列，我们能使用这些空间去存储新的值。

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
	int* a;//数组模拟环形队列
	int k;//队列可存储的有效数据数
	int front;//队头
	int tail;//队尾的后一个位置
} MyCircularQueue;


MyCircularQueue* myCircularQueueCreate(int k) {
	MyCircularQueue* obj = (MyCircularQueue*)malloc(sizeof(MyCircularQueue));//申请一个环形队列
	obj->a = (int*)malloc(sizeof(int)*(k + 1));//开辟队列空间
	//初始时，队头和队尾均为0
	obj->front = 0;
	obj->tail = 0;
	obj->k = k;//设置队列可存储的有效数据个数

	return obj;
}

bool myCircularQueueIsEmpty(MyCircularQueue* obj) {
	return obj->front == obj->tail;//当front和tail指向同一位置时，队列为空
}

bool myCircularQueueIsFull(MyCircularQueue* obj) {
	int tailNext = obj->tail + 1;
	if (tailNext == obj->k + 1)//当指针指到队列末尾时，指针返回队列开头，使队列循环
	{
		tailNext = 0;
	}
	return tailNext == obj->front;//当tail+1指向的位置与front相同时，队列满
}

bool myCircularQueueEnQueue(MyCircularQueue* obj, int value) {
	if (myCircularQueueIsFull(obj))//队列已满，不能再插入数据
	{
		return false;
	}
	else//插入数据
	{
		obj->a[obj->tail] = value;
		obj->tail++;

		if (obj->tail == obj->k + 1)//使队列循环
			obj->tail = 0;

		return true;
	}
}

bool myCircularQueueDeQueue(MyCircularQueue* obj) {
	if (myCircularQueueIsEmpty(obj))//当队列为空时，无法再删除数据
	{
		return false;
	}
	else//删除数据
	{
		obj->front++;

		if (obj->front == obj->k + 1)//使队列循环
			obj->front = 0;

		return true;
	}
}

int myCircularQueueFront(MyCircularQueue* obj) {
	if (myCircularQueueIsEmpty(obj))//当队列为空时，无数据返回
	{
		return -1;
	}
	else
	{
		return obj->a[obj->front];//返回队头指向的数据
	}
}

int myCircularQueueRear(MyCircularQueue* obj) {
	if (myCircularQueueIsEmpty(obj))//当队列为空时，无数据返回
	{
		return -1;
	}
	else//返回tail+1指向位置的数据
	{
		int tailPrev = obj->tail - 1;

		if (tailPrev == -1)//使队列循环
			tailPrev = obj->k;

		return obj->a[tailPrev];
	}
}

void myCircularQueueFree(MyCircularQueue* obj) {
	free(obj->a);//先释放动态开辟的数组
	free(obj);//再释放队列结构体
}