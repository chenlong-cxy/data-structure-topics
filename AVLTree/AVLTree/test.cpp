#include "AVLTree.h"

void test1()
{
	AVLTree<int, int> t;
	int arr[] = { 1, 3, 5, 7, 6 };
	for (auto e : arr)
	{
		t.Insert(make_pair(e, e));
	}

}
int main()
{
	test1();
	return 0;
}