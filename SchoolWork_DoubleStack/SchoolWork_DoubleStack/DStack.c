#include "DStack.h"

//�ж�ջ��
bool DblStackEmpty(DblStack* pds)
{
	assert(pds);//���ԣ��ж�ָ����Ч��

	return pds->top[0] == -1 && pds->top[1] == pds->m;
}

//�ж�ջ��
bool DblStackFull(DblStack* pds)
{
	assert(pds);//���ԣ��ж�ָ����Ч��

	return pds->top[1] - pds->top[0] == 1;
}

//��ջ
bool DblStackPush(DblStack* pds, int tag, SElemType x)
{
	assert(pds);//���ԣ��ж�ָ����Ч��
	assert(DblStackFull(pds));//ջ�����޷���ջ


}

//��ջ
SElemType DblStackPop(DblStack*pds, int tag)
{
	assert(pds);//���ԣ��ж�ָ����Ч��
	assert(DblStackEmpty(pds));//ջ�գ��޷���ջ


}