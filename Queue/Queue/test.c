#include "queue.h"

void TestQueue()
{
	Queue q;
	QueueInit(&q);
	QueuePush(&q, 1);
	printf("%d ", QueueFront(&q));
	QueuePop(&q);
	QueuePush(&q, 2);
	QueuePush(&q, 3);
	printf("%d ", QueueFront(&q));
	QueuePop(&q);
	QueuePush(&q, 4);
	QueuePush(&q, 5);
	while (!QueueEmpty(&q))
	{
		printf("%d ", QueueFront(&q));
		QueuePop(&q);
	}
	//QueuePop(&q);
	QueueDestroy(&q);
}
int main()
{
	TestQueue();
	return 0;
}