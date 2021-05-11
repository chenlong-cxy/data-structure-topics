#include "SList.h"

//打印链表
void SListPrint(SListNode* plist)
{
	SListNode* cur = plist;//接收头指针
	while (cur != NULL)//判断链表是否打印完毕
	{
		printf("%d->", cur->data);//打印数据
		cur = cur->next;//指针指向下一个结点
	}
	printf("NULL\n");//打印NULL，表明链表最后一个结点指向NULL
}

//创建一个新结点，返回新结点地址
SListNode* BuySLTNode(SLTDataType x)
{
	SListNode* node = (SListNode*)malloc(sizeof(SListNode));//向新结点申请空间
	if (node == NULL)
	{
		printf("malloc fail\n");
		exit(-1);
	}
	node->data = x;//将数据赋值到新结点的数据域
	node->next = NULL;//将新结点的指针域置空
	return node;//返回新结点地址
}

//头插
void SListPushFront(SListNode** pplist, SLTDataType x)
{
	SListNode* newnode = BuySLTNode(x);//申请一个新结点
	newnode->next = *pplist;//新结点的指针域指向头指针指向的位置
	*pplist = newnode;//头指针指向新结点
}

//尾插
void SListPushBack(SListNode** pplist, SLTDataType x)
{
	SListNode* newnode = BuySLTNode(x);//申请一个新结点
	if (*pplist == NULL)//判断是否为空表
	{
		*pplist = newnode;//头指针直接指向新结点
	}
	else
	{
		SListNode* tail = *pplist;//接收头指针
		while (tail->next != NULL)//若某结点的指针域为NULL，说明它是最后一个结点
		{
			tail = tail->next;////指针指向下一个结点
		}
		tail->next = newnode;//让最后一个结点的指针域指向新结点
	}
}

//在给定位置之后插入
void SListInsertAfter(SListNode* pos, SLTDataType x)
{
	assert(pos);//确保传入地址不为空
	SListNode* newnode = BuySLTNode(x);//申请一个新结点
	newnode->next = pos->next;//让新结点的指针域指向地址为pos的结点的下一个结点
	pos->next = newnode;//让地址为pos的结点指向新结点
}

//在给定位置之前插入
void SListInsertBefore(SListNode** pplist, SListNode* pos, SLTDataType x)
{
	assert(pos);//确保传入地址不为空
	SListNode* newnode = BuySLTNode(x);//申请一个新结点
	if (pos == *pplist)//判断给定位置是否为头指针指向的位置
	{
		newnode->next = pos;//让新结点的指针域指向地址为pos的结点
		*pplist = newnode;//让头指针指向新结点
	}
	else
	{
		SListNode* prev = *pplist;//接收头指针
		while (prev->next != pos)//找到地址为pos的结点的前一个结点
		{
			prev = prev->next;
		}
		newnode->next = prev->next;//让新结点的指针域指向地址为pos的结点
		prev->next = newnode;//让前一个结点指向新结点
	}
}

//头删
void SListPopFront(SListNode** pplist)
{
	if (*pplist == NULL)//判断是否为空表
	{
		return;
	}
	else
	{
		SListNode* tmp = *pplist;//记录第一个结点的位置
		*pplist = (*pplist)->next;//让头指针指向第二个结点
		free(tmp);//释放第一个结点的内存空间
		tmp = NULL;//及时置空
	}
}

//尾删
void SListPopBack(SListNode** pplist)
{
	if (*pplist == NULL)//判断是否为空表
	{
		return;
	}
	else if ((*pplist)->next == NULL)//判断是否只有一个结点
	{
		free(*pplist);//释放该结点
		*pplist = NULL;//及时置空
	}
	else
	{
		SListNode* prev = *pplist;//接收头指针
		SListNode* tail = (*pplist)->next;//接收第一个结点的地址
		while (tail->next != NULL)//当tail指向最后一个结点时停止循环
		{
			prev = tail;//使prev始终指向tail的前一个结点
			tail = tail->next;//tail指针后移
		}
		free(tail);//释放最后一个结点
		tail = NULL;//及时置空
		prev->next = NULL;//将倒数第二个结点的指针域置空，使其成为新的尾节点
	}
}

//删除给定位置之后的值
void SListErasetAfter(SListNode* pos)
{
	assert(pos);//确保传入地址不为空
	if (pos->next == NULL)//判断传入地址是否为最后一个结点的地址
	{
		return;
	}
	SListNode* after = pos->next;//待删除的结点
	pos->next = after->next;//让pos结点指向待删除的结点的下一个结点
	free(after);//释放结点
	after = NULL;//及时置空
}

//删除给定位置的值
void SListErasetCur(SListNode** pplist, SListNode* pos)
{
	assert(pos);//确保传入地址不为空
	if (pos == *pplist)//判断待删除的结点是否为第一个结点
	{
		*pplist = pos->next;//让头指针指向第二个结点
		free(pos);//释放第一个结点
		pos=NULL;//及时置空
	}
	else
	{
		SListNode* prev = *pplist;//接收头指针
		while (prev->next != pos)//找到待删除结点的前一个结点
		{
			prev = prev->next;
		}
		prev->next = pos->next;//让待删除的结点的前一个结点指向待删除结点的后一个结点
		free(pos);//释放待删除结点
		pos = NULL;//及时置空
	}
}

//查找数据
SListNode* SListFind(SListNode* plist, SLTDataType x)
{
	SListNode* cur = plist;//接收头指针
	while (cur != NULL)//遍历链表
	{
		if (cur->data == x)//判断结点是否为待找结点
			return cur;//返回目标结点的地址
		cur = cur->next;//指针后移
	}
	return NULL;//没有找到数据为x的结点
}

//修改数据
void SListModify(SListNode* pos, SLTDataType x)
{
	pos->data = x;//将结点的数据改为目标数据
}