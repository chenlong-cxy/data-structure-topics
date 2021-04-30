#include "DStack.h"

int main()
{
	DblStack ds;
	DblStackInit(&ds);

	DblStackPush(&ds, 1, 1);
	DblStackPush(&ds, 1, 2);
	DblStackPush(&ds, 1, 3);
	DblStackPush(&ds, 1, 4);
	DblStackPush(&ds, 1, 5);
	DblStackPush(&ds, 2, 10);
	DblStackPush(&ds, 2, 11);
	DblStackPush(&ds, 2, 12);
	DblStackPush(&ds, 2, 13);
	DblStackPush(&ds, 2, 14);
	DblStackPrint(&ds);
	printf("%d\n", DblStackPop(&ds, 1));
	DblStackPrint(&ds);
	if (DblStackFull(&ds))
	{
		printf("Õ»Âú\n");
	}

	return 0;
}