#include "SList.h"

//��ӡ����
void SListPrint(SListNode* plist)
{
	SListNode* cur = plist;//����ͷָ��
	while (cur != NULL)//�ж������Ƿ��ӡ���
	{
		printf("%d->", cur->data);//��ӡ����
		cur = cur->next;//ָ��ָ����һ�����
	}
	printf("NULL\n");//��ӡNULL�������������һ�����ָ��NULL
}

//����һ���½�㣬�����½���ַ
SListNode* BuySLTNode(SLTDataType x)
{
	SListNode* node = (SListNode*)malloc(sizeof(SListNode));//���½������ռ�
	if (node == NULL)
	{
		printf("malloc fail\n");
		exit(-1);
	}
	node->data = x;//�����ݸ�ֵ���½���������
	node->next = NULL;//���½���ָ�����ÿ�
	return node;//�����½���ַ
}

//ͷ��
void SListPushFront(SListNode** pplist, SLTDataType x)
{
	SListNode* newnode = BuySLTNode(x);//����һ���½��
	newnode->next = *pplist;//�½���ָ����ָ��ͷָ��ָ���λ��
	*pplist = newnode;//ͷָ��ָ���½��
}

//β��
void SListPushBack(SListNode** pplist, SLTDataType x)
{
	SListNode* newnode = BuySLTNode(x);//����һ���½��
	if (*pplist == NULL)//�ж��Ƿ�Ϊ�ձ�
	{
		*pplist = newnode;//ͷָ��ֱ��ָ���½��
	}
	else
	{
		SListNode* tail = *pplist;//����ͷָ��
		while (tail->next != NULL)//��ĳ����ָ����ΪNULL��˵���������һ�����
		{
			tail = tail->next;////ָ��ָ����һ�����
		}
		tail->next = newnode;//�����һ������ָ����ָ���½��
	}
}

//�ڸ���λ��֮�����
void SListInsertAfter(SListNode* pos, SLTDataType x)
{
	assert(pos);//ȷ�������ַ��Ϊ��
	SListNode* newnode = BuySLTNode(x);//����һ���½��
	newnode->next = pos->next;//���½���ָ����ָ���ַΪpos�Ľ�����һ�����
	pos->next = newnode;//�õ�ַΪpos�Ľ��ָ���½��
}

//�ڸ���λ��֮ǰ����
void SListInsertBefore(SListNode** pplist, SListNode* pos, SLTDataType x)
{
	assert(pos);//ȷ�������ַ��Ϊ��
	SListNode* newnode = BuySLTNode(x);//����һ���½��
	if (pos == *pplist)//�жϸ���λ���Ƿ�Ϊͷָ��ָ���λ��
	{
		newnode->next = pos;//���½���ָ����ָ���ַΪpos�Ľ��
		*pplist = newnode;//��ͷָ��ָ���½��
	}
	else
	{
		SListNode* prev = *pplist;//����ͷָ��
		while (prev->next != pos)//�ҵ���ַΪpos�Ľ���ǰһ�����
		{
			prev = prev->next;
		}
		newnode->next = prev->next;//���½���ָ����ָ���ַΪpos�Ľ��
		prev->next = newnode;//��ǰһ�����ָ���½��
	}
}

//ͷɾ
void SListPopFront(SListNode** pplist)
{
	if (*pplist == NULL)//�ж��Ƿ�Ϊ�ձ�
	{
		return;
	}
	else
	{
		SListNode* tmp = *pplist;//��¼��һ������λ��
		*pplist = (*pplist)->next;//��ͷָ��ָ��ڶ������
		free(tmp);//�ͷŵ�һ�������ڴ�ռ�
		tmp = NULL;//��ʱ�ÿ�
	}
}

//βɾ
void SListPopBack(SListNode** pplist)
{
	if (*pplist == NULL)//�ж��Ƿ�Ϊ�ձ�
	{
		return;
	}
	else if ((*pplist)->next == NULL)//�ж��Ƿ�ֻ��һ�����
	{
		free(*pplist);//�ͷŸý��
		*pplist = NULL;//��ʱ�ÿ�
	}
	else
	{
		SListNode* prev = *pplist;//����ͷָ��
		SListNode* tail = (*pplist)->next;//���յ�һ�����ĵ�ַ
		while (tail->next != NULL)//��tailָ�����һ�����ʱֹͣѭ��
		{
			prev = tail;//ʹprevʼ��ָ��tail��ǰһ�����
			tail = tail->next;//tailָ�����
		}
		free(tail);//�ͷ����һ�����
		tail = NULL;//��ʱ�ÿ�
		prev->next = NULL;//�������ڶ�������ָ�����ÿգ�ʹ���Ϊ�µ�β�ڵ�
	}
}

//ɾ������λ��֮���ֵ
void SListErasetAfter(SListNode* pos)
{
	assert(pos);//ȷ�������ַ��Ϊ��
	if (pos->next == NULL)//�жϴ����ַ�Ƿ�Ϊ���һ�����ĵ�ַ
	{
		return;
	}
	SListNode* after = pos->next;//��ɾ���Ľ��
	pos->next = after->next;//��pos���ָ���ɾ���Ľ�����һ�����
	free(after);//�ͷŽ��
	after = NULL;//��ʱ�ÿ�
}

//ɾ������λ�õ�ֵ
void SListErasetCur(SListNode** pplist, SListNode* pos)
{
	assert(pos);//ȷ�������ַ��Ϊ��
	if (pos == *pplist)//�жϴ�ɾ���Ľ���Ƿ�Ϊ��һ�����
	{
		*pplist = pos->next;//��ͷָ��ָ��ڶ������
		free(pos);//�ͷŵ�һ�����
		pos=NULL;//��ʱ�ÿ�
	}
	else
	{
		SListNode* prev = *pplist;//����ͷָ��
		while (prev->next != pos)//�ҵ���ɾ������ǰһ�����
		{
			prev = prev->next;
		}
		prev->next = pos->next;//�ô�ɾ���Ľ���ǰһ�����ָ���ɾ�����ĺ�һ�����
		free(pos);//�ͷŴ�ɾ�����
		pos = NULL;//��ʱ�ÿ�
	}
}

//��������
SListNode* SListFind(SListNode* plist, SLTDataType x)
{
	SListNode* cur = plist;//����ͷָ��
	while (cur != NULL)//��������
	{
		if (cur->data == x)//�жϽ���Ƿ�Ϊ���ҽ��
			return cur;//����Ŀ����ĵ�ַ
		cur = cur->next;//ָ�����
	}
	return NULL;//û���ҵ�����Ϊx�Ľ��
}

//�޸�����
void SListModify(SListNode* pos, SLTDataType x)
{
	pos->data = x;//���������ݸ�ΪĿ������
}