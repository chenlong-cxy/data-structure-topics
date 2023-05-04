#pragma once

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

//���鼯
class UnionFindSet {
public:
	//���캯��
	UnionFindSet(int n)
		:_ufs(n, -1) //��ʼʱ����Ԫ���Գ�һ������
	{}
	////����Ԫ�����ڼ��ϵĸ���㣨������
	//int findRoot(int x) {
	//	int parent = x; //Ĭ�ϵ�ǰ�����Ǹ����
	//	while (_ufs[parent] >= 0) { //��ǰ���ֵ���Ǹ��������������
	//		parent = _ufs[parent];
	//	}
	//	return parent; //���ظ����
	//}
	////����Ԫ�����ڼ��ϵĸ���㣨�ݹ飩
	//int findRoot(int x) {
	//	return _ufs[x] < 0 ? x : findRoot(_ufs[x]);
	//}
	////����Ԫ�����ڼ��ϵĸ���㣨�ݹ飩
	//int findRoot(int x) {
	//	int parent = x; //Ĭ�ϵ�ǰ�����Ǹ����
	//	if (_ufs[x] >= 0) { //��ǰ���ֵ���Ǹ��������������
	//		parent = findRoot(_ufs[x]); //�ҵ������
	//		_ufs[x] = parent; //����ǰ���ĸ��׸�Ϊ����㣨·��ѹ����
	//	}
	//	return parent; //���ظ����
	//}
	////�ݹ�+ѹ��
	//int findRoot(int x) {
	//	if (_ufs[x] >= 0) {
	//		_ufs[x] = findRoot(_ufs[x]);
	//		return _ufs[x];
	//	}
	//	return x;
	//}
	//����+ѹ��
	int findRoot(int x) {
		int root = x; //Ĭ�ϵ�ǰ�����Ǹ����
		while (_ufs[root] >= 0) { //��ǰ���ֵ���Ǹ��������������
			root = _ufs[root];
		}
		//·��ѹ��
		while (_ufs[x] >= 0) { //�����Ӹ���㵽x���·���ϵ����н��
			int parent = _ufs[x];
			_ufs[x] = root; //�����ĸ��׸�Ϊ�����
			x = parent;
		}
		return root; //���ظ����
	}
	//�ϲ�����Ԫ�����ڵļ���
	bool unionSet(int x1, int x2) {
		int parent1 = findRoot(x1), parent2 = findRoot(x2); //�ֱ��ҵ�����Ԫ�����ڼ��ϵĸ����
		if (parent1 == parent2) //��������Ѿ�λ��ͬһ����
			return false;
		if (_ufs[parent1] > _ufs[parent2]) //��parent1��Ǵ󼯺ϸ���㣬parent2���С���ϸ����
			swap(parent1, parent2);
		//��С���Ϻϲ����󼯺���
		_ufs[parent1] += _ufs[parent2]; //��С���ϸ�����ֵ�ۼӵ��󼯺ϵĸ������
		_ufs[parent2] = parent1; //��С���ϸ�����ֵ��Ϊ�󼯺ϸ����ı��
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
	//�ж�����Ԫ���Ƿ���ͬһ������
	bool inSameSet(int x1, int x2) {
		return findRoot(x1) == findRoot(x2);
	}
	void print() {
		for (const auto& e : _ufs)
			cout << e << " ";
		cout << endl;
	}
private:
	vector<int> _ufs; //ά���������֮��Ĺ�ϵ
};

////���鼯
//template<class T>
//class UnionFindSet {
//public:
//	//���캯��
//	UnionFindSet(const vector<T>& v)
//		:_ufs(v.size(), -1) //��ʼʱ����Ԫ���Գ�һ������
//	{
//		//����Ԫ���������±�֮���ӳ���ϵ
//		for (int i = 0; i < v.size(); i++) {
//			_indexMap[v[i]] = i;
//		}
//	}
//	//����Ԫ�����ڼ��ϵĸ���㣨������
//	int findRoot(const T& x) {
//		int parent = _indexMap[x]; //Ĭ�ϵ�ǰ�����Ǹ����
//		while (_ufs[parent] >= 0) { //��ǰ���ֵ���Ǹ��������������
//			parent = _ufs[parent];
//		}
//		return parent; //���ظ����
//	}
//	//�ϲ�����Ԫ�����ڵļ���
//	bool unionSet(const T& x1, const T& x2) {
//		int parent1 = findRoot(x1), parent2 = findRoot(x2); //�ֱ��ҵ�����Ԫ�����ڼ��ϵĸ����
//		if (parent1 == parent2) //��������Ѿ�λ��ͬһ����
//			return false;
//		if (_ufs[parent1] > _ufs[parent2]) //��parent1��Ǵ󼯺ϸ���㣬parent2���С���ϸ����
//			swap(parent1, parent2);
//		//��С���Ϻϲ����󼯺���
//		_ufs[parent1] += _ufs[parent2]; //��С���ϸ�����ֵ�ۼӵ��󼯺ϵĸ������
//		_ufs[parent2] = parent1; //��С���ϸ�����ֵ��Ϊ�󼯺ϸ����ı��
//		return true;
//	}
//	//��ȡ���鼯�м��ϵĸ���
//	int getNum() {
//		int count = 0; //ͳ�Ƹ����ĸ���
//		for (const int& val : _ufs) {
//			if (val < 0) //Ԫ��ֵΪ������Ϊ�����
//				count++;
//		}
//		return count; //���ظ����ĸ���
//	}
//	void print() {
//		for (const auto& e : _ufs)
//			cout << e << " ";
//		cout << endl;
//	}
//private:
//	vector<int> _ufs; //ά���������֮��Ĺ�ϵ
//	unordered_map<T, int> _indexMap; //����Ԫ���������±�֮���ӳ���ϵ
//};

////ʡ������
//class Solution {
//public:
//	int findCircleNum(vector<vector<int>>& isConnected) {
//		//1����ʼ�����鼯
//		int n = isConnected.size();
//		vector<int> ufs(n, -1);
//		auto findRoot = [&ufs](int x)->int {
//			int parent = x;
//			while (ufs[parent] >= 0) {
//				parent = ufs[parent];
//			}
//			return parent;
//		};
//		//2��������������ϲ�����
//		for (int i = 0; i < n; i++) {
//			for (int j = 0; j < n; j++) {
//				if (isConnected[i][j] == 1) { //��������
//					int parent1 = findRoot(i), parent2 = findRoot(j);
//					if (parent1 != parent2) { //��Ҫ�ϲ�
//						ufs[parent2] = parent1;
//					}
//				}
//			}
//		}
//		//3��ͳ�Ʋ��鼯�м��ϵĸ���
//		int count = 0;
//		for (const int& e : ufs) {
//			if (e < 0)
//				count++;
//		}
//		return count;
//	}
//};

////��ʽ���̵Ŀ�������
//class Solution {
//public:
//	bool equationsPossible(vector<string>& equations) {
//		//1����ʼ�����鼯
//		vector<int> ufs(26, -1);
//		auto findRoot = [&ufs](int x)->int {
//			int parent = x;
//			while (ufs[parent] >= 0) {
//				parent = ufs[parent];
//			}
//			return parent;
//		};
//		//2�������ַ����������еĵ�ʽ�ϲ�����
//		for (const string& s : equations) {
//			if (s[1] == '=') { //��ʽ
//				int parent1 = findRoot(s[0] - 'a'), parent2 = findRoot(s[3] - 'a');
//				if (parent1 != parent2) { //��Ҫ�ϲ�
//					ufs[parent2] = parent1;
//				}
//			}
//		}
//		//3�����ݲ��鼯��֤�ַ����������еĲ���ʽ
//		for (const string& s : equations) {
//			if (s[1] == '!') { //����ʽ
//				int parent1 = findRoot(s[0] - 'a'), parent2 = findRoot(s[3] - 'a');
//				if (parent1 == parent2) { //��ͬһ������
//					return false;
//				}
//			}
//		}
//		return true;
//	}
//};
