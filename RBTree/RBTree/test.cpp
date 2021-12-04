#include "RBTree.h"
void test1()
{
	RBTree<int, int> t;
	//int arr[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
	int arr[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };
	for (auto e : arr)
	{
		t.Insert(make_pair(e, e));
	}
	cout << t.ISRBTree() << endl;
}
int main()
{
	test1();
	return 0;
}