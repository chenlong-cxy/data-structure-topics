#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;

namespace CloseHash
{
	enum State
	{
		EMPTY,
		EXIST,
		DELETE
	};
	template<class K, class V>
	struct HashData
	{
		pair<K, V> _kv;
		State _state = EMPTY; //״̬
	};

	template<class K, class V, class HashFunc, class PredFunc>
	class HashTable
	{
	public:
		//���뺯��
		bool Insert(const pair<K, V>& kv)
		{
			HashData<K, V>* ret = Find(kv.first);
			if (ret) //��������������
			{
				return false;
			}

			if (_table.size() == 0)
			{
				_table.resize(10);
			}
			else if ((double)_n / (double)_table.size() > 0.7) //�жϸ�������
			{
				//����
				HashTable<K, V, HashFunc, PredFunc> newHT;
				newHT._table.resize(2 * _table.size());
				for (auto& e : _table)
				{
					if (e._state == EXIST)
					{
						newHT.Insert(e._kv);
					}
				}
				_table.swap(newHT._table);
			}

			HashFunc hf;
			size_t start = hf(kv.first)%_table.size(); //������capacity
			size_t index = start;
			size_t i = 1;
			int base = index;
			while (_table[index]._state == EXIST)
			{
				index = start + i; //index = start + i*i;
				index %= _table.size();
				i++;
			}
			_table[index]._kv = kv;
			_table[index]._state = EXIST;
			_n++;
			return true;
		}
		//���Һ���
		HashData<K, V>* Find(const K& key)
		{
			if (_table.size() == 0)
			{
				return nullptr;
			}

			HashFunc hf;
			PredFunc pf;
			size_t start = hf(key)%_table.size();
			size_t index = start;
			size_t i = 1;
			while (_table[index]._state != EMPTY)
			{
				if (_table[index]._state == EXIST&&pf(_table[index]._kv.first, key))
				{
					return &_table[index];
				}
				index = start + i; //index = start + i*i;
				index %= _table.size();
				i++;
			}
			return nullptr;
		}

		bool Erase(const K& key)
		{
			HashData<K, V>* ret = Find(key);
			if (ret)
			{
				ret->_state = DELETE;
				return true;
			}
			return false;
		}
	private:
		vector<HashData<K, V>> _table;
		size_t _n = 0; //��ЧԪ�ظ���
	};

	struct IntHashFunc
	{
		int operator()(int i)
		{
			return i;
		}
	};

	struct IntPredFunc
	{
		bool operator()(int i1, int i2)
		{
			return i1 == i2;
		}
	};

	struct StringHashFunc
	{
		size_t operator()(const string s)
		{
			return s[0];
		}
	};

	struct StringPredFunc
	{
		bool operator()(const string& s1, const string& s2)
		{
			return s1 == s2;
		}
	};

	//struct StringHashFunc
	//{
	//	size_t operator()(const string& s)
	//	{
	//		size_t value = 0;
	//		for (auto ch : s)
	//		{
	//			value += ch;
	//		}
	//		return value;
	//	}
	//};
	void TestHashTable1()
	{
		vector<int> v{ 1, 5, 10, 100000, 100, 18, 15, 7, 40 , 10};
		HashTable<int, int, IntHashFunc, IntPredFunc> ht;
		for (auto& e : v)
		{
			ht.Insert(make_pair(e, e));
		}
		HashData<int, int>* ret = ht.Find(100);
		if (ret)
		{
			cout << "�ҵ���" << endl;
		}
		else
		{
			cout << "û�ҵ�" << endl;
		}
		ht.Erase(100000);
		ret = ht.Find(100);
		if (ret)
		{
			cout << "�ҵ���" << endl;
		}
		else
		{
			cout << "û�ҵ�" << endl;
		}
		ht.Insert(make_pair(20, 20));

		ret = ht.Find(100);
		if (ret)
		{
			cout << "�ҵ���" << endl;
		}
		else
		{
			cout << "û�ҵ�" << endl;
		}
		ht.Erase(100);
		ret = ht.Find(100);
		if (ret)
		{
			cout << "�ҵ���" << endl;
		}
		else
		{
			cout << "û�ҵ�" << endl;
		}
	}
	void TestHashTable2()
	{
		//vector<string> v{ "ƻ��", "�㽶", "ƻ��", "����", "ƻ��", "�㽶", "ƻ��", "�㽶", "ƻ��" };
		vector<string> v{ "insert", "int", "iostream", "it", "is", "int", "int" };
		HashTable<string, int, StringHashFunc, StringPredFunc> ht;
		for (auto e : v)
		{
			HashData<string, int>* ret = ht.Find(e);
			if (ret)
			{
				ret->_kv.second++;
			}
			else
			{
				ht.Insert(make_pair(e, 1));
			}
		}

	}
	void TestHashTable3()
	{
		struct Stu
		{
			int _id;
			string _name;
		};
		struct HashFunc
		{
			int operator()(Stu s)
			{
				return s._id;
			}
		};
		struct HashPred
		{
			bool operator()(Stu s1, Stu s2)
			{
				return s1._id == s2._id;
			}
		};
		//vector<string> v{ "ƻ��", "�㽶", "ƻ��", "����", "ƻ��", "�㽶", "ƻ��", "�㽶", "ƻ��" };
		vector<Stu> v{ { 1, "zhangsan" }, { 2, "lisi" }, { 2, "lisi" } };
		HashTable<Stu, int, HashFunc, HashPred> ht;
		for (auto e : v)
		{
			HashData<Stu, int>* ret = ht.Find(e);
			if (ret)
			{
				ret->_kv.second++;
			}
			else
			{
				ht.Insert(make_pair(e, 1));
			}
		}

	}
}