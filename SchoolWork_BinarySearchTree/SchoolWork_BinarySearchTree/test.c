#include "BSTree.h"

void Test1()
{
	BTNode* p = NULL;
	p = Insert(p, 10);
	p = Insert(p, 2);
	p = Insert(p, 35);
	p = Insert(p, 4);
	p = Insert(p, 5);
	//BinaryLevelOrder(p);
	BTNode* find = Find(p, 35);
	printf("%d\n", find->data);
	find = Find(p, 1);
	if (find == NULL)
	{
		printf("����ʧ��\n");
	}
	else
	{
		printf("%d\n", find->data);
	}
}
// Ҫɾ������Ҷ���
void TestDelete1(BTNode* p)
{
	printf("ɾ��Ҷ�ӽ��35��:>\n");
	p = Delete(p, 35);
	BinaryLevelOrder(p);
}
// Ҫɾ���Ľ��ֻ��һ�����ӽ��
void TestDelete2(BTNode* p)
{
	printf("ɾ��ֻ��һ�����ӵĽ��33��:>\n");
	p = Delete(p, 33);
	BinaryLevelOrder(p);
}
// Ҫɾ���Ľ����������������
void TestDelete3(BTNode* p)
{
	p = Insert(p, 34);
	printf("����Ԫ��34��:>\n");
	BinaryLevelOrder(p);

	printf("ɾ�����������ӵĽ��41��:>\n");
	p = Delete(p, 41);
	BinaryLevelOrder(p);
}

void Test2()
{
	BTNode* p = NULL;
	p = Insert(p, 30);
	p = Insert(p, 15);
	p = Insert(p, 41);
	p = Insert(p, 50);
	p = Insert(p, 33);
	printf("ԭ����������Ϊ:>\n");
	printf("�������:>");
	BinaryLevelOrder(p);
	printf("�������:>");
	BinaryInOrder(p);
	printf("\n");

	p = Insert(p, 35);
	printf("����Ԫ��35��:>\n");
	printf("�������:>");
	BinaryLevelOrder(p);
	printf("�������:>");
	BinaryInOrder(p);
	printf("\n");

	// �ݹ����
	//BTNode* pmax = FindMax(p);
	//BTNode* pmin = FindMin(p);
	// �ǵݹ����
	BTNode* pmax = FindMaxNonR(p);
	BTNode* pmin = FindMinNonR(p);
	printf("���Ԫ��Ϊ:>%d\n", pmax->data);
	printf("��СԪ��Ϊ:>%d\n", pmin->data);

	// Ҫɾ������Ҷ���
	//TestDelete1(p);
	// Ҫɾ���Ľ��ֻ��һ�����ӽ��
	TestDelete2(p);
	// Ҫɾ���Ľ����������������
	//TestDelete3(p);
}

int main()
{
	Test2();
	return 0;
}