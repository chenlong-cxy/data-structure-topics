#include "AVLTree.h"
#include <stdlib.h>
#include <time.h>
#include <vector>

void test1()
{
	AVLTree<int, int> t;
	int arr[] = { 1, 3, 5, 7, 6 };
	//int arr[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
	//int arr[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };
	for (auto e : arr)
	{
		t.Insert(make_pair(e, e));
	}
	t.Inorder();
	cout << t.IsAVLTree() << endl;
	t[3] *= 10;
	t[7] *= 10;
	t[6] *= 90;
	t.Modify(3, 80);
	t.Inorder();
}
void test2()
{
	AVLTree<int, int> t;
	//int arr[] = { 1, 3, 5, 7, 6 };
	int arr[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
	//int arr[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };
	for (auto e : arr)
	{
		t.Insert(make_pair(e, e));
	}
	t.Inorder();
	cout << t.IsAVLTree() << endl;
	//for (auto e : arr)
	//{
	//	t.Erase(e);
	//}
	//t.Erase(16);
	//t.Erase(26);
	t.Erase(3);
	t.Inorder();
	cout << t.IsAVLTree() << endl;
}
void test3()
{
	AVLTree<int, int> t;
	//int arr[] = { 18, 15, 26, 14, 16 };
	int arr[] = { 18, 15, 26, 24, 28 };
	for (auto e : arr)
	{
		t.Insert(make_pair(e, e));
	}
	t.Inorder();
	cout << t.IsAVLTree() << endl;
	t.Erase(15);
	t.Inorder();
	cout << t.IsAVLTree() << endl;
}
void test4()
{
	srand((unsigned int)time(NULL));
	AVLTree<int, int> t;
	//int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
	int n = 1000;
	vector<int> v;
	for (int i = 0; i < n;i++)
	{
		int e = rand();
		v.push_back(e);
		t.Insert(make_pair(e, e));
	}
	for (int i = 0; i < n;i++)
	{
		int e = v[i];
		t.Erase(e);
		cout << t.IsAVLTree() << endl;
	}

}
void test5()
{
	AVLTree<int, int> t;
	//int arr[] = { 18, 15, 26, 14, 16 };
	int arr[] = { 18, 15, 26, 24, 28 };
	for (auto e : arr)
	{
		t.Insert(make_pair(e, e));
	}
	t.Inorder();
	cout << t.IsAVLTree() << endl;
	
	t[18] = 188;
	t[0] = 9;

	t.Inorder();
	cout << t.IsAVLTree() << endl;
}
int main()
{
	test5();
	return 0;
}