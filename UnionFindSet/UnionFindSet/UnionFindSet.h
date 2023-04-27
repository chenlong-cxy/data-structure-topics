#pragma once

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

//并查集
class UnionFindSet {
public:
	UnionFindSet(int n)
		:_ufs(n, -1) //初始时各个元素自成一个集合
	{}
	//找到元素所在集合的根结点（迭代）
	int findRoot(int x) {
		int parent = x; //默认当前结点就是根结点
		while (_ufs[parent] >= 0) { //当前结点值不是负数则继续向上找
			parent = _ufs[parent];
		}
		return parent; //返回根结点
	}
	////递归
	//int findRoot(int x) {
	//	return _ufs[x] < 0 ? x : findRoot(_ufs[x]);
	//}
	////递归+压缩
	//int findRoot(int x) {
	//	int parent = x;
	//	if (_ufs[x] >= 0) {
	//		parent = findRoot(_ufs[x]);
	//		_ufs[x] = parent;
	//	}
	//	return parent;
	//}
	////递归+压缩
	//int findRoot(int x) {
	//	if (_ufs[x] >= 0) {
	//		_ufs[x] = findRoot(_ufs[x]);
	//		return _ufs[x];
	//	}
	//	return x;
	//}
	//合并两个元素所在的集合
	bool unionSet(int x1, int x2) {
		int parent1 = findRoot(x1), parent2 = findRoot(x2); //分别找到两个元素所在集合的根结点
		if (parent1 == parent2) //两个结点已经位于同一集合
			return false;
		if (_ufs[parent1] > _ufs[parent2]) //把小集合合并到大集合上
			swap(parent1, parent2);
		//将x2所在的集合合并到x1所在的集合
		_ufs[parent1] += _ufs[parent2]; //更新x1所在集合的元素个数
		_ufs[parent2] = parent1; //让x1所在集合的根结点作为x2所在集合的根结点的父亲
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
	void print() {
		for (const auto& e : _ufs)
			cout << e << " ";
		cout << endl;
	}
private:
	vector<int> _ufs; //维护各个结点之间的关系
};

//template<class T>
//class UnionFindSet {
//public:
//	UnionFindSet(vector<T> v)
//		:_ufs(v.size(), -1) {
//		for (int i = 0; i < v.size(); i++) {
//			_indexMap[v[i]] = i;
//		}
//	}
//	int findRoot(const T& x) {
//		int parent = _indexMap[x];
//		while (_ufs[parent] >= 0) {
//			parent = _ufs[parent];
//		}
//		return parent;
//	}
//	bool unionSet(const T& x1, const T& x2) {
//		int parent1 = findRoot(x1), parent2 = findRoot(x2);
//		if (parent1 == parent2)
//			return false;
//		_ufs[parent1] += _ufs[parent2];
//		_ufs[parent2] = parent1;
//		return true;
//	}
//	int getNum() {
//		int count = 0;
//		for (const int& e : _ufs) {
//			if (e < 0)
//				count++;
//		}
//		return count;
//	}
//private:
//	vector<int> _ufs;
//	unordered_map<T, int> _indexMap;
//};
