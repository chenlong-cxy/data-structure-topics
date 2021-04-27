#include "heap.h"

//交换函数
void Swap(int* x, int* y)
{
	int tmp = *x;
	*x = *y;
	*y = tmp;
}

//堆的向下调整（小堆）
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
	memcpy(php->a, a, sizeof(HPDataType)*n);//拷贝数据
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

//求结点数为n的二叉树的深度
int depth(int n)
{
	assert(n >= 0);

	if (n>0)
	{
		int m = 2;
		int hight = 1;
		while (m < n + 1)
		{
			m *= 2;
			hight++;
		}
		return hight;
	}
	else
	{
		return 0;
	}
}
//打印堆
void HeapPrint(HP* php)
{
	assert(php);
	//普通打印
	int i = 0;
	for (i = 0; i < php->size; i++)
	{
		printf("%d ", php->a[i]);
	}
	printf("\n");
	//树形结构打印
	int h = depth(php->size);
	int N = (int)pow(2, h) - 1;//与该二叉树深度相同的满二叉树的结点总数
	int space = N - 1;//记录每一行前面的空格数
	int row = 1;//当前打印的行数
	int pos = 0;//待打印数据的下标
	while (1)
	{
		//打印前面的空格
		int i = 0;
		for (i = 0; i < space; i++)
		{
			printf(" ");
		}
		//打印数据和间距
		int count = (int)pow(2, row - 1);//每一行的数字个数
		while (count--)//打印一行
		{
			printf("%02d", php->a[pos++]);//打印数据
			if (pos >= php->size)//数据打印完毕
			{
				printf("\n");
				return;
			}
			int distance = (space + 1) * 2;//两个数之间的空格数
			while (distance--)//打印两个数之间的空格
			{
				printf(" ");
			}
		}
		printf("\n");
		row++;
		space = space / 2 - 1;
	}
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
	int child = php->size - 1;
	while (child > 0)
	{
		int parent = (child - 1) / 2;
		if (php->a[child] < php->a[parent])
		{
			Swap(&php->a[child], &php->a[parent]);
		}
		child = parent;
	}
}

//删除堆顶元素
void HeapPop(HP* php)
{

}

//获取堆顶元素
HPDataType HeapTop(HP* php);
//获取堆中元素个数
int HeapSize(HP* php);
//判断堆是否为空
bool HeapEmpty(HP* php);