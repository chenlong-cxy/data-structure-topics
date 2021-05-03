//堆排序（升序）
#include <stdio.h>
//交换函数
void Swap(int* x, int* y)
{
	int tmp = *x;
	*x = *y;
	*y = tmp;
}
//堆的向下调整（大堆）
void AdjustDown(int* a, int n, int parent)
{
	//child记录左右孩子中值较大的孩子的下标
	int child = 2 * parent + 1;//先默认其左孩子的值较大
	while (child < n)
	{
		if (child + 1 < n&&a[child + 1] > a[child])//右孩子存在并且右孩子比左孩子还大
		{
			child++;//较大的孩子改为右孩子
		}
		if (a[child] > a[parent])//左右孩子中较大孩子的值比父结点还大
		{
			//将父结点与较大的子结点交换
			Swap(&a[child], &a[parent]);
			//继续向下进行调整
			parent = child;
			child = 2 * parent + 1;
		}
		else//已成堆
		{
			break;
		}
	}
}
void HeapSort(int* a, int n)
{
	//建大堆
	int i;
	for (i = (n - 1 - 1) / 2; i >= 0; i--)
	{
		AdjustDown(a, n, i);
	}
	//排升序
	int end = n - 1;
	while (end > 0)
	{
		Swap(&a[0], &a[end]);
		AdjustDown(a, end, 0);
		end--;
	}
}

int main()
{
	int arr[] = { 23, 43, 56, 87, 12, 34, 54, 87, 23, 83 };
	int sz = sizeof(arr) / sizeof(arr[0]);
	HeapSort(arr, sz);
	int i = 0;
	for (i = 0; i < sz; i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
	return 0;
}