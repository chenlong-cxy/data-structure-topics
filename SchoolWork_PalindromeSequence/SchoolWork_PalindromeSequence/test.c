#include "stack.h"

int main()
{
	char arr1[] = "abcdef";
	printf("%d\n", Judgearray(arr1));

	char arr2[] = "abdba";
	printf("%d\n", Judgearray(arr2));

	char arr3[] = "abba";
	printf("%d\n", Judgearray(arr3));

	char arr4[] = "good";
	printf("%d\n", Judgearray(arr4));
	return 0;
}