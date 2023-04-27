#pragma once

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

//���鼯
class UnionFindSet {
public:
	UnionFindSet(int n)
		:_ufs(n, -1) //��ʼʱ����Ԫ���Գ�һ������
	{}
	//�ҵ�Ԫ�����ڼ��ϵĸ���㣨������
	int findRoot(int x) {
		int parent = x; //Ĭ�ϵ�ǰ�����Ǹ����
		while (_ufs[parent] >= 0) { //��ǰ���ֵ���Ǹ��������������
			parent = _ufs[parent];
		}
		return parent; //���ظ����
	}
	////�ݹ�
	//int findRoot(int x) {
	//	return _ufs[x] < 0 ? x : findRoot(_ufs[x]);
	//}
	////�ݹ�+ѹ��
	//int findRoot(int x) {
	//	int parent = x;
	//	if (_ufs[x] >= 0) {
	//		parent = findRoot(_ufs[x]);
	//		_ufs[x] = parent;
	//	}
	//	return parent;
	//}
	////�ݹ�+ѹ��
	//int findRoot(int x) {
	//	if (_ufs[x] >= 0) {
	//		_ufs[x] = findRoot(_ufs[x]);
	//		return _ufs[x];
	//	}
	//	return x;
	//}
	//�ϲ�����Ԫ�����ڵļ���
	bool unionSet(int x1, int x2) {
		int parent1 = findRoot(x1), parent2 = findRoot(x2); //�ֱ��ҵ�����Ԫ�����ڼ��ϵĸ����
		if (parent1 == parent2) //��������Ѿ�λ��ͬһ����
			return false;
		if (_ufs[parent1] > _ufs[parent2]) //��С���Ϻϲ����󼯺���
			swap(parent1, parent2);
		//��x2���ڵļ��Ϻϲ���x1���ڵļ���
		_ufs[parent1] += _ufs[parent2]; //����x1���ڼ��ϵ�Ԫ�ظ���
		_ufs[parent2] = parent1; //��x1���ڼ��ϵĸ������Ϊx2���ڼ��ϵĸ����ĸ���
		return true;
	}
	//��ȡ���鼯�м��ϵĸ���
	int getNum() {
		int count = 0; //ͳ�Ƹ����ĸ���
		for (const int& val : _ufs) {
			if (val < 0) //Ԫ��ֵΪ������Ϊ�����
				count++;
		}
		return count; //���ظ����ĸ���
	}
	void print() {
		for (const auto& e : _ufs)
			cout << e << " ";
		cout << endl;
	}
private:
	vector<int> _ufs; //ά���������֮��Ĺ�ϵ
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
