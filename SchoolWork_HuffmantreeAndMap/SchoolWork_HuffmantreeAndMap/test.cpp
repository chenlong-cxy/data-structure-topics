//#define MAXVALUE 32767
//#include <stdio.h>
//
//typedef struct{						//哈夫曼树结构体
//	int weight;                       //输入权值
//	int parent, lchild, rchild;        //双亲节点，左孩子，右孩子
//}HNodeType;
//typedef struct{					//哈夫曼编码结构体
//	int bit[8];					//存放当前结点的哈夫曼编码
//	int start;						//bit[start]-bit[8[存放哈夫曼编码
//}HCodeType;
//HNodeType HuffNode[8];		//定义全局变量数组HuffNode存放哈夫曼树
//HCodeType HuffCode[8];		//定义全局变量数组HuffCode存放哈夫曼编码
//int n;							//定义全局变量n表示叶子结点个数
//void	CreateHuffTree(void);			//构造哈夫曼树
//void	PrintHuffTree(void);			//输出哈夫曼树
//void	CreateHuffCode(void);			//构造哈夫曼编码
//void	PrintHuffcode(void);			//输出每个叶子结点的哈夫曼编码
//
////构造哈夫曼树
//void CreateHuffTree(void)
//{		
//	int i, j, a, b, x1, x2;
//	scanf("%d", &n);        //输入叶子节点个数
//	for (i = 1; i<2 * n; i++) //HuffNode 初始化 
//	{
//		HuffNode[i].weight = 0;
//		HuffNode[i].parent = -1;
//		HuffNode[i].lchild = -1;
//		HuffNode[i].rchild = -1;
//	}
//	printf("输入%d个节点的权值\n", n);
//	for (i = 1; i <= n; i++)
//		scanf("%d", &HuffNode[i].weight);//输入N个叶子节点的权值
//	for (i = 1; i<n; i++){   //构造哈夫曼树 
//		a = MAXVALUE;
//		b = MAXVALUE;
//		x1 = 0;
//		x2 = 0;
//		for (j = 1; j<n + i; j++){        //选取最小和次小两个权值
//			if (HuffNode[j].parent == -1 && HuffNode[j].weight<a){
//				b = a;
//				x2 = x1;
//				a = HuffNode[j].weight;
//				x1 = j;
//			}
//			else
//			if (HuffNode[j].parent == -1 && HuffNode[j].weight<b){
//				b = HuffNode[j].weight;
//				x2 = j;
//			}
//		}
//		HuffNode[x1].parent = n + i;
//		HuffNode[x2].parent = n + i;
//		HuffNode[n + i].weight = HuffNode[x1].weight + HuffNode[x2].weight;
//		HuffNode[n + i].lchild = x1;
//		HuffNode[n + i].rchild = x2;
//	}
//}
//
////输出哈夫曼树
//void PrintHuffTree()
//{			
//	int i;
//	printf("\n哈夫曼树各项数据如下表所示:\n");
//	printf("        结点i weight parent    lchid    rchild\n");
//	for (i = 1; i<2 * n; i++)
//		printf("\t%d\t%d\t%d\t%d\t%d\n", i, HuffNode[i].weight, HuffNode[i].parent,
//		HuffNode[i].lchild, HuffNode[i].rchild);
//	printf("\n");
//}
//
////构造哈夫曼编码
//void CreateHuffCode(void)
//{	
//	HCodeType cd;
//	int i, j, c, p;
//
//	for (i = 1; i <= n; i++){
//		cd.start = n;
//		c = i;
//		p = HuffNode[c].parent;
//		while (p != -1){
//			if (HuffNode[p].lchild == c)
//				cd.bit[cd.start] = 0;
//			else
//				cd.bit[cd.start] = 1;
//			cd.start--;
//			c = p;
//			p = HuffNode[c].parent;
//		}
//		for (j = cd.start + 1; j <= n; j++)
//			HuffCode[i].bit[j] = cd.bit[j];
//		HuffCode[i].start = cd.start;
//	}
//}
//
////输出每个叶子结点的哈夫曼编码
//void PrintHuffcode(void)
//{		
//	int i, j;
//	printf("每个叶子结点的哈夫曼编码为:\n");
//	for (i = 1; i <= n; i++)
//	{
//		for (j = HuffCode[i].start + 1; j <= n; j++)
//			printf("%d", HuffCode[i].bit[j]);
//		printf("\n");
//	}
//}
//
////主函数
//int main(void){
//	printf("输入叶子节点个数\n");
//	CreateHuffTree();	//构造哈夫曼树
//	PrintHuffTree();	//输出哈夫曼树
//	CreateHuffCode();	//构造哈夫曼编码
//	PrintHuffcode();	//输出每个叶子结点的哈夫曼编码
//	return 0;
//}


#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#define MAX 100
#define isLetter(a)  ((((a)>='a')&&((a)<='z')) || (((a)>='A')&&((a)<='Z')))
#define LENGTH(a)  (sizeof(a)/sizeof(a[0]))

// 邻接矩阵
typedef struct _graph
{
	char vexs[MAX];       // 顶点集合
	int vexnum;           // 顶点数
	int edgnum;           // 边数
	int matrix[MAX][MAX]; // 邻接矩阵
}Graph, *PGraph;

/*
* 返回ch在matrix矩阵中的位置
*/
static int get_position(Graph g, char ch)
{
	int i;
	for (i = 0; i<g.vexnum; i++)
	if (g.vexs[i] == ch)
		return i;
	return -1;
}

/*
* 读取一个输入字符
*/
static char read_char()
{
	char ch;

	do {
		ch = getchar();
	} while (!isLetter(ch));

	return ch;
}

/*
* 创建图(自己输入)
*/
Graph* create_graph()
{
	char c1, c2;
	int v, e;
	int i, p1, p2;
	Graph* pG;

	// 输入"顶点数"和"边数"
	printf("input vertex number: ");
	scanf("%d", &v);
	printf("input edge number: ");
	scanf("%d", &e);
	if (v < 1 || e < 1 || (e >(v * (v - 1))))
	{
		printf("input error: invalid parameters!\n");
		return NULL;
	}

	if ((pG = (Graph*)malloc(sizeof(Graph))) == NULL)
		return NULL;
	memset(pG, 0, sizeof(Graph));

	// 初始化"顶点数"和"边数"
	pG->vexnum = v;
	pG->edgnum = e;
	// 初始化"顶点"
	for (i = 0; i < pG->vexnum; i++)
	{
		printf("vertex(%d): ", i);
		pG->vexs[i] = read_char();
	}

	// 初始化"边"
	for (i = 0; i < pG->edgnum; i++)
	{
		// 读取边的起始顶点和结束顶点
		printf("edge(%d):", i);
		c1 = read_char();
		c2 = read_char();

		p1 = get_position(*pG, c1);
		p2 = get_position(*pG, c2);
		if (p1 == -1 || p2 == -1)
		{
			printf("input error: invalid edge!\n");
			free(pG);
			return NULL;
		}

		pG->matrix[p1][p2] = 1;
		pG->matrix[p2][p1] = 1;
	}

	return pG;
}

/*
* 创建图(用已提供的矩阵)
*/
Graph* create_example_graph()
{
	char vexs[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G' };
	char edges[][2] = {
		{ 'A', 'C' },
		{ 'A', 'D' },
		{ 'A', 'F' },
		{ 'B', 'C' },
		{ 'C', 'D' },
		{ 'E', 'G' },
		{ 'F', 'G' } };
	int vlen = LENGTH(vexs);
	int elen = LENGTH(edges);
	int i, p1, p2;
	Graph* pG;

	// 输入"顶点数"和"边数"
	if ((pG = (Graph*)malloc(sizeof(Graph))) == NULL)
		return NULL;
	memset(pG, 0, sizeof(Graph));

	// 初始化"顶点数"和"边数"
	pG->vexnum = vlen;
	pG->edgnum = elen;
	// 初始化"顶点"
	for (i = 0; i < pG->vexnum; i++)
	{
		pG->vexs[i] = vexs[i];
	}

	// 初始化"边"
	for (i = 0; i < pG->edgnum; i++)
	{
		// 读取边的起始顶点和结束顶点
		p1 = get_position(*pG, edges[i][0]);
		p2 = get_position(*pG, edges[i][1]);

		pG->matrix[p1][p2] = 1;
		pG->matrix[p2][p1] = 1;
	}

	return pG;
}

/*
* 返回顶点v的第一个邻接顶点的索引，失败则返回-1
*/
static int first_vertex(Graph G, int v)
{
	int i;

	if (v<0 || v>(G.vexnum - 1))
		return -1;

	for (i = 0; i < G.vexnum; i++)
	if (G.matrix[v][i] == 1)
		return i;

	return -1;
}

/*
* 返回顶点v相对于w的下一个邻接顶点的索引，失败则返回-1
*/
static int next_vertix(Graph G, int v, int w)
{
	int i;

	if (v<0 || v>(G.vexnum - 1) || w<0 || w>(G.vexnum - 1))
		return -1;

	for (i = w + 1; i < G.vexnum; i++)
	if (G.matrix[v][i] == 1)
		return i;

	return -1;
}

/*
* 深度优先搜索遍历图的递归实现
*/
static void DFS(Graph G, int i, int *visited)
{
	int w;

	visited[i] = 1;
	printf("%c ", G.vexs[i]);
	// 遍历该顶点的所有邻接顶点。若是没有访问过，那么继续往下走
	for (w = first_vertex(G, i); w >= 0; w = next_vertix(G, i, w))
	{
		if (!visited[w])
			DFS(G, w, visited);
	}

}

/*
* 深度优先搜索遍历图
*/
void DFSTraverse(Graph G)
{
	int i;
	int visited[MAX];       // 顶点访问标记

	// 初始化所有顶点都没有被访问
	for (i = 0; i < G.vexnum; i++)
		visited[i] = 0;

	printf("DFS: ");
	for (i = 0; i < G.vexnum; i++)
	{
		//printf("\n== LOOP(%d)\n", i);
		if (!visited[i])
			DFS(G, i, visited);
	}
	printf("\n");
}

/*
* 广度优先搜索（类似于树的层次遍历）
*/
void BFS(Graph G)
{
	int head = 0;
	int rear = 0;
	int queue[MAX];     // 辅组队列
	int visited[MAX];   // 顶点访问标记
	int i, j, k;

	for (i = 0; i < G.vexnum; i++)
		visited[i] = 0;

	printf("BFS: ");
	for (i = 0; i < G.vexnum; i++)
	{
		if (!visited[i])
		{
			visited[i] = 1;
			printf("%c ", G.vexs[i]);
			queue[rear++] = i;  // 入队列
		}
		while (head != rear)
		{
			j = queue[head++];  // 出队列
			for (k = first_vertex(G, j); k >= 0; k = next_vertix(G, j, k)) //k是为访问的邻接顶点
			{
				if (!visited[k])
				{
					visited[k] = 1;
					printf("%c ", G.vexs[k]);
					queue[rear++] = k;
				}
			}
		}
	}
	printf("\n");
}

/*
* 打印矩阵队列图
*/
void print_graph(Graph G)
{
	int i, j;

	printf("Martix Graph:\n");
	for (i = 0; i < G.vexnum; i++)
	{
		for (j = 0; j < G.vexnum; j++)
			printf("%d ", G.matrix[i][j]);
		printf("\n");
	}
}

void main()
{
	Graph* pG;

	// 自定义"图"(输入矩阵队列)
	//pG = create_graph();
	// 采用已有的"图"
	pG = create_example_graph();

	print_graph(*pG);       // 打印图
	DFSTraverse(*pG);       // 深度优先遍历
	BFS(*pG);               // 广度优先遍历
}