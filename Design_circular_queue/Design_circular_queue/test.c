//������ѭ������ʵ�֡� 
//ѭ��������һ���������ݽṹ����������ֻ��� FIFO���Ƚ��ȳ���ԭ��
//���Ҷ�β�������ڶ���֮�����γ�һ��ѭ������Ҳ����Ϊ�����λ���������

//ѭ�����е�һ���ô������ǿ��������������֮ǰ�ù��Ŀռ䡣
//��һ����ͨ�����һ��һ���������ˣ����ǾͲ��ܲ�����һ��Ԫ�أ���ʹ�ڶ���ǰ�����пռ䡣
//����ʹ��ѭ�����У�������ʹ����Щ�ռ�ȥ�洢�µ�ֵ��

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
	int* a;//����ģ�⻷�ζ���
	int k;//���пɴ洢����Ч������
	int front;//��ͷ
	int tail;//��β�ĺ�һ��λ��
} MyCircularQueue;


MyCircularQueue* myCircularQueueCreate(int k) {
	MyCircularQueue* obj = (MyCircularQueue*)malloc(sizeof(MyCircularQueue));//����һ�����ζ���
	obj->a = (int*)malloc(sizeof(int)*(k + 1));//���ٶ��пռ�
	//��ʼʱ����ͷ�Ͷ�β��Ϊ0
	obj->front = 0;
	obj->tail = 0;
	obj->k = k;//���ö��пɴ洢����Ч���ݸ���

	return obj;
}

bool myCircularQueueIsEmpty(MyCircularQueue* obj) {
	return obj->front == obj->tail;//��front��tailָ��ͬһλ��ʱ������Ϊ��
}

bool myCircularQueueIsFull(MyCircularQueue* obj) {
	int tailNext = obj->tail + 1;
	if (tailNext == obj->k + 1)//��ָ��ָ������ĩβʱ��ָ�뷵�ض��п�ͷ��ʹ����ѭ��
	{
		tailNext = 0;
	}
	return tailNext == obj->front;//��tail+1ָ���λ����front��ͬʱ��������
}

bool myCircularQueueEnQueue(MyCircularQueue* obj, int value) {
	if (myCircularQueueIsFull(obj))//���������������ٲ�������
	{
		return false;
	}
	else//��������
	{
		obj->a[obj->tail] = value;
		obj->tail++;

		if (obj->tail == obj->k + 1)//ʹ����ѭ��
			obj->tail = 0;

		return true;
	}
}

bool myCircularQueueDeQueue(MyCircularQueue* obj) {
	if (myCircularQueueIsEmpty(obj))//������Ϊ��ʱ���޷���ɾ������
	{
		return false;
	}
	else//ɾ������
	{
		obj->front++;

		if (obj->front == obj->k + 1)//ʹ����ѭ��
			obj->front = 0;

		return true;
	}
}

int myCircularQueueFront(MyCircularQueue* obj) {
	if (myCircularQueueIsEmpty(obj))//������Ϊ��ʱ�������ݷ���
	{
		return -1;
	}
	else
	{
		return obj->a[obj->front];//���ض�ͷָ�������
	}
}

int myCircularQueueRear(MyCircularQueue* obj) {
	if (myCircularQueueIsEmpty(obj))//������Ϊ��ʱ�������ݷ���
	{
		return -1;
	}
	else//����tail+1ָ��λ�õ�����
	{
		int tailPrev = obj->tail - 1;

		if (tailPrev == -1)//ʹ����ѭ��
			tailPrev = obj->k;

		return obj->a[tailPrev];
	}
}

void myCircularQueueFree(MyCircularQueue* obj) {
	free(obj->a);//���ͷŶ�̬���ٵ�����
	free(obj);//���ͷŶ��нṹ��
}