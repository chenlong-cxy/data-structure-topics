#include "HTree.h"

int main()
{
	int n = 0;
	printf("请输入数据个数:>");
	scanf("%d", &n);
	DataType* w = (DataType*)malloc(sizeof(DataType)*n);
	if (w == NULL)
	{
		printf("malloc fail\n");
		exit(-1);
	}
	printf("请输入数据:>");
	for (int i = 0; i < n; i++)
	{
		/*scanf("%d", &w[i]);*/
		scanf("%lf", &w[i]);
	}
	HuffmanTree HT;
	CreateHuff(HT, w, n); //构建哈夫曼树

	HuffmanCode HC;
	HuffCoding(HT, HC, n); //构建哈夫曼编码

	for (int i = 1; i <= n; i++) //打印哈夫曼编码
	{
		printf("数据%.2lf的编码为:%s\n", HT[i].weight, HC[i]);
	}
	free(w);
	return 0;
}