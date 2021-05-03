//����������
#include <stdio.h>
//��������
void Swap(int* x, int* y)
{
	int tmp = *x;
	*x = *y;
	*y = tmp;
}
//�ѵ����µ�������ѣ�
void AdjustDown(int* a, int n, int parent)
{
	//child��¼���Һ�����ֵ�ϴ�ĺ��ӵ��±�
	int child = 2 * parent + 1;//��Ĭ�������ӵ�ֵ�ϴ�
	while (child < n)
	{
		if (child + 1 < n&&a[child + 1] > a[child])//�Һ��Ӵ��ڲ����Һ��ӱ����ӻ���
		{
			child++;//�ϴ�ĺ��Ӹ�Ϊ�Һ���
		}
		if (a[child] > a[parent])//���Һ����нϴ��ӵ�ֵ�ȸ���㻹��
		{
			//���������ϴ���ӽ�㽻��
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
void HeapSort(int* a, int n)
{
	//�����
	int i;
	for (i = (n - 1 - 1) / 2; i >= 0; i--)
	{
		AdjustDown(a, n, i);
	}
	//������
	int end = n - 1;
	while (end > 0)
	{
		Swap(&a[0], &a[end]);
		AdjustDown(a, end, 0);
		end--;
	}
}

int main()
{
	int arr[] = { 23, 43, 56, 87, 12, 34, 54, 87, 23, 83 };
	int sz = sizeof(arr) / sizeof(arr[0]);
	HeapSort(arr, sz);
	int i = 0;
	for (i = 0; i < sz; i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
	return 0;
}