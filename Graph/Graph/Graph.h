#pragma once

#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <string>
#include <queue>
#include "UnionFindSet.h"
using namespace std;

//�ڽӾ���
namespace Matrix {
	template<class V, class W, W MAX_W = INT_MAX, bool Direction = false>
	class Graph {
	public:
		//ǿ������Ĭ�Ϲ���
		Graph() = default;
		//���캯��
		Graph(const V* vertexs, int n)
			:_vertexs(vertexs, vertexs + n) //���ö��㼯��
			,_matrix(n, vector<int>(n, MAX_W)) { //���ٶ�ά����ռ�
			//�����������±��ӳ���ϵ
			for (int i = 0; i < n; i++) {
				_vIndexMap[vertexs[i]] = i;
			}
		}
		//��ȡ�����Ӧ���±�
		int getVertexIndex(const V& v) {
			auto iter = _vIndexMap.find(v);
			if (iter != _vIndexMap.end()) { //�������
				return iter->second;
			}
			else { //���㲻����
				throw invalid_argument("�����ڵĶ���");
				return -1;
			}
		}
		void _addEdge(int srci, int dsti, const W& weight) {
			_matrix[srci][dsti] = weight; //�����ڽӾ����ж�Ӧ��ֵ
			if (Direction == false) { //����ͼ
				_matrix[dsti][srci] = weight; //��Ӵ�Ŀ�궥�㵽Դ����ı�
			}
		}
		//��ӱ�
		void addEdge(const V& src, const V& dst, const W& weight) {
			int srci = getVertexIndex(src), dsti = getVertexIndex(dst); //��ȡԴ�����Ŀ�궥����±�
			_addEdge(srci, dsti, weight);
		}
		//������ȱ���
		void bfs(const V& src) {
			int srci = getVertexIndex(src); //��ʼ������±�
			queue<int> q; //����
			vector<bool> visited(_vertexs.size(), false); //�������
			q.push(srci); //��ʼ���������
			visited[srci] = true; //��ʼ������Ϊ���ʹ�

			while (!q.empty()) {
				int levelSize = q.size(); //һ��һ��ĳ�
				for (int i = 0; i < levelSize; i++) {
					int front = q.front();
					q.pop();
					cout << _vertexs[front] << " ";
					for (int j = 0; j < _vertexs.size(); j++) { //��front������ڽӶ���������
						if (_matrix[front][j] != MAX_W && visited[j] == false) { //���ڽӶ��㣬����û�б����ʹ�
							q.push(j); //�����
							visited[j] = true; //���Ϊ���ʹ�
						}
					}
				}
				cout << endl;
			}
			//while (!q.empty()) {
			//	int front = q.front();
			//	q.pop();
			//	cout << _vertexs[front] << " ";
			//	for (int i = 0; i < _vertexs.size(); i++) { //�ҳ���front���ӳ�ȥ�Ķ���
			//		if (_matrix[front][i] != MAX_W && visited[i] == false) { //���ڽӶ��㣬����û�б����ʹ�
			//			q.push(i); //�����
			//			visited[i] = true; //���Ϊ���ʹ�
			//		}
			//	}
			//}
			//cout << endl;
		}
		//������ȱ������Ӻ�����
		void _dfs(int srci, vector<bool>& visited) {
			cout << _vertexs[srci] << " "; //����
			visited[srci] = true; //���Ϊ���ʹ�
			for (int i = 0; i < _vertexs.size(); i++) { //�Ҵ�srci���ӳ�ȥ�Ķ���
				if (_matrix[srci][i] != MAX_W && visited[i] == false) { //���ڽӶ��㣬����û�б����ʹ�
					_dfs(i, visited); //�ݹ����
				}
			}
		}
		//������ȱ���
		void dfs(const V& src) {
			int srci = getVertexIndex(src); //��ʼ������±�
			vector<bool> visited(_vertexs.size(), false); //�������
			_dfs(srci, visited); //�ݹ����
			cout << endl;
		}
		void print() {
			int n = _vertexs.size();
			//��ӡ���㼯��
			for (int i = 0; i < n; i++) {
				cout << "[" << i << "]->" << _vertexs[i] << endl;
			}
			cout << endl;

			//��ӡ�ڽӾ���
			//���±�
			cout << "  ";
			for (int i = 0; i < n; i++) {
				//cout << i << " ";
				printf("%4d", i);
			}
			cout << endl;
			for (int i = 0; i < n; i++) {
				cout << i << " "; //���±�
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
		//��
		struct Edge {
			int _srci; //Դ������±�
			int _dsti; //Ŀ�궥����±�
			W _weight; //�ߵ�Ȩֵ
			Edge(int srci, int dsti, const W& weight)
				:_srci(srci)
				, _dsti(dsti)
				, _weight(weight)
			{}
			bool operator>(const Edge& edge) const{
				return _weight > edge._weight;
			}
		};
		//��ȡ��ǰͼ����С��������Kruskal�㷨��
		W Kruskal(Graph<V, W, MAX_W, Direction>& minTree) {
			int n = _vertexs.size();
			//������С�������ĸ�����Ա����
			minTree._vertexs = _vertexs; //������С�������Ķ��㼯��
			minTree._vIndexMap = _vIndexMap; //������С�������������±��ӳ��
			minTree._matrix.resize(n, vector<W>(n, MAX_W)); //������С�������Ķ�ά����ռ�

			priority_queue<Edge, vector<Edge>, greater<Edge>> minHeap; //���ȼ����У�С�ѣ�
			//�����б���ӵ����ȼ�����
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < i; j++) { //ֻ���������һ�룬�����ظ������ͬ�ı�
					if (_matrix[i][j] != MAX_W)
						minHeap.push(Edge(i, j, _matrix[i][j]));
				}
			}
			UnionFindSet ufs(n); //n������Ĳ��鼯
			int count = 0; //��ѡ�ߵ�����
			W totalWeight = W(); //��С����������Ȩֵ
			while (!minHeap.empty() && count < n - 1) {
				//�����ȼ������л�ȡһ��Ȩֵ��С�ı�
				Edge minEdge = minHeap.top();
				minHeap.pop();
				int srci = minEdge._srci, dsti = minEdge._dsti;
				W weight = minEdge._weight;

				if (!ufs.inSameSet(srci, dsti)) { //�ߵ�Դ�����Ŀ�궥�㲻��ͬһ������
					minTree._addEdge(srci, dsti, weight); //����С����������ӱ�
					ufs.unionSet(srci, dsti); //�ϲ�Դ�����Ŀ�궥���Ӧ�ļ���
					count++;
					totalWeight += weight;
					cout << "ѡ��: " << _vertexs[srci] << "->" << _vertexs[dsti] << ":" << weight << endl;
				}
				else { //�ߵ�Դ�����Ŀ�궥����ͬһ�����ϣ����������߻ṹ�ɻ�
					cout << "�ɻ�: " << _vertexs[srci] << "->" << _vertexs[dsti] << ":" << weight << endl;
				}
			}
			if (count == n - 1) {
				cout << "������С�������ɹ�" << endl;
				return totalWeight;
			}
			else {
				cout << "�޷�������С������" << endl;
				return W();
			}
		}
		//��ȡ��ǰͼ����С��������Kruskal�㷨��
		//W Kruskal(Graph<V, W, MAX_W, Direction>& minTree) {
		//	int n = _vertexs.size();
		//	minTree._vertexs = _vertexs;
		//	minTree._vIndexMap = _vIndexMap;
		//	minTree._matrix.resize(n, vector<W>(n, MAX_W));

		//	vector<Edge> v;
		//	//�����б���ӵ����ȼ����У���Ҫ�ظ���ӣ�
		//	for (int i = 0; i < n; i++) {
		//		for (int j = 0; j < i; j++) { //ע��
		//			if (_matrix[i][j] != MAX_W)
		//				v.push_back(Edge(i, j, _matrix[i][j]));
		//		}
		//	}
		//	sort(v.begin(), v.end(), [](const Edge& e1, const Edge& e2)->bool {
		//		return e1._weight < e2._weight;
		//		});
		//	UnionFindSet ufs(n); //n������Ĳ��鼯
		//	int count = 0; //��ѡ�ߵ�����
		//	W totalWeight = W(); //��С����������Ȩֵ
		//	size_t index = 0;
		//	while (index < v.size() && count < n - 1) {
		//		Edge minEdge = v[index];
		//		int srci = minEdge._srci, dsti = minEdge._dsti;
		//		W weight = minEdge._weight;
		//		index++;
		//		if (!ufs.inSameSet(srci, dsti)) {
		//			minTree._addEdge(srci, dsti, weight); //����С����������ӱ�
		//			ufs.unionSet(srci, dsti);
		//			count++;
		//			totalWeight += weight;
		//			cout << "ѡ��: " << _vertexs[srci] << "->" << _vertexs[dsti] << ":" << weight << endl;
		//		}
		//		else {
		//			cout << "�ɻ�: " << _vertexs[srci] << "->" << _vertexs[dsti] << ":" << weight << endl;
		//		}
		//	}
		//	if (count == n - 1) {
		//		cout << "������С�������ɹ�" << endl;
		//		return totalWeight;
		//	}
		//	else {
		//		cout << "�޷�������С������" << endl;
		//		return W();
		//	}
		//}
		//��ȡ��ǰͼ����С��������Prim�㷨��
		W Prim(Graph<V, W, MAX_W, Direction>& minTree, const V& start) {
			int n = _vertexs.size();
			//������С�������ĸ�����Ա����
			minTree._vertexs = _vertexs; //������С�������Ķ��㼯��
			minTree._vIndexMap = _vIndexMap; //������С�������������±��ӳ��
			minTree._matrix.resize(n, vector<W>(n, MAX_W)); //������С�������Ķ�ά����ռ�

			int starti = getVertexIndex(start); //��ȡ��ʼ������±�
			vector<bool> forest(n, false);
			forest[starti] = true;
			priority_queue<Edge, vector<Edge>, greater<Edge>> minHeap; //���ȼ����У�С�ѣ�
			
			//������ʼ�������ӳ�ȥ�ı߼������ȼ�����
			for (int i = 0; i < n; i++) {
				if (_matrix[starti][i] != MAX_W)
					minHeap.push(Edge(starti, i, _matrix[starti][i]));
			}

			int count = 0; //��ѡ�ߵ�����
			W totalWeight = W(); //��С����������Ȩֵ
			while (!minHeap.empty() && count < n - 1) {
				//�����ȼ������л�ȡһ��Ȩֵ��С�ı�
				Edge minEdge = minHeap.top();
				minHeap.pop();
				int srci = minEdge._srci, dsti = minEdge._dsti;
				W weight = minEdge._weight;

				if (forest[dsti] == false) { //�ߵ�Ŀ�궥�㻹û�б����뵽forest������
					//����Ŀ�궥�����ӳ�ȥ�ı߼������ȼ�����
					for (int i = 0; i < n; i++) {
						if (_matrix[dsti][i] != MAX_W && forest[i] == false) //����ıߵ�Ŀ�궥�㲻����forest������
							minHeap.push(Edge(dsti, i, _matrix[dsti][i]));
					}
					minTree._addEdge(srci, dsti, weight); //����С����������ӱ�
					forest[dsti] = true; //���ߵ�Ŀ�궥�����forest����
					count++;
					totalWeight += weight;
					cout << "ѡ��: " << _vertexs[srci] << "->" << _vertexs[dsti] << ":" << weight << endl;
				}
				else { //�ߵ�Ŀ�궥���Ѿ���forest�����У����������߻ṹ�ɻ�
					cout << "�ɻ�: " << _vertexs[srci] << "->" << _vertexs[dsti] << ":" << weight << endl;
				}
			}
			if (count == n - 1) {
				cout << "������С�������ɹ�" << endl;
				return totalWeight;
			}
			else {
				cout << "�޷�������С������" << endl;
				return W();
			}
		}
		void Dijkstra(const V& src, vector<W>& dict, vector<int>& parentPath) {
			int n = _vertexs.size();
			int srci = getVertexIndex(src); //��ȡԴ����ı��
			dict.resize(n, MAX_W); //Դ���㵽���������·��Ȩֵ�ܺͳ�ʼ��Ϊ�����
			parentPath.resize(n, -1); //�����������·������һ������ı�ų�ʼ��Ϊ-1
			dict[srci] = W(); //Դ���㵽Դ�����·��Ȩֵ�ܺ�ΪȨֵ��ȱʡֵ
			vector<bool> S(n, false); //�Ѿ�ȷ�����·���Ķ���
			for (int i = 0; i < n; i++) { //��Ҫ��Q������ѡ��n�����㵽S����
				W minW = MAX_W;
				int u = -1;
				//�Ӽ���Q��ѡ��һ��·��Ȩֵ�ܺ���С�Ķ���
				for (int j = 0; j < n; j++) {
					if (S[j] == false && dict[j] < minW) {
						u = j;
						minW = dict[j];
					}
				}
				S[u] = true;
				//�ɳ�
				for (int v = 0; v < n; v++) {
					if (S[v] == false && _matrix[u][v] != MAX_W && dict[u] + _matrix[u][v] < dict[v]) {
						dict[v] = dict[u] + _matrix[u][v];
						parentPath[v] = u; //�ɳڳɹ�������·��������
					}
				}
			}
		}
		bool BellmanFord(const char& src, vector<W>& dict, vector<int>& parentPath) {
			int n = _vertexs.size();
			int srci = getVertexIndex(src);
			dict.resize(n, MAX_W);
			parentPath.resize(n, -1);
			dict[srci] = W();
			for (int k = 0; k < n - 1; k++) { //������n-1��
				bool exchange = false;
				for (int i = 0; i < n; i++) {
					for (int j = 0; j < n; j++) {
						if (_matrix[i][j] != MAX_W && dict[i] + _matrix[i][j] < dict[j]) {
							dict[j] = dict[i] + _matrix[i][j];
							parentPath[j] = i;
							exchange = true;
						}
					}
				}
				if (exchange == false) {
					break;
				}
			}
			//������n-1�κ�������ܸ��£���˵�����и�Ȩ��·
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					if (_matrix[i][j] != MAX_W && dict[i] + _matrix[i][j] < dict[j]) {
						return false;
					}
				}
			}
			return true;
		}
		void FloydWarshall(vector<vector<W>>& vvDict, vector<vector<int>>& vvParentPath) {
			int n = _vertexs.size();
			vvDict.resize(n, vector<W>(n, MAX_W));
			vvParentPath.resize(n, vector<int>(n, -1));

			//��ʼ��ֱ�������Ķ���
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					if (_matrix[i][j] != MAX_W) {
						vvDict[i][j] = _matrix[i][j];
						vvParentPath[i][j] = i;
					}
					if (i == j) {
						vvDict[i][j] = 0;
					}
				}
			}
			printDictAndParentPath(vvDict, vvParentPath);
			//�ɳ�
			for (int k = 0; k < n; k++) {
				for (int i = 0; i < n; i++) {
					for (int j = 0; j < n; j++) {
						if (vvDict[i][k] != MAX_W && vvDict[k][j] != MAX_W &&
							vvDict[i][k] + vvDict[k][j] < vvDict[i][j]) {
							vvDict[i][j] = vvDict[i][k] + vvDict[k][j];
							vvParentPath[i][j] = vvParentPath[k][j];
						}
					}
				}
				printDictAndParentPath(vvDict, vvParentPath);
			}
		}
		void printDictAndParentPath(const vector<vector<W>>& vvDict, const vector<vector<int>>& vvParentPath) {
			int n = _vertexs.size();
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					if (vvDict[i][j] != MAX_W) {
						printf("%4d", vvDict[i][j]);
					}
					else {
						printf("   *");
					}
				}
				cout << endl;
			}
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
		void printShortPath(const V& src, const vector<W>& dict, const vector<int>& parentPath) {
			int n = _vertexs.size();
			int srci = getVertexIndex(src);
			for (int i = 0; i < n; i++) {
				cout << src << "->" << _vertexs[i] << ": " << src;
				vector<int> path;
				int cur = i;
				while (cur != srci) {
					path.push_back(cur);
					cur = parentPath[cur];
				}
				reverse(path.begin(), path.end());
				for (int j = 0; j < path.size(); j++) {
					cout << "->" << _vertexs[path[j]];
				}
				cout << "[" << dict[i] << "]" << endl;
			}
		}
	private:
		vector<V> _vertexs;               //���㼯��
		unordered_map<V, int> _vIndexMap; //����ӳ���±�
		vector<vector<W>> _matrix;        //�ڽӾ���
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
		//string a[] = { "����","����","����","����","����" ,"���"};
		//Graph<string, int> g(a, 6);
		//g.addEdge("����", "����", 100);
		//g.addEdge("����", "����", 200);
		//g.addEdge("����", "����", 30);
		//g.addEdge("����", "����", 30);
		//g.addEdge("����", "���", 50);

		//g.print();
		//g.bfs("����");
		//g.dfs("����");

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
		vector<int> dict, parentPath;
		g.Dijkstra('s', dict, parentPath);
		g.printShortPath('s', dict, parentPath);

		////û���ҵ�����Ȩ�����·��
		//Graph<char, int, INT_MAX, true> g("styx", 4);
		//g.addEdge('s', 't', 10);
		//g.addEdge('s', 'y', 5);
		//g.addEdge('t', 'y', -7);
		//g.addEdge('y', 'x', 3);
		//vector<int> dict, parentPath;
		//g.Dijkstra('s', dict, parentPath);
		//g.printShortPath('s', dict, parentPath);
	}
	void testBellmanFord() {
		Graph<char, int, INT_MAX, true> g("stxyz", 5);
		g.addEdge('s', 't', 6);
		g.addEdge('s', 'y', 7);
		g.addEdge('t', 'x', 5);
		g.addEdge('t', 'y', 8);
		g.addEdge('t', 'z', -4);
		g.addEdge('x', 't', -2);
		g.addEdge('y', 'x', -3);
		g.addEdge('y', 'z', 9);
		g.addEdge('z', 's', 2);
		//g.addEdge('z', 'x', 7);
		g.addEdge('z', 'x', -7);

		vector<int> dict, parentPath;
		if (g.BellmanFord('s', dict, parentPath)) {
			g.printShortPath('s', dict, parentPath);
		}
		else {
			cout << "���ڸ�Ȩ��·" << endl;
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

		vector<vector<int>> vvDict, vvParentPath;
		g.FloydWarshall(vvDict, vvParentPath);
	}
}

//�ڽӱ�
namespace LinkTable {
	template<class W>
	//�����㶨��
	struct Edge {
		//int _srci;    //Դ������±꣨��ѡ��
		int _dsti;      //Ŀ�궥����±�
		W _weight;      //�ߵ�Ȩֵ
		Edge<W>* _next; //����ָ��

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
		//���캯��
		Graph(const V* vertexs, int n)
			:_vertexs(vertexs, vertexs + n) //���ö��㼯��
			, _linkTable(n, nullptr) { //�����ڽӱ�Ŀռ�
			//�����������±��ӳ���ϵ
			for (int i = 0; i < n; i++) {
				_vIndexMap[vertexs[i]] = i;
			}
		}
		//��ȡ�����Ӧ���±�
		int getVertexIndex(const V& v) {
			auto iter = _vIndexMap.find(v);
			if (iter != _vIndexMap.end()) { //�������
				return iter->second;
			}
			else { //���㲻����
				throw invalid_argument("�����ڵĶ���");
				return -1;
			}
		}
		//��ӱ�
		void addEdge(const V& src, const V& dst, const W& weight) {
			int srci = getVertexIndex(src), dsti = getVertexIndex(dst); //��ȡԴ�����Ŀ�궥����±�

			//��Ӵ�Դ���㵽Ŀ�궥��ı�
			Edge* sdEdge = new Edge(dsti, weight);
			sdEdge->_next = _linkTable[srci];
			_linkTable[srci] = sdEdge;

			if (Direction == false) { //����ͼ
				//��Ӵ�Ŀ�궥�㵽Դ����ı�
				Edge* dsEdge = new Edge(srci, weight);
				dsEdge->_next = _linkTable[dsti];
				_linkTable[dsti] = dsEdge;
			}
		}
		//��ӡ���㼯�Ϻ��ڽӱ�
		void print() {
			int n = _vertexs.size();
			//��ӡ���㼯��
			for (int i = 0; i < n; i++) {
				cout << "[" << i << "]->" << _vertexs[i] << " ";
			}
			cout << endl << endl;

			//��ӡ�ڽӱ�
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
		vector<V> _vertexs;               //���㼯��
		unordered_map<V, int> _vIndexMap; //����ӳ���±�
		vector<Edge*> _linkTable;         //�ڽӱ����߱�
	};
	void testGraph() {
		string a[] = { "����","����","����","����" };
		Graph<string, int, true> g(a, 4);
		g.addEdge("����", "����", 100);
		g.addEdge("����", "����", 200);
		g.addEdge("����", "����", 30);

		g.print();
	}
}
