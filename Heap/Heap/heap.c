#include "heap.h"

//��������
void Swap(int* x, int* y)
{
	int tmp = *x;
	*x = *y;
	*y = tmp;
}

//�ѵ����µ�����С�ѣ�
void AdjustDown(int* a, int n, int parent)
{
	int child = 2 * parent + 1;
	while (child < n)
	{
		if (child + 1 < n&&a[child + 1] < a[child])
		{
			child++;
		}
		if (a[child] < a[parent])
		{
			Swap(&a[child], &a[parent]);
			parent = child;
			child = 2 * parent + 1;
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

	HPDataType* tmp = (HPDataType*)malloc(sizeof(HPDataType)*n);
	if (tmp == NULL)
	{
		printf("malloc fail\n");
		exit(-1);
	}
	php->a = tmp;
	memcpy(php->a, a, sizeof(HPDataType)*n);//��������
	php->size = n;
	php->capacity = n;
	int i = 0;
	for (i = (php->size - 1 - 1) / 2; i >= 0; i--)
	{
		AdjustDown(php->a, n, i);
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

//����в���Ԫ��
void HeapPush(HP* php, HPDataType x)
{
	assert(php);
	
	if (php->size == php->capacity)
	{
		HPDataType* tmp = (HPDataType*)realloc(php->a, sizeof(HPDataType)* 2 * php->capacity);
		if (tmp == NULL)
		{
			printf("realloc fail\n");
			exit(-1);
		}
		php->a = tmp;
	}
	php->a[php->size] = x;
	php->size++;
	//���ϵ���
	int child = php->size - 1;
	while (child > 0)
	{
		int parent = (child - 1) / 2;
		if (php->a[child] < php->a[parent])
		{
			Swap(&php->a[child], &php->a[parent]);
		}
		child = parent;
	}
}

//ɾ���Ѷ�Ԫ��
void HeapPop(HP* php)
{

}

//��ȡ�Ѷ�Ԫ��
HPDataType HeapTop(HP* php);
//��ȡ����Ԫ�ظ���
int HeapSize(HP* php);
//�ж϶��Ƿ�Ϊ��
bool HeapEmpty(HP* php);