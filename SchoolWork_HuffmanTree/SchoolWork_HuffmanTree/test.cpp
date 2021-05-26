#include "HTree.h"





p = m; cdlen = 0;
for (i = 1; i <= m; ++i) HT[i].weight = 0; //用作结点状态标志
while (p){
	if (HT[p].weight == 0){
		HT[p].weight = 1; //向左
		if (HT[p].lchild != 0) { p = HT[p].lchild; cd[cdlen++] = '0'; }
		else if (HT[p].rchild == 0){
			HC[p] = (char *)malloc((cdlen + 1)*sizeof(char));
			cd[cdlen] = '\0';
			strcpy(HC[p], cd];
		}
	}//if
	else if (HT[p].weight == 1){
		HT[p].weight = 2;  //向右
		if (HT[p].rchild != 0){
			p = HT[p].rchild; cd[cdlen++] = '1';
		}
		else{
			HT[p].weight = 0;
			p = HT[p].parent; --cdlen;
		}//else
	}//while
