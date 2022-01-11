#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;

namespace CloseHash
{
	//枚举：标识每个位置的状态
	enum State
	{
		EMPTY,
		EXIST,
		DELETE
	};
	//每个位置除了需要存储KV结构外，还需存储该位置当前的状态
	template<class K, class V>
	struct HashData
	{
		pair<K, V> _kv;
		State _state = EMPTY; //状态
	};
	//让key通过该仿函数得到一个可以取模的整数
	template<class K>
	struct Hash
	{
		size_t operator()(const K& key)
		{
			return key;
		}
	};
	//string类型的特化仿函数（string做key比较常见）
	template<>
	struct Hash<string>
	{
		size_t operator()(const string& s)
		{
			size_t value = 0;
			for (auto ch : s)
			{
				value = value * 131 + ch; //BKDR
			}
			return value;
		}
	};
	//哈希表
	template<class K, class V, class HashFunc=Hash<K>>
	class HashTable
	{
	public:
		//插入函数
		bool Insert(const pair<K, V>& kv)
		{
			HashData<K, V>* ret = Find(kv.first);
			if (ret) //不允许数据冗余
			{
				return false;
			}

			if (_table.size() == 0)
			{
				_table.resize(10); //设置哈希表初始空间大小
			}
			else if ((double)_n / (double)_table.size() > 0.7) //负载因子大于0.7需要增容
			{
				//增容
				//1、将哈希表当中的数据插入到一个新的哈希表，该哈希表的大小设置为原来的2倍
				HashTable<K, V, HashFunc> newHT;
				newHT._table.resize(2 * _table.size());
				for (auto& e : _table)
				{
					if (e._state == EXIST)
					{
						newHT.Insert(e._kv);
					}
				}
				//2、交换这两个哈希表
				_table.swap(newHT._table);
			}

			//插入数据
			HashFunc hf;
			size_t start = hf(kv.first)%_table.size(); //不能是capacity
			size_t index = start;
			size_t i = 1;
			int base = index;
			//1、找到一个状态为EMPTY或DELETE的位置
			while (_table[index]._state == EXIST)
			{
				index = start + i; //index = start + i*i;
				index %= _table.size();
				i++;
			}
			//2、将数据插入该位置，并将该位置的状态设置为EXIST
			_table[index]._kv = kv;
			_table[index]._state = EXIST;
			_n++;
			return true;
		}
		//查找函数
		HashData<K, V>* Find(const K& key)
		{
			if (_table.size() == 0) //哈希表大小为0，查找失败
			{
				return nullptr;
			}

			HashFunc hf;
			size_t start = hf(key)%_table.size();
			size_t index = start;
			size_t i = 1;
			//直到找到空位置为止
			while (_table[index]._state != EMPTY)
			{
				//若该位置的状态为EXIST，并且key值匹配，则查找成功
				if (_table[index]._state == EXIST&&_table[index]._kv.first == key)
				{
					return &_table[index];
				}
				index = start + i; //index = start + i*i;
				index %= _table.size();
				i++;
			}
			return nullptr; //直到找到空位置还没有找到目标元素，查找失败
		}

		//删除函数
		bool Erase(const K& key)
		{
			//1、判断哈希表中是否存在该元素
			HashData<K, V>* ret = Find(key);
			if (ret)
			{
				//2、若存在，则将该元素所在位置的状态改为DELETE即可
				ret->_state = DELETE;
				_n--;
				return true;
			}
			return false;
		}
	private:
		vector<HashData<K, V>> _table; //哈希表
		size_t _n = 0; //有效元素个数
	};

	struct IntHashFunc
	{
		int operator()(int i)
		{
			return i;
		}
	};


	//struct StringHashFunc
	//{
	//	size_t operator()(const string s)
	//	{
	//		return s[0];
	//	}
	//};


	struct StringHashFunc
	{
		size_t operator()(const string& s)
		{
			size_t value = 0;
			for (auto ch : s)
			{
				value = value*131 + ch;
			}
			return value;
		}
	};
	void TestHashTable1()
	{
		vector<int> v{ 1, 5, 10, 100000, 100, 18, 15, 7, 40 , 10};
		HashTable<int, int> ht;
		for (auto& e : v)
		{
			ht.Insert(make_pair(e, e));
		}
		HashData<int, int>* ret = ht.Find(100);
		if (ret)
		{
			cout << "找到了" << endl;
		}
		else
		{
			cout << "没找到" << endl;
		}
		ht.Erase(100000);
		ret = ht.Find(100);
		if (ret)
		{
			cout << "找到了" << endl;
		}
		else
		{
			cout << "没找到" << endl;
		}
		ht.Insert(make_pair(20, 20));

		ret = ht.Find(100);
		if (ret)
		{
			cout << "找到了" << endl;
		}
		else
		{
			cout << "没找到" << endl;
		}
		ht.Erase(100);
		ret = ht.Find(100);
		if (ret)
		{
			cout << "找到了" << endl;
		}
		else
		{
			cout << "没找到" << endl;
		}
	}
	void TestHashTable2()
	{
		//vector<string> v{ "苹果", "香蕉", "苹果", "榴莲", "苹果", "香蕉", "苹果", "香蕉", "苹果" };
		vector<string> v{ "abcd", "cbad", "accc", "acbd"};
		StringHashFunc hf;
		for (auto e : v)
		{
			cout << hf(e) << endl;
		}
		HashTable<string, int> ht;
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
		//printf("%d, %d, %d\n", ('i' + 't') % 10, ('i' + 'n' + 't') % 10, ('i'+'n'+'s'+'e'+'r'+'t')%10);
	}
	//void TestHashTable3()
	//{
	//	struct Stu
	//	{
	//		int _id;
	//		string _name;
	//	};
	//	struct HashFunc
	//	{
	//		int operator()(Stu s)
	//		{
	//			return s._id;
	//		}
	//	};
	//	struct HashPred
	//	{
	//		bool operator()(Stu s1, Stu s2)
	//		{
	//			return s1._id == s2._id;
	//		}
	//	};
	//	//vector<string> v{ "苹果", "香蕉", "苹果", "榴莲", "苹果", "香蕉", "苹果", "香蕉", "苹果" };
	//	vector<Stu> v{ { 1, "zhangsan" }, { 2, "lisi" }, { 2, "lisi" } };
	//	HashTable<Stu, int, HashFunc> ht;
	//	for (auto e : v)
	//	{
	//		HashData<Stu, int>* ret = ht.Find(e);
	//		if (ret)
	//		{
	//			ret->_kv.second++;
	//		}
	//		else
	//		{
	//			ht.Insert(make_pair(e, 1));
	//		}
	//	}

	//}
}

namespace OpenHash
{
	template<class K, class V>
	struct HashNode
	{
		HashNode(const pair<K, V>& kv)
			:_kv(kv)
			, _next(nullptr)
		{}

		pair<K, V> _kv;
		HashNode<K, V>* _next;
	};
	template<class K>
	struct Hash
	{
		size_t operator()(const K& key)
		{
			return key;
		}
	};
	template<>
	struct Hash<string>
	{
		size_t operator()(const string& s)
		{
			size_t value = 0;
			for (auto ch : s)
			{
				value = value * 131 + ch; //BKDR
			}
			return value;
		}
	};
	template<class K, class V, class HashFunc = Hash<K>>
	class HashTable
	{
		typedef HashNode<K, V> Node;
	public:
		size_t GetNextPrime(size_t prime)
		{
			const int PRIMECOUNT = 28;
			const size_t primeList[PRIMECOUNT] =
			{
				53ul, 97ul, 193ul, 389ul, 769ul,
				1543ul, 3079ul, 6151ul, 12289ul, 24593ul,
				49157ul, 98317ul, 196613ul, 393241ul, 786433ul,
				1572869ul, 3145739ul, 6291469ul, 12582917ul, 25165843ul,
				50331653ul, 100663319ul, 201326611ul, 402653189ul, 805306457ul,
				1610612741ul, 3221225473ul, 4294967291ul
			};
			for (size_t i = 0; i < PRIMECOUNT; i++)
			{
				if (primeList[i] > prime)
					return primeList[i];
			}
			return primeList[i];
		}
		//插入函数
		bool Insert(const pair<K, V>& kv)
		{
			Node* ret = Find(kv.first);
			if (ret)
			{
				return false;
			}

			if (_n == _table.size())
			{
				HashFunc hf;
				vector<Node*> newtable;
				//size_t newsize = _table.size() == 0 ? 10 : _table.size() * 2;
				//newtable.resize(newsize);

				newtable.resize(GetNextPrime(_table.size()));
				for (size_t i = 0; i < _table.size(); i++)
				{
					if (_table[i]) //桶不为空
					{
						Node* cur = _table[i];
						while (cur)
						{
							Node* next = cur->_next;
							size_t index = hf(cur->_kv.first)%newtable.size();
							//头插
							cur->_next = newtable[index];
							newtable[index] = cur;

							cur = next;
						}
						_table[i] = nullptr;
					}
				}
				_table.swap(newtable);
			}

			HashFunc hf;
			size_t index = hf(kv.first)%_table.size();
			Node* newnode = new Node(kv);
			//头插
			newnode->_next = _table[index];
			_table[index] = newnode;
			_n++;
			return true;
		}
		//查找函数
		HashNode<K, V>* Find(const K& key)
		{
			if (_table.size() == 0)
			{
				return nullptr;
			}

			HashFunc hf;
			size_t index = hf(key)%_table.size();
			HashNode<K, V>* cur = _table[index];
			while (cur)
			{
				if (cur->_kv.first == key)
				{
					return cur;
				}
				cur = cur->_next;
			}
			return nullptr;
		}
		//删除函数
		bool Erase(const K& key)
		{
			HashFunc hf;
			size_t index = hf(key)%_table.size();
			Node* prev = nullptr;
			Node* cur = _table[index];
			while (cur)
			{
				if (cur->_kv.first == key)
				{
					if (prev == nullptr)
					{
						_table[index] = cur->_next;
					}
					else
					{
						prev->_next = cur->_next;
					}
					delete cur;
					_n--;
					return true;
				}
				prev = cur;
				cur = cur->_next;
			}
			//假删除可能会导致迭代器失效
			
			return false;
		}
	private:
		vector<Node*> _table;
		size_t _n = 0;
	};
	void TestHashTable1()
	{
		vector<int> v{ 1, 5, 10, 100000, 100, 18, 15, 7, 40, 6 };
		HashTable<int, int> ht;
		for (auto& e : v)
		{
			ht.Insert(make_pair(e, e));
		}
		ht.Insert(make_pair(25, 25));

	}

	void TestHashTable2()
	{
		vector<string> v{ "苹果", "香蕉", "苹果", "榴莲", "苹果", "香蕉", "苹果", "香蕉", "苹果" };
		HashTable<string, int> ht;
		for (const auto& e : v)
		{
			HashNode<string, int>* ret = ht.Find(e);
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