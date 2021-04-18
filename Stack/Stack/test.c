#include "stack.h"

void TestStack()
{
	Stack st;
	StackInit(&st);
	StackPush(&st, 1);
	printf("%d ", StackTop(&st));
	StackPop(&st);
	StackPush(&st, 2);
	StackPush(&st, 3);
	printf("%d ", StackTop(&st));
	StackPop(&st);
	StackPush(&st, 4);
	StackPush(&st, 5);
	while (!StackEmpty(&st))
	{
		printf("%d ", StackTop(&st));
		StackPop(&st);
	}

	StackDestroy(&st);
}
int main()
{
	TestStack();
	return 0;
}