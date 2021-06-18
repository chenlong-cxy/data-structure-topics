#include "HTree.h"

int main()
{
	int n = 0;
	printf("���������ݸ���:>");
	scanf("%d", &n);
	DataType* w = (DataType*)malloc(sizeof(DataType)*n);
	if (w == NULL)
	{
		printf("malloc fail\n");
		exit(-1);
	}
	printf("����������:>");
	for (int i = 0; i < n; i++)
	{
		/*scanf("%d", &w[i]);*/
		scanf("%lf", &w[i]);
	}
	HuffmanTree HT;
	CreateHuff(HT, w, n); //������������

	HuffmanCode HC;
	HuffCoding(HT, HC, n); //��������������

	for (int i = 1; i <= n; i++) //��ӡ����������
	{
		printf("����%.2lf�ı���Ϊ:%s\n", HT[i].weight, HC[i]);
	}
	free(w);
	return 0;
}