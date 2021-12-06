#include "RBTree.h"
#include <stdlib.h>
#include <time.h>
#include <vector>
void test1()
{
	RBTree<int, int> t;
	//int arr[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
	int arr[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };
	for (auto e : arr)
	{
		t.Insert(make_pair(e, e));
	}
	//t.Inorder();
	cout << t.ISRBTree() << endl;
}
void test2()
{
	RBTree<int, int> t;
	int arr[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
	//int arr[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };
	for (auto e : arr)
	{
		t.Insert(make_pair(e, e));
	}
	for (auto e : arr)
	{
		t.Erase(e);
		cout << t.ISRBTree() << endl;
	}
	t.Erase(4);
	cout << t.ISRBTree() << endl;
}
void test3()
{
	srand((unsigned int)time(NULL));
	RBTree<int, int> t;
	vector<int> arr;
	int n = 10000;
	for (int i = 0; i < n; i++)
	{
		int e = rand();
		t.Insert(make_pair(e, e));
		arr.push_back(e);
	}
	for (int i = n-1; i >= 0;i--)
	{
		int e = arr[i];
		t.Erase(e);
		cout << t.ISRBTree() << endl;
	}
	cout << t.ISRBTree() << endl;
}
int main()
{
	test3();
	return 0;
}