#include "DStack.h"

//判断栈空
bool DblStackEmpty(DblStack* pds)
{
	assert(pds);//断言，判断指针有效性

	return pds->top[0] == -1 && pds->top[1] == pds->m;
}

//判断栈满
bool DblStackFull(DblStack* pds)
{
	assert(pds);//断言，判断指针有效性

	return pds->top[1] - pds->top[0] == 1;
}

//进栈
bool DblStackPush(DblStack* pds, int tag, SElemType x)
{
	assert(pds);//断言，判断指针有效性
	assert(DblStackFull(pds));//栈满，无法进栈


}

//出栈
SElemType DblStackPop(DblStack*pds, int tag)
{
	assert(pds);//断言，判断指针有效性
	assert(DblStackEmpty(pds));//栈空，无法出栈


}