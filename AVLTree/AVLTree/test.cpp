#include "AVLTree.h"

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
int main()
{
	test1();
	return 0;
}