#include "heap.h"

//��������
void Swap(HPDataType* x, HPDataType* y)
{
	HPDataType tmp = *x;
	*x = *y;
	*y = tmp;
}

//�ѵ����µ�����С�ѣ�
void AdjustDown(HPDataType* a, int n, int parent)
{
	//child��¼���Һ�����ֵ��С�ĺ��ӵ��±�
	int child = 2 * parent + 1;//��Ĭ�������ӵ�ֵ��С
	while (child < n)
	{
		if (child + 1 < n&&a[child + 1] < a[child])//�Һ��Ӵ��ڲ����Һ��ӱ����ӻ�С
		{
			child++;//��С�ĺ��Ӹ�Ϊ�Һ���
		}
		if (a[child] < a[parent])//���Һ����н�С���ӵ�ֵ�ȸ���㻹С
		{
			//����������С���ӽ�㽻��
			Swap(&a[child], &a[parent]);
			//�������½��е���
			parent = child;
			child = 2 * parent + 1;
		}
		else//�ѳɶ�
		{
			break;
		}
	}
}

//�ѵ����ϵ�����С�ѣ�
void AdjustUp(HPDataType* a, int child)
{
	int parent = (child - 1) / 2;
	while (child > 0)
	{
		if (a[child] < a[parent])
		{
			Swap(&a[child], &a[parent]);
			child = parent;
			parent = (child - 1) / 2;
		}
		else
		{
			break;
		}
	}
}

//��ʼ����
void HeapInit(HP* php, HPDataType* a, int n)
{
	assert(php);

	HPDataType* tmp = (HPDataType*)malloc(sizeof(HPDataType)*n);//����һ���ѽṹ
	if (tmp == NULL)
	{
		printf("malloc fail\n");
		exit(-1);
	}
	php->a = tmp;
	memcpy(php->a, a, sizeof(HPDataType)*n);//�������ݵ�����
	php->size = n;
	php->capacity = n;
	int i = 0;
	//����
	for (i = (php->size - 1 - 1) / 2; i >= 0; i--)
	{
		AdjustDown(php->a, php->size, i);
	}
}

//���ٶ�
void HeapDestroy(HP* php)
{
	assert(php);

	free(php->a);
	php->a = NULL;
	php->size = 0;
	php->capacity = 0;
}

//������Ϊn�Ķ����������
int depth(int n)
{
	assert(n >= 0);

	if (n>0)
	{
		int m = 2;
		int hight = 1;
		while (m < n + 1)
		{
			m *= 2;
			hight++;
		}
		return hight;
	}
	else
	{
		return 0;
	}
}

//��ӡ��
void HeapPrint(HP* php)
{
	assert(php);
	//��ͨ��ӡ
	int i = 0;
	for (i = 0; i < php->size; i++)
	{
		printf("%d ", php->a[i]);
	}
	printf("\n");
	//���νṹ��ӡ
	int h = depth(php->size);
	int N = (int)pow(2, h) - 1;//��ö����������ͬ�����������Ľ������
	int space = N - 1;//��¼ÿһ��ǰ��Ŀո���
	int row = 1;//��ǰ��ӡ������
	int pos = 0;//����ӡ���ݵ��±�
	while (1)
	{
		//��ӡǰ��Ŀո�
		int i = 0;
		for (i = 0; i < space; i++)
		{
			printf(" ");
		}
		//��ӡ���ݺͼ��
		int count = (int)pow(2, row - 1);//ÿһ�е����ָ���
		while (count--)//��ӡһ��
		{
			printf("%02d", php->a[pos++]);//��ӡ����
			if (pos >= php->size)//���ݴ�ӡ���
			{
				printf("\n");
				return;
			}
			int distance = (space + 1) * 2;//������֮��Ŀո���
			while (distance--)//��ӡ������֮��Ŀո�
			{
				printf(" ");
			}
		}
		printf("\n");
		row++;
		space = space / 2 - 1;
	}
}



//�ѵĲ���
void HeapPush(HP* php, HPDataType x)
{
	assert(php);

	if (php->size == php->capacity)
	{
		HPDataType* tmp = (HPDataType*)realloc(php->a, 2 * php->capacity*sizeof(HPDataType));
		if (tmp == NULL)
		{
			printf("realloc fail\n");
			exit(-1);
		}
		php->a = tmp;
		php->capacity *= 2;
	}
	php->a[php->size] = x;
	php->size++;
	//���ϵ���
	AdjustUp(php->a, php->size - 1);
}

//�ѵ�ɾ��
void HeapPop(HP* php)
{
	assert(php);
	assert(!HeapEmpty(php));

	Swap(&php->a[0], &php->a[php->size - 1]);
	php->size--;
	AdjustDown(php->a, php->size, 0);
}

//��ȡ�Ѷ�������
HPDataType HeapTop(HP* php)
{
	assert(php);
	assert(!HeapEmpty(php));

	return php->a[0];
}

//��ȡ�������ݸ���
int HeapSize(HP* php)
{
	assert(php);

	return php->size;
}

//�ѵ��п�
bool HeapEmpty(HP* php)
{
	assert(php);

	return php->size == 0;
}
