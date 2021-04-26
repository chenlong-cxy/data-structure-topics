#include "heap.h"

//交换函数
void Swap(int* x, int* y)
{
	int tmp = *x;
	*x = *y;
	*y = tmp;
}

//堆的向下调整
void AdjustDown(int* a, int n, int parent)
{
	int child = 2 * parent + 1;
	while (child < n)
	{
		if (child + 1 < n&&a[child + 1] < a[child])
		{
			child++;
		}
		if (a[child] < a[parent])
		{
			Swap(&a[child], &a[parent]);
			parent = child;
			child = 2 * parent + 1;
		}
		else
		{
			break;
		}
	}
}

//初始化堆
void HeapInit(HP* php, HPDataType* a, int n)
{
	assert(php);

	HPDataType* tmp = (HPDataType*)malloc(sizeof(HPDataType)*n);
	if (tmp == NULL)
	{
		printf("malloc fail\n");
		exit(-1);
	}
	php->a = tmp;
	memcpy(php->a, a, sizeof(HPDataType)*n);
	php->size = n;
	php->capacity = n;
	int i = 0;
	for (i = (php->size - 1 - 1) / 2; i >= 0; i--)
	{
		AdjustDown(php->a, n, i);
	}
}

//销毁堆
void HeapDestroy(HP* php)
{
	assert(php);

	free(php->a);
	php->a = NULL;
	php->size = 0;
	php->capacity = 0;
}
//打印堆
void HeapPrint(HP* php)
{
	assert(php);

	int i = 0;
	for (i = 0; i < php->size; i++)
	{
		printf("%d ", php->a[i]);
	}
	printf("\n");
}

//向堆中插入元素
void HeapPush(HP* php, HPDataType x)
{
	assert(php);
	
	if (php->size == php->capacity)
	{
		HPDataType* tmp = (HPDataType*)realloc(php->a, sizeof(HPDataType)* 2 * php->capacity);
		if (tmp == NULL)
		{
			printf("realloc fail\n");
			exit(-1);
		}
		php->a = tmp;
	}
	php->a[php->size] = x;
	php->size++;
	//向上调整

}

//删除堆顶元素
void HeapPop(HP* php);

//获取堆顶元素
HPDataType HeapTop(HP* php);
//获取堆中元素个数
int HeapSize(HP* php);
//判断堆是否为空
bool HeapEmpty(HP* php);