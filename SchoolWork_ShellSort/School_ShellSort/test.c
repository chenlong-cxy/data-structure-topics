#include <stdio.h>
// ÷±Ω”≤Â»Î≈≈–Ú
void InsertSort(int* arr, int n)
{
	int i = 0;
	for (i = 0; i < n - 1; i++)
	{
		int end = i;
		int tmp = arr[end + 1];
		while (end >= 0)
		{
			if (arr[end]>tmp)
			{
				arr[end + 1] = arr[end];
				end--;
			}
			else
			{
				break;
			}
		}
		arr[end + 1] = tmp;
	}
}
// œ£∂˚≈≈–Ú
void ShellSort(int* arr, int n)
{
	int gap = n;
	while (gap > 1)
	{
		gap = gap / 2;// ‘ˆ¡ø
		int i = 0;
		for (i = 0; i < n - gap; i++)
		{
			int end = i;
			int tmp = arr[end + gap];
			while (end >= 0)
			{
				if (arr[end]>tmp)
				{
					arr[end + gap] = arr[end];
					end -= gap;
				}
				else
				{
					break;
				}
			}
			arr[end + gap] = tmp;
		}
	}
}
// œ£∂˚≈≈–Ú£® È£©
void ShellSortBook(int* arr, int n)
{
	int Sedgewick[] = { 929, 505, 209, 109, 41, 19, 5, 1, 0 };
	int Si = 0;
	for (Si = 0; Sedgewick[Si] >= n; Si++)
		;
	int D = 0;
	for (D = Sedgewick[Si]; D > 0; D = Sedgewick[++Si])
	{
		int P = 0;
		for (P = D; P < n; P++)
		{
			int tmp = arr[P];
			int i = 0;
			for (i = P; i>=D&&arr[i - D]>tmp; i -= D)
			{
				arr[i] = arr[i - D];
			}
			arr[i] = tmp;
		}
	}
}
int main()
{
	int arr[] = { 24, 76, 23, 55, 89, 65, 18, 5, 0, 25, 34, 67, 12 };
	int n = sizeof(arr) / sizeof(arr[0]);
	ShellSortBook(arr, n);

	int i = 0;
	for (i = 0; i < n; i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
	return 0;
}