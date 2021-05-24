#include "BSTree.h"

int main()
{
	BTNode* p = NULL;
	p = Insert(p, 10);
	p = Insert(p, 2);
	p = Insert(p, 35);
	p = Insert(p, 4);
	p = Insert(p, 5);
	BinaryLevelOrder(p);
	return 0;
}