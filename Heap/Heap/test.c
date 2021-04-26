#include "heap.h"

//void Test1()
//{
//	//int a[] = { 27, 15, 19, 18, 28, 34, 65, 49, 25, 37 };
//	//int n = sizeof(a) / sizeof(a[0]);
//	//AdjustDown(a, n, 0);
//
//	int a[] = { 23, 54, 76, 34, 89, 12, 78, 34, 87, 10 };
//	int n = sizeof(a) / sizeof(a[0]);
//	int i = 0;
//	for (i = (n - 1 - 1) / 2; i >= 0; i--)
//	{
//		AdjustDown(a, n, i);
//	}
//}

void Test2()
{
	int a[] = { 23, 54, 76, 34, 89, 12, 78, 34, 87, 10 };
	int n = sizeof(a) / sizeof(a[0]);
	HP hp;
	HeapInit(&hp, a, n);
	HeapPrint(&hp);

	HeapDestroy(&hp);
}
int main()
{
	Test2();
	return 0;
}