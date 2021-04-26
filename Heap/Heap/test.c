#include <stdio.h>
void Swap(int* x, int* y)
{
	int tmp = *x;
	*x = *y;
	*y = tmp;
}
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
int main()
{
	//int a[] = { 27, 15, 19, 18, 28, 34, 65, 49, 25, 37 };
	//int n = sizeof(a) / sizeof(a[0]);
	//AdjustDown(a, n, 0);

	int a[] = { 23, 54, 76, 34, 89, 12, 78, 34, 87, 10 };
	int n = sizeof(a) / sizeof(a[0]);
	int i = 0;
	for (i = (n - 1 - 1) / 2; i >= 0; i--)
	{
		AdjustDown(a, n, i);
	}
	return 0;
}