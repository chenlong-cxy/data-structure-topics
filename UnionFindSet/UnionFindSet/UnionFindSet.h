#pragma once

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

//并查集
class UnionFindSet {
public:
	//构造函数
	UnionFindSet(int n)
		:_ufs(n, -1) //初始时各个元素自成一个集合
	{}
	////查找元素所在集合的根结点（迭代）
	//int findRoot(int x) {
	//	int parent = x; //默认当前结点就是根结点
	//	while (_ufs[parent] >= 0) { //当前结点值不是负数则继续向上找
	//		parent = _ufs[parent];
	//	}
	//	return parent; //返回根结点
	//}
	////查找元素所在集合的根结点（递归）
	//int findRoot(int x) {
	//	return _ufs[x] < 0 ? x : findRoot(_ufs[x]);
	//}
	////查找元素所在集合的根结点（递归）
	//int findRoot(int x) {
	//	int parent = x; //默认当前结点就是根结点
	//	if (_ufs[x] >= 0) { //当前结点值不是负数则继续向上找
	//		parent = findRoot(_ufs[x]); //找到根结点
	//		_ufs[x] = parent; //将当前结点的父亲改为根结点（路径压缩）
	//	}
	//	return parent; //返回根结点
	//}
	////递归+压缩
	//int findRoot(int x) {
	//	if (_ufs[x] >= 0) {
	//		_ufs[x] = findRoot(_ufs[x]);
	//		return _ufs[x];
	//	}
	//	return x;
	//}
	//迭代+压缩
	int findRoot(int x) {
		int root = x; //默认当前结点就是根结点
		while (_ufs[root] >= 0) { //当前结点值不是负数则继续向上找
			root = _ufs[root];
		}
		//路径压缩
		while (_ufs[x] >= 0) { //遍历从根结点到x结点路径上的所有结点
			int parent = _ufs[x];
			_ufs[x] = root; //将结点的父亲改为根结点
			x = parent;
		}
		return root; //返回根结点
	}
	//合并两个元素所在的集合
	bool unionSet(int x1, int x2) {
		int parent1 = findRoot(x1), parent2 = findRoot(x2); //分别找到两个元素所在集合的根结点
		if (parent1 == parent2) //两个结点已经位于同一集合
			return false;
		if (_ufs[parent1] > _ufs[parent2]) //让parent1标记大集合根结点，parent2标记小集合根结点
			swap(parent1, parent2);
		//将小集合合并到大集合上
		_ufs[parent1] += _ufs[parent2]; //将小集合根结点的值累加到大集合的根结点上
		_ufs[parent2] = parent1; //将小集合根结点的值改为大集合根结点的编号
		return true;
	}
	//获取并查集中集合的个数
	int getNum() {
		int count = 0; //统计根结点的个数
		for (const int& val : _ufs) {
			if (val < 0) //元素值为负数则为根结点
				count++;
		}
		return count; //返回根结点的个数
	}
	//判断两个元素是否在同一个集合
	bool inSameSet(int x1, int x2) {
		return findRoot(x1) == findRoot(x2);
	}
	void print() {
		for (const auto& e : _ufs)
			cout << e << " ";
		cout << endl;
	}
private:
	vector<int> _ufs; //维护各个结点之间的关系
};

////并查集
//template<class T>
//class UnionFindSet {
//public:
//	//构造函数
//	UnionFindSet(const vector<T>& v)
//		:_ufs(v.size(), -1) //初始时各个元素自成一个集合
//	{
//		//建立元素与数组下标之间的映射关系
//		for (int i = 0; i < v.size(); i++) {
//			_indexMap[v[i]] = i;
//		}
//	}
//	//查找元素所在集合的根结点（迭代）
//	int findRoot(const T& x) {
//		int parent = _indexMap[x]; //默认当前结点就是根结点
//		while (_ufs[parent] >= 0) { //当前结点值不是负数则继续向上找
//			parent = _ufs[parent];
//		}
//		return parent; //返回根结点
//	}
//	//合并两个元素所在的集合
//	bool unionSet(const T& x1, const T& x2) {
//		int parent1 = findRoot(x1), parent2 = findRoot(x2); //分别找到两个元素所在集合的根结点
//		if (parent1 == parent2) //两个结点已经位于同一集合
//			return false;
//		if (_ufs[parent1] > _ufs[parent2]) //让parent1标记大集合根结点，parent2标记小集合根结点
//			swap(parent1, parent2);
//		//将小集合合并到大集合上
//		_ufs[parent1] += _ufs[parent2]; //将小集合根结点的值累加到大集合的根结点上
//		_ufs[parent2] = parent1; //将小集合根结点的值改为大集合根结点的编号
//		return true;
//	}
//	//获取并查集中集合的个数
//	int getNum() {
//		int count = 0; //统计根结点的个数
//		for (const int& val : _ufs) {
//			if (val < 0) //元素值为负数则为根结点
//				count++;
//		}
//		return count; //返回根结点的个数
//	}
//	void print() {
//		for (const auto& e : _ufs)
//			cout << e << " ";
//		cout << endl;
//	}
//private:
//	vector<int> _ufs; //维护各个结点之间的关系
//	unordered_map<T, int> _indexMap; //建立元素与数组下标之间的映射关系
//};

////省份数量
//class Solution {
//public:
//	int findCircleNum(vector<vector<int>>& isConnected) {
//		//1、初始化并查集
//		int n = isConnected.size();
//		vector<int> ufs(n, -1);
//		auto findRoot = [&ufs](int x)->int {
//			int parent = x;
//			while (ufs[parent] >= 0) {
//				parent = ufs[parent];
//			}
//			return parent;
//		};
//		//2、根据所给矩阵合并集合
//		for (int i = 0; i < n; i++) {
//			for (int j = 0; j < n; j++) {
//				if (isConnected[i][j] == 1) { //城市相连
//					int parent1 = findRoot(i), parent2 = findRoot(j);
//					if (parent1 != parent2) { //需要合并
//						ufs[parent2] = parent1;
//					}
//				}
//			}
//		}
//		//3、统计并查集中集合的个数
//		int count = 0;
//		for (const int& e : ufs) {
//			if (e < 0)
//				count++;
//		}
//		return count;
//	}
//};

////等式方程的可满足性
//class Solution {
//public:
//	bool equationsPossible(vector<string>& equations) {
//		//1、初始化并查集
//		vector<int> ufs(26, -1);
//		auto findRoot = [&ufs](int x)->int {
//			int parent = x;
//			while (ufs[parent] >= 0) {
//				parent = ufs[parent];
//			}
//			return parent;
//		};
//		//2、根据字符串方程组中的等式合并集合
//		for (const string& s : equations) {
//			if (s[1] == '=') { //等式
//				int parent1 = findRoot(s[0] - 'a'), parent2 = findRoot(s[3] - 'a');
//				if (parent1 != parent2) { //需要合并
//					ufs[parent2] = parent1;
//				}
//			}
//		}
//		//3、根据并查集验证字符串方程组中的不等式
//		for (const string& s : equations) {
//			if (s[1] == '!') { //不等式
//				int parent1 = findRoot(s[0] - 'a'), parent2 = findRoot(s[3] - 'a');
//				if (parent1 == parent2) { //在同一个集合
//					return false;
//				}
//			}
//		}
//		return true;
//	}
//};
