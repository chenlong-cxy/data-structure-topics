#pragma once

#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <string>
#include <queue>
#include "UnionFindSet.h"
using namespace std;

//邻接矩阵
namespace Matrix {
	template<class V, class W, W MAX_W = INT_MAX, bool Direction = false>
	class Graph {
	public:
		//强制生成默认构造
		Graph() = default;
		//构造函数
		Graph(const V* vertexs, int n)
			:_vertexs(vertexs, vertexs + n) //设置顶点集合
			,_matrix(n, vector<int>(n, MAX_W)) { //开辟二维数组空间
			//建立顶点与下标的映射关系
			for (int i = 0; i < n; i++) {
				_vIndexMap[vertexs[i]] = i;
			}
		}
		//获取顶点对应的下标
		int getVertexIndex(const V& v) {
			auto iter = _vIndexMap.find(v);
			if (iter != _vIndexMap.end()) { //顶点存在
				return iter->second;
			}
			else { //顶点不存在
				cout << "debug: " << v << endl;
				throw invalid_argument("不存在的顶点");
				return -1;
			}
		}
		void _addEdge(int srci, int dsti, const W& weight) {
			_matrix[srci][dsti] = weight; //设置邻接矩阵中对应的值
			if (Direction == false) { //无向图
				_matrix[dsti][srci] = weight; //添加从目标顶点到源顶点的边
			}
		}
		//添加边
		void addEdge(const V& src, const V& dst, const W& weight) {
			int srci = getVertexIndex(src), dsti = getVertexIndex(dst); //获取源顶点和目标顶点的下标
			_addEdge(srci, dsti, weight);
		}
		//广度优先遍历
		void bfs(const V& src) {
			int srci = getVertexIndex(src); //起始顶点的下标
			queue<int> q; //队列
			vector<bool> visited(_vertexs.size(), false); //标记数组
			q.push(srci); //起始顶点入队列
			visited[srci] = true; //起始顶点标记为访问过

			while (!q.empty()) {
				int levelSize = q.size(); //一层一层的出
				for (int i = 0; i < levelSize; i++) {
					int front = q.front();
					q.pop();
					cout << _vertexs[front] << " ";
					for (int j = 0; j < _vertexs.size(); j++) { //将front顶点的邻接顶点带入队列
						if (_matrix[front][j] != MAX_W && visited[j] == false) { //是邻接顶点，并且没有被访问过
							q.push(j); //入队列
							visited[j] = true; //标记为访问过
						}
					}
				}
				cout << endl;
			}
			//while (!q.empty()) {
			//	int front = q.front();
			//	q.pop();
			//	cout << _vertexs[front] << " ";
			//	for (int i = 0; i < _vertexs.size(); i++) { //找出从front连接出去的顶点
			//		if (_matrix[front][i] != MAX_W && visited[i] == false) { //是邻接顶点，并且没有被访问过
			//			q.push(i); //入队列
			//			visited[i] = true; //标记为访问过
			//		}
			//	}
			//}
			//cout << endl;
		}
		//深度优先遍历（子函数）
		void _dfs(int srci, vector<bool>& visited) {
			cout << _vertexs[srci] << " "; //访问
			visited[srci] = true; //标记为访问过
			for (int i = 0; i < _vertexs.size(); i++) { //找从srci连接出去的顶点
				if (_matrix[srci][i] != MAX_W && visited[i] == false) { //是邻接顶点，并且没有被访问过
					_dfs(i, visited); //递归遍历
				}
			}
		}
		//深度优先遍历
		void dfs(const V& src) {
			int srci = getVertexIndex(src); //起始顶点的下标
			vector<bool> visited(_vertexs.size(), false); //标记数组
			_dfs(srci, visited); //递归遍历
			cout << endl;
		}
		void print() {
			int n = _vertexs.size();
			//打印顶点集合
			for (int i = 0; i < n; i++) {
				cout << "[" << i << "]->" << _vertexs[i] << endl;
			}
			cout << endl;

			//打印邻接矩阵
			//横下标
			cout << "  ";
			for (int i = 0; i < n; i++) {
				//cout << i << " ";
				printf("%4d", i);
			}
			cout << endl;
			for (int i = 0; i < n; i++) {
				cout << i << " "; //竖下标
				for (int j = 0; j < n; j++) {
					if (_matrix[i][j] == MAX_W) {
						//cout << "* ";
						printf("%4c", '*');
					}
					else {
						//cout << _matrix[i][j] << " ";
						printf("%4d", _matrix[i][j]);
					}
				}
				cout << endl;
			}
			cout << endl;
		}
		//边
		struct Edge {
			int _srci; //源顶点的下标
			int _dsti; //目标顶点的下标
			W _weight; //边的权值
			Edge(int srci, int dsti, const W& weight)
				:_srci(srci)
				, _dsti(dsti)
				, _weight(weight)
			{}
			bool operator>(const Edge& edge) const{
				return _weight > edge._weight;
			}
		};
		//获取当前图的最小生成树（Kruskal算法）
		W Kruskal(Graph<V, W, MAX_W, Direction>& minTree) {
			int n = _vertexs.size();
			//设置最小生成树的各个成员变量
			minTree._vertexs = _vertexs; //设置最小生成树的顶点集合
			minTree._vIndexMap = _vIndexMap; //设置最小生成树顶点与下标的映射
			minTree._matrix.resize(n, vector<W>(n, MAX_W)); //开辟最小生成树的二维数组空间

			priority_queue<Edge, vector<Edge>, greater<Edge>> minHeap; //优先级队列（小堆）
			//将所有边添加到优先级队列
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < i; j++) { //只遍历矩阵的一半，避免重复添加相同的边
					if (_matrix[i][j] != MAX_W)
						minHeap.push(Edge(i, j, _matrix[i][j]));
				}
			}
			UnionFindSet ufs(n); //n个顶点的并查集
			int count = 0; //已选边的数量
			W totalWeight = W(); //最小生成树的总权值
			while (!minHeap.empty() && count < n - 1) {
				//从优先级队列中获取一个权值最小的边
				Edge minEdge = minHeap.top();
				minHeap.pop();
				int srci = minEdge._srci, dsti = minEdge._dsti;
				W weight = minEdge._weight;

				if (!ufs.inSameSet(srci, dsti)) { //边的源顶点和目标顶点不在同一个集合
					minTree._addEdge(srci, dsti, weight); //在最小生成树中添加边
					ufs.unionSet(srci, dsti); //合并源顶点和目标顶点对应的集合
					count++;
					totalWeight += weight;
					cout << "选边: " << _vertexs[srci] << "->" << _vertexs[dsti] << ":" << weight << endl;
				}
				else { //边的源顶点和目标顶点在同一个集合，加入这条边会构成环
					cout << "成环: " << _vertexs[srci] << "->" << _vertexs[dsti] << ":" << weight << endl;
				}
			}
			if (count == n - 1) {
				cout << "构建最小生成树成功" << endl;
				return totalWeight;
			}
			else {
				cout << "无法构成最小生成树" << endl;
				return W();
			}
		}
		//获取当前图的最小生成树（Kruskal算法）
		//W Kruskal(Graph<V, W, MAX_W, Direction>& minTree) {
		//	int n = _vertexs.size();
		//	minTree._vertexs = _vertexs;
		//	minTree._vIndexMap = _vIndexMap;
		//	minTree._matrix.resize(n, vector<W>(n, MAX_W));

		//	vector<Edge> v;
		//	//将所有边添加到优先级队列（不要重复添加）
		//	for (int i = 0; i < n; i++) {
		//		for (int j = 0; j < i; j++) { //注意
		//			if (_matrix[i][j] != MAX_W)
		//				v.push_back(Edge(i, j, _matrix[i][j]));
		//		}
		//	}
		//	sort(v.begin(), v.end(), [](const Edge& e1, const Edge& e2)->bool {
		//		return e1._weight < e2._weight;
		//		});
		//	UnionFindSet ufs(n); //n个顶点的并查集
		//	int count = 0; //已选边的数量
		//	W totalWeight = W(); //最小生成树的总权值
		//	size_t index = 0;
		//	while (index < v.size() && count < n - 1) {
		//		Edge minEdge = v[index];
		//		int srci = minEdge._srci, dsti = minEdge._dsti;
		//		W weight = minEdge._weight;
		//		index++;
		//		if (!ufs.inSameSet(srci, dsti)) {
		//			minTree._addEdge(srci, dsti, weight); //在最小生成树中添加边
		//			ufs.unionSet(srci, dsti);
		//			count++;
		//			totalWeight += weight;
		//			cout << "选边: " << _vertexs[srci] << "->" << _vertexs[dsti] << ":" << weight << endl;
		//		}
		//		else {
		//			cout << "成环: " << _vertexs[srci] << "->" << _vertexs[dsti] << ":" << weight << endl;
		//		}
		//	}
		//	if (count == n - 1) {
		//		cout << "构建最小生成树成功" << endl;
		//		return totalWeight;
		//	}
		//	else {
		//		cout << "无法构成最小生成树" << endl;
		//		return W();
		//	}
		//}
		//获取当前图的最小生成树（Prim算法）
		W Prim(Graph<V, W, MAX_W, Direction>& minTree, const V& start) {
			int n = _vertexs.size();
			//设置最小生成树的各个成员变量
			minTree._vertexs = _vertexs; //设置最小生成树的顶点集合
			minTree._vIndexMap = _vIndexMap; //设置最小生成树顶点与下标的映射
			minTree._matrix.resize(n, vector<W>(n, MAX_W)); //开辟最小生成树的二维数组空间

			int starti = getVertexIndex(start); //获取起始顶点的下标
			vector<bool> forest(n, false);
			forest[starti] = true;
			priority_queue<Edge, vector<Edge>, greater<Edge>> minHeap; //优先级队列（小堆）
			
			//将从起始顶点连接出去的边加入优先级队列
			for (int i = 0; i < n; i++) {
				if (_matrix[starti][i] != MAX_W)
					minHeap.push(Edge(starti, i, _matrix[starti][i]));
			}

			int count = 0; //已选边的数量
			W totalWeight = W(); //最小生成树的总权值
			while (!minHeap.empty() && count < n - 1) {
				//从优先级队列中获取一个权值最小的边
				Edge minEdge = minHeap.top();
				minHeap.pop();
				int srci = minEdge._srci, dsti = minEdge._dsti;
				W weight = minEdge._weight;

				if (forest[dsti] == false) { //边的目标顶点还没有被加入到forest集合中
					//将从目标顶点连接出去的边加入优先级队列
					for (int i = 0; i < n; i++) {
						if (_matrix[dsti][i] != MAX_W && forest[i] == false) //加入的边的目标顶点不能在forest集合中
							minHeap.push(Edge(dsti, i, _matrix[dsti][i]));
					}
					minTree._addEdge(srci, dsti, weight); //在最小生成树中添加边
					forest[dsti] = true; //将边的目标顶点加入forest集合
					count++;
					totalWeight += weight;
					cout << "选边: " << _vertexs[srci] << "->" << _vertexs[dsti] << ":" << weight << endl;
				}
				else { //边的目标顶点已经在forest集合中，加入这条边会构成环
					cout << "成环: " << _vertexs[srci] << "->" << _vertexs[dsti] << ":" << weight << endl;
				}
			}
			if (count == n - 1) {
				cout << "构建最小生成树成功" << endl;
				return totalWeight;
			}
			else {
				cout << "无法构成最小生成树" << endl;
				return W();
			}
		}
		//获取单源最短路径（Dijkstra算法）
		void Dijkstra(const V& src, vector<W>& dist, vector<int>& parentPath) {
			int n = _vertexs.size();
			int srci = getVertexIndex(src); //获取源顶点的下标
			dist.resize(n, MAX_W); //源顶点到各个顶点的路径权值初始化为MAX_W
			parentPath.resize(n, -1); //各个顶点的前驱顶点初始化为-1

			dist[srci] = W(); //源顶点到源顶点的路径权值设置为权值的缺省值
			vector<bool> S(n, false); //已经确定最短路径的顶点集合
			for (int i = 0; i < n; i++) { //需要将Q集合中的n个顶点加入到S集合
				//从集合Q中选出一个路径权值最小的顶点
				W minW = MAX_W; //最小路径权值
				int u = -1;     //顶点的下标
				for (int j = 0; j < n; j++) {
					if (S[j] == false && dist[j] < minW) {
						u = j;
						minW = dist[j];
					}
				}
				S[u] = true; //将选出的顶点加入到S集合
				//对u连接出去的顶点进行松弛
				for (int v = 0; v < n; v++) {
					if (S[v] == false && _matrix[u][v] != MAX_W && dist[u] + _matrix[u][v] < dist[v]) { //松弛的顶点不能在S集合
						dist[v] = dist[u] + _matrix[u][v]; //松弛更新出更小的路径权值
						parentPath[v] = u; //更新路径的前驱顶点
					}
				}
			}
		}
		//获取单源最短路径（BellmanFord算法）
		bool BellmanFord(const char& src, vector<W>& dist, vector<int>& parentPath) {
			int n = _vertexs.size();
			int srci = getVertexIndex(src); //获取源顶点的下标
			dist.resize(n, MAX_W); //源顶点到各个顶点的路径权值初始化为MAX_W
			parentPath.resize(n, -1); //各个顶点的前驱顶点初始化为-1

			dist[srci] = W(); //源顶点到源顶点的路径权值设置为权值的缺省值
			for (int k = 0; k < n - 1; k++) { //最多更新n-1轮
				bool update = false; //记录本轮是否更新过
				for (int i = 0; i < n; i++) {
					for (int j = 0; j < n; j++) {
						if (_matrix[i][j] != MAX_W && dist[i] != MAX_W && dist[i] + _matrix[i][j] < dist[j]) {
							dist[j] = dist[i] + _matrix[i][j]; //松弛更新出更小的路径权值
							parentPath[j] = i; //更新路径的前驱顶点
							update = true;
						}
					}
				}
				if (update == false) { //本轮没有更新过，不必进行后续轮次的更新
					break;
				}
				else {
					cout << "更新第" << k << "次" << endl;
				}
			}
			//更新n-1轮后如果还能更新，则说明带有负权回路
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					if (_matrix[i][j] != MAX_W && dist[i] + _matrix[i][j] < dist[j]) {
						return false; //带有负权回路的图无法求出最短路径
					}
				}
			}
			return true;
		}
		//获取多源最短路径（FloydWarshall算法）
		void FloydWarshall(vector<vector<W>>& vvDist, vector<vector<int>>& vvParentPath) {
			int n = _vertexs.size();
			vvDist.resize(n, vector<W>(n, MAX_W)); //任意两个顶点直接的路径权值初始化为MAX_W
			vvParentPath.resize(n, vector<int>(n, -1)); //各个顶点的前驱顶点初始化为-1

			//根据邻接矩阵初始化直接相连的顶点
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					if (_matrix[i][j] != MAX_W) { //i->j有边
						vvDist[i][j] = _matrix[i][j]; //i->j的路径权值
						vvParentPath[i][j] = i; //i->j路径的前驱顶点为i
					}
					if (i == j) { //i->i
						vvDist[i][j] = W(); //i->i的路径权值设置为权值的缺省值
					}
				}
			}
			printDictAndParentPath(vvDist, vvParentPath);
			for (int k = 0; k < n; k++) { //依次取各个顶点作为i->j路径的中间顶点
				for (int i = 0; i < n; i++) {
					for (int j = 0; j < n; j++) {
						if (vvDist[i][k] != MAX_W && vvDist[k][j] != MAX_W &&
							vvDist[i][k] + vvDist[k][j] < vvDist[i][j]) { //存在i->k和k->j的路径，并且这两条路径的权值之和小于当前i->j路径的权值
							vvDist[i][j] = vvDist[i][k] + vvDist[k][j]; //松弛更新出更小的路径权值
							vvParentPath[i][j] = vvParentPath[k][j]; //更小路径的前驱顶点
						}
					}
				}
				printDictAndParentPath(vvDist, vvParentPath);
			}
		}
		void printDictAndParentPath(const vector<vector<W>>& vvDist, const vector<vector<int>>& vvParentPath) {
			int n = _vertexs.size();
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					if (vvDist[i][j] != MAX_W) {
						printf("%4d", vvDist[i][j]);
					}
					else {
						printf("   *");
					}
				}
				cout << endl;
			}
			cout << endl;
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					if (vvParentPath[i][j] != -1) {
						printf("%4d", vvParentPath[i][j]);
					}
					else {
						printf("   *");
					}
				}
				cout << endl;
			}
			cout << "--------------------------------------" << endl;
		}
		//打印最短路径及路径权值
		void printShortPath(const V& src, const vector<W>& dist, const vector<int>& parentPath) {
			int n = _vertexs.size();
			int srci = getVertexIndex(src); //获取源顶点的下标
			for (int i = 0; i < n; i++) {
				vector<int> path;
				int cur = i;
				while (cur != -1) { //源顶点的前驱顶点为-1
					path.push_back(cur);
					cur = parentPath[cur];
				}
				reverse(path.begin(), path.end()); //逆置
				for (int j = 0; j < path.size(); j++) {
					cout << _vertexs[path[j]] << "->";
				}
				cout << "路径权值: " << dist[i] << "" << endl;
			}
		}
	private:
		vector<V> _vertexs;               //顶点集合
		unordered_map<V, int> _vIndexMap; //顶点映射下标
		vector<vector<W>> _matrix;        //邻接矩阵
	};
	void testGraph() {
		Graph<char, int, INT_MAX, true> g("ABCD", 4);
		g.addEdge('A', 'B', 1);
		g.addEdge('A', 'D', 4);
		g.addEdge('B', 'D', 2);
		g.addEdge('B', 'C', 9);
		g.addEdge('C', 'D', 8);
		g.addEdge('C', 'B', 5);
		g.addEdge('C', 'A', 3);
		g.addEdge('D', 'C', 6);

		g.print();
	}
	void testBfsDfs() {
		//string a[] = { "张三","李四","王五","赵六","周七" ,"吴八"};
		//Graph<string, int> g(a, 6);
		//g.addEdge("张三", "李四", 100);
		//g.addEdge("张三", "王五", 200);
		//g.addEdge("王五", "赵六", 30);
		//g.addEdge("王五", "周七", 30);
		//g.addEdge("李四", "吴八", 50);

		//g.print();
		//g.bfs("张三");
		//g.dfs("张三");

		Graph<char, int> g("ABCDEFGHI", 9);
		g.addEdge('A', 'B', 1);
		g.addEdge('A', 'C', 1);
		g.addEdge('A', 'D', 1);
		g.addEdge('B', 'E', 1);
		g.addEdge('B', 'C', 1);
		g.addEdge('D', 'F', 1);
		g.addEdge('C', 'F', 1);
		g.addEdge('F', 'H', 1);
		g.addEdge('H', 'I', 1);
		g.addEdge('E', 'G', 1);

		g.print();
		g.bfs('A');
		g.dfs('A');
	}
	void testMinTree() {
		Graph<char, int> g("abcdefghi", 9);
		g.addEdge('a', 'b', 4);
		g.addEdge('a', 'h', 8);
		g.addEdge('b', 'c', 8);
		g.addEdge('b', 'h', 11);
		g.addEdge('c', 'i', 2);
		g.addEdge('c', 'f', 4);
		g.addEdge('c', 'd', 7);
		g.addEdge('d', 'f', 14);
		g.addEdge('d', 'e', 9);
		g.addEdge('e', 'f', 10);
		g.addEdge('f', 'g', 2);
		g.addEdge('g', 'h', 1);
		g.addEdge('g', 'i', 6);
		g.addEdge('h', 'i', 7);


		//Graph<char, int> minTree;
		//cout << g.Kruskal(minTree) << endl;
		//minTree.print();

		Graph<char, int> minTree;
		cout << g.Prim(minTree, 'a') << endl;
		minTree.print();

		//for (int i = 0; i < 9; i++) {
		//	Graph<char, int> minTree;
		//	cout << g.Prim(minTree, 'a'+i) << endl;
		//}
	}
	void testDijkstra() {
		Graph<char, int, INT_MAX, true> g("stxyz", 5);
		g.addEdge('s', 't', 10);
		g.addEdge('s', 'y', 5);
		g.addEdge('t', 'y', 2);
		g.addEdge('t', 'x', 1);
		g.addEdge('x', 'z', 4);
		g.addEdge('y', 't', 3);
		g.addEdge('y', 'x', 9);
		g.addEdge('y', 'z', 2);
		g.addEdge('z', 's', 7);
		g.addEdge('z', 'x', 6);
		vector<int> dist, parentPath;
		g.Dijkstra('s', dist, parentPath);
		g.printShortPath('s', dist, parentPath);

		////没有找到带负权的最短路径
		//Graph<char, int, INT_MAX, true> g("styx", 4);
		//g.addEdge('s', 't', 10);
		//g.addEdge('s', 'y', 5);
		//g.addEdge('t', 'y', -7);
		//g.addEdge('y', 'x', 3);
		//vector<int> dist, parentPath;
		//g.Dijkstra('s', dist, parentPath);
		//g.printShortPath('s', dist, parentPath);
	}
	void testBellmanFord() {
		//Graph<char, int, INT_MAX, true> g("stxyz", 5);
		//g.addEdge('s', 't', 6);
		//g.addEdge('s', 'y', 7);
		//g.addEdge('t', 'x', 5);
		//g.addEdge('t', 'y', 8);
		//g.addEdge('t', 'z', -4);
		//g.addEdge('x', 't', -2);
		//g.addEdge('y', 'x', -3);
		//g.addEdge('y', 'z', 9);
		//g.addEdge('z', 's', 2);
		//g.addEdge('z', 'x', 7);
		////g.addEdge('z', 'x', -7);

		//vector<int> dist, parentPath;
		//if (g.BellmanFord('s', dist, parentPath)) {
		//	g.printShortPath('s', dist, parentPath);
		//}
		//else {
		//	cout << "存在负权回路" << endl;
		//}

		Graph<char, int, INT_MAX, true> g("ABCDE", 5);
		g.addEdge('B', 'A', 1);
		g.addEdge('C', 'B', 1);
		g.addEdge('D', 'C', 1);
		g.addEdge('E', 'D', 1);
		vector<int> dist, parentPath;
		if (g.BellmanFord('E', dist, parentPath)) {
			g.printShortPath('E', dist, parentPath);
		}
		else {
			cout << "存在负权回路" << endl;
		}
	}
	void testFloydWarshall() {
		Graph<char, int, INT_MAX, true> g("12345", 5);
		g.addEdge('1', '2', 3);
		g.addEdge('1', '3', 8);
		g.addEdge('1', '5', -4);
		g.addEdge('2', '5', 7);
		g.addEdge('2', '4', 1);
		g.addEdge('3', '2', 4);
		g.addEdge('4', '1', 2);
		g.addEdge('4', '3', -5);
		g.addEdge('5', '4', 6);

		vector<vector<int>> vvDist, vvParentPath;
		g.FloydWarshall(vvDist, vvParentPath);

		const string str("12345");
		for (int i = 0; i < vvDist.size(); i++) {
			g.printShortPath(str[i], vvDist[i], vvParentPath[i]);
			cout << endl;
		}
	}
}

//邻接表
namespace LinkTable {
	template<class W>
	//链表结点定义
	struct Edge {
		//int _srci;    //源顶点的下标（可选）
		int _dsti;      //目标顶点的下标
		W _weight;      //边的权值
		Edge<W>* _next; //连接指针

		Edge(int dsti, const W& weight)
			:_dsti(dsti)
			,_weight(weight)
			,_next(nullptr)
		{}
	};
	template<class V, class W, bool Direction = false>
	class Graph {
		typedef Edge<W> Edge;
	public:
		//构造函数
		Graph(const V* vertexs, int n)
			:_vertexs(vertexs, vertexs + n) //设置顶点集合
			, _linkTable(n, nullptr) { //开辟邻接表的空间
			//建立顶点与下标的映射关系
			for (int i = 0; i < n; i++) {
				_vIndexMap[vertexs[i]] = i;
			}
		}
		//获取顶点对应的下标
		int getVertexIndex(const V& v) {
			auto iter = _vIndexMap.find(v);
			if (iter != _vIndexMap.end()) { //顶点存在
				return iter->second;
			}
			else { //顶点不存在
				throw invalid_argument("不存在的顶点");
				return -1;
			}
		}
		//添加边
		void addEdge(const V& src, const V& dst, const W& weight) {
			int srci = getVertexIndex(src), dsti = getVertexIndex(dst); //获取源顶点和目标顶点的下标

			//添加从源顶点到目标顶点的边
			Edge* sdEdge = new Edge(dsti, weight);
			sdEdge->_next = _linkTable[srci];
			_linkTable[srci] = sdEdge;

			if (Direction == false) { //无向图
				//添加从目标顶点到源顶点的边
				Edge* dsEdge = new Edge(srci, weight);
				dsEdge->_next = _linkTable[dsti];
				_linkTable[dsti] = dsEdge;
			}
		}
		//打印顶点集合和邻接表
		void print() {
			int n = _vertexs.size();
			//打印顶点集合
			for (int i = 0; i < n; i++) {
				cout << "[" << i << "]->" << _vertexs[i] << " ";
			}
			cout << endl << endl;

			//打印邻接表
			for (int i = 0; i < n; i++) {
				Edge* cur = _linkTable[i];
				cout << "[" << i << ":" << _vertexs[i] << "]->";
				while (cur) {
					cout << "[" << cur->_dsti << ":" << _vertexs[cur->_dsti] << ":" << cur->_weight << "]->";
					cur = cur->_next;
				}
				cout << "nullptr" << endl;
			}
		}
	private:
		vector<V> _vertexs;               //顶点集合
		unordered_map<V, int> _vIndexMap; //顶点映射下标
		vector<Edge*> _linkTable;         //邻接表（出边表）
	};
	void testGraph() {
		string a[] = { "张三","李四","王五","赵六" };
		Graph<string, int, true> g(a, 4);
		g.addEdge("张三", "李四", 100);
		g.addEdge("张三", "王五", 200);
		g.addEdge("王五", "赵六", 30);

		g.print();
	}
}
