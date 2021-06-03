#include "BSTree.h"

void Test1()
{
	BTNode* p = NULL;
	p = Insert(p, 10);
	p = Insert(p, 2);
	p = Insert(p, 35);
	p = Insert(p, 4);
	p = Insert(p, 5);
	//BinaryLevelOrder(p);
	BTNode* find = Find(p, 35);
	printf("%d\n", find->data);
	find = Find(p, 1);
	if (find == NULL)
	{
		printf("²éÕÒÊ§°Ü\n");
	}
	else
	{
		printf("%d\n", find->data);
	}
}

void Test2()
{
	BTNode* p = NULL;
	p = Insert(p, 10);
	p = Insert(p, 2);
	p = Insert(p, 35);
	p = Insert(p, 4);
	p = Insert(p, 5);

}

int main()
{
	Test2();
	return 0;
}