#pragma once

#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <queue>
using namespace std;

//�ڽӾ���
namespace Matrix {
	template<class V, class W, W MAX_W = INT_MAX, bool Direction = false>
	class Graph {
	public:
		Graph(const V* vertexs, int n)
			:_vertexs(vertexs, vertexs + n)
			,_matrix(n, vector<int>(n, MAX_W)) {
			for (int i = 0; i < n; i++) {
				_vIndexMap[vertexs[i]] = i;
			}
		}
		int getVertexIndex(const V& v) {
			auto iter = _vIndexMap.find(v);
			if (iter != _vIndexMap.end()) {
				return iter->second;
			}
			else {
				throw invalid_argument("�����ڵĶ���");
				return -1;
			}
		}
		void addEdge(const V& src, const V& dst, const W& weight) {
			int srci = getVertexIndex(src), dsti = getVertexIndex(dst);
			_matrix[srci][dsti] = weight;
			if (Direction == false) { //����ͼ
				_matrix[dsti][srci] = weight;
			}
		}
		void bfs(const V& src) {
			int srci = getVertexIndex(src);
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
		void _dfs(int srci, vector<bool>& visited) {
			cout << _vertexs[srci] << " "; //����
			visited[srci] = true; //���Ϊ���ʹ�
			for (int i = 0; i < _vertexs.size(); i++) { //�Ҵ�srci���ӳ�ȥ�Ķ���
				if (_matrix[srci][i] != MAX_W && visited[i] == false) { //���ڽӶ��㣬����û�б����ʹ�
					_dfs(i, visited);
				}
			}
		}
		void dfs(const V& src) {
			int srci = getVertexIndex(src);
			vector<bool> visited(_vertexs.size(), false); //�������
			_dfs(srci, visited);
			cout << endl;
		}
		void print() {
			int n = _vertexs.size();
			//��ӡ����
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
	void testBfs() {
		string a[] = { "����","����","����","����","����" ,"���"};
		Graph<string, int> g(a, 6);
		g.addEdge("����", "����", 100);
		g.addEdge("����", "����", 200);
		g.addEdge("����", "����", 30);
		g.addEdge("����", "����", 30);
		g.addEdge("����", "���", 50);

		g.print();
		g.bfs("����");
		g.dfs("����");
	}
}

//�ڽӱ�
namespace LinkTable {
	template<class W>
	struct Edge {
		//int _srci; //Դ������±�
		int _dsti; //Ŀ�궥����±�
		W _weight; //�ߵ�Ȩֵ
		Edge<W>* _next;

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
		Graph(const V* vertexs, int n)
			:_vertexs(vertexs, vertexs + n)
			, _linkTable(n, nullptr) {
			for (int i = 0; i < n; i++) {
				_vIndexMap[vertexs[i]] = i;
			}
		}
		int getVertexIndex(const V& v) {
			auto iter = _vIndexMap.find(v);
			if (iter != _vIndexMap.end()) {
				return iter->second;
			}
			else {
				throw invalid_argument("�����ڵĶ���");
				return -1;
			}
		}
		void addEdge(const V& src, const V& dst, const W& weight) {
			int srci = getVertexIndex(src), dsti = getVertexIndex(dst);

			Edge* sdEdge = new Edge(dsti, weight);
			sdEdge->_next = _linkTable[srci];
			_linkTable[srci] = sdEdge;

			if (Direction == false) { //����ͼ
				Edge* dsEdge = new Edge(srci, weight);
				dsEdge->_next = _linkTable[dsti];
				_linkTable[dsti] = dsEdge;
			}
		}
		void print() {
			int n = _vertexs.size();
			cout << "����: ";
			for (int i = 0; i < n; i++) {
				cout << _vertexs[i] << " ";
			}
			cout << endl;

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
		vector<Edge*> _linkTable;         //�ڽӱ�
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
