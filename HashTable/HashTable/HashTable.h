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
	//哈希表每个位置存储的结构
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
			//1、查看哈希表中是否存在该键值的键值对
			HashData<K, V>* ret = Find(kv.first);
			if (ret) //哈希表中已经存在该键值的键值对（不允许数据冗余）
			{
				return false; //插入失败
			}

			//2、判断是否需要调整哈希表的大小
			if (_table.size() == 0) //哈希表大小为0
			{
				_table.resize(10); //设置哈希表初始空间大小
			}
			else if ((double)_n / (double)_table.size() > 0.7) //负载因子大于0.7需要增容
			{
				//增容
				//a、创建一个新的哈希表，新哈希表的大小设置为原哈希表的2倍
				HashTable<K, V, HashFunc> newHT;
				newHT._table.resize(2 * _table.size());
				//b、将原哈希表当中的数据插入到新哈希表
				for (auto& e : _table)
				{
					if (e._state == EXIST)
					{
						newHT.Insert(e._kv);
					}
				}
				//c、交换这两个哈希表
				_table.swap(newHT._table);
			}

			//3、将键值对插入哈希表
			HashFunc hf;
			size_t start = hf(kv.first)%_table.size(); //通过哈希函数计算哈希地址（除数不能是capacity）
			size_t index = start;
			size_t i = 1;
			int base = index;
			//a、找到一个状态为EMPTY或DELETE的位置
			while (_table[index]._state == EXIST)
			{
				index = start + i; //线性探测
				//index = start + i*i; //二次探测
				index %= _table.size(); //防止下标超出哈希表范围
				i++;
			}
			//b、将数据插入该位置，并将该位置的状态设置为EXIST
			_table[index]._kv = kv;
			_table[index]._state = EXIST;
			
			//4、哈希表中的有效元素个数加一
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
			size_t start = hf(key) % _table.size(); //通过哈希函数计算哈希地址（除数不能是capacity）
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
				index = start + i; //线性探测
				//index = start + i*i; //二次探测
				index %= _table.size(); //防止下标超出哈希表范围
				i++;
			}
			return nullptr; //直到找到空位置还没有找到目标元素，查找失败
		}

		//删除函数
		bool Erase(const K& key)
		{
			//1、查看哈希表中是否存在该键值的键值对
			HashData<K, V>* ret = Find(key);
			if (ret)
			{
				//2、若存在，则将该键值对所在位置的状态改为DELETE即可
				ret->_state = DELETE;
				//3、哈希表中的有效元素个数减一
				_n--;
				return true;
			}
			return false;
		}
	private:
		vector<HashData<K, V>> _table; //哈希表
		size_t _n = 0; //哈希表中的有效元素个数
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
	//每个哈希桶中存储数据的结构
	template<class K, class V>
	struct HashNode
	{
		pair<K, V> _kv;
		HashNode<K, V>* _next;

		//构造函数
		HashNode(const pair<K, V>& kv)
			:_kv(kv)
			, _next(nullptr)
		{}
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
		//构造函数
		HashTable()
			:_n(0)
		{}
		//拷贝构造函数
		HashTable(const HashTable<K, V>& ht)
		{
			//1、先将原来的哈希表释放
			_Destroy(_table);
			//2、将哈希表的大小调整为ht._table的大小
			_table.resize(ht._table.size());
			//3、将ht._table每个桶当中的结点一个个拷贝到自己的哈希表中（深拷贝）
			for (size_t i = 0; i < ht._table.size(); i++)
			{
				if (ht._table[i])
				{
					Node* cur = ht._table[i];
					while (cur)
					{
						Node* next = cur->_next;
						Node* newnode = new Node(cur->_kv);
						newnode->_next = _table[i];
						_table[i] = newnode;
						cur = next;
					}
				}
			}
			//4、更改哈希表当中的有效数据个数
			_n = ht._n;
		}
		//赋值运算符重载函数
		HashTable<K, V>& operator=(const HashTable<K, V> ht)
		{
			_table.swap(ht._table);
			swap(_n, ht._n);
			return *this;
		}
		void _Destroy(vector<Node*>& v)
		{
			//将哈希表当中的结点一个个释放
			for (size_t i = 0; i < v.size(); i++)
			{
				if (v[i]) //桶不为空
				{
					Node* cur = v[i];
					while (cur)
					{
						Node* next = cur->_next;
						delete cur;
						cur = next;
					}
					v[i] = nullptr;
				}
			}
		}
		//析构函数
		~HashTable()
		{
			//释放哈希表
			_Destroy(_table);
		}
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
			size_t i = 0;
			for (i = 0; i < PRIMECOUNT; i++)
			{
				if (primeList[i] > prime)
					return primeList[i];
			}
			return primeList[i];
		}
		//插入函数
		bool Insert(const pair<K, V>& kv)
		{
			//1、查看哈希表中是否存在该键值的键值对
			Node* ret = Find(kv.first);
			if (ret) //哈希表中已经存在该键值的键值对（不允许数据冗余）
			{
				return false; //插入失败
			}

			//2、判断是否需要调整哈希表的大小
			if (_n == _table.size()) //哈希表的大小为0，或负载因子超过1
			{
				//增容
				//a、创建一个新的哈希表，新哈希表的大小设置为原哈希表的2倍（若哈希表大小为0，则将哈希表的初始大小设置为10）
				HashFunc hf;
				vector<Node*> newtable;
				size_t newsize = _table.size() == 0 ? 10 : _table.size() * 2;
				newtable.resize(newsize);

				//newtable.resize(GetNextPrime(_table.size()));
				
				//b、将原哈希表当中的结点插入到新哈希表
				for (size_t i = 0; i < _table.size(); i++)
				{
					if (_table[i]) //桶不为空
					{
						Node* cur = _table[i];
						while (cur) //将该桶的结点取完为止
						{
							Node* next = cur->_next; //记录cur的下一个结点
							size_t index = hf(cur->_kv.first)%newtable.size(); //通过哈希函数计算出对应的哈希桶编号index（除数不能是capacity）
							//将该结点头插到新哈希表中编号为index的哈希桶中
							cur->_next = newtable[index];
							newtable[index] = cur;

							cur = next; //取原哈希表中该桶的下一个结点
						}
						_table[i] = nullptr; //该桶取完后将该桶置空
					}
				}
				//c、交换这两个哈希表
				_table.swap(newtable);
			}

			//3、将键值对插入哈希表
			HashFunc hf;
			size_t index = hf(kv.first) % _table.size(); //通过哈希函数计算出对应的哈希桶编号index（除数不能是capacity）
			Node* newnode = new Node(kv); //根据所给数据创建一个待插入结点
			//将该结点头插到新哈希表中编号为index的哈希桶中
			newnode->_next = _table[index];
			_table[index] = newnode;

			//4、哈希表中的有效元素个数加一
			_n++;
			return true;
		}
		//查找函数
		HashNode<K, V>* Find(const K& key)
		{
			if (_table.size() == 0) //哈希表大小为0，查找失败
			{
				return nullptr;
			}

			HashFunc hf;
			size_t index = hf(key) % _table.size(); //通过哈希函数计算出对应的哈希桶编号index（除数不能是capacity）
			//遍历编号为index的哈希桶
			HashNode<K, V>* cur = _table[index];
			while (cur) //直到将该桶遍历完为止
			{
				if (cur->_kv.first == key) //key值匹配，则查找成功
				{
					return cur;
				}
				cur = cur->_next;
			}
			return nullptr; //直到该桶全部遍历完毕还没有找到目标元素，查找失败
		}
		//删除函数
		bool Erase(const K& key)
		{
			//1、通过哈希函数计算出对应的哈希桶编号index（除数不能是capacity）
			HashFunc hf;
			size_t index = hf(key) % _table.size();
			//2、在编号为index的哈希桶中寻找待删除结点
			Node* prev = nullptr;
			Node* cur = _table[index];
			while (cur) //直到将该桶遍历完为止
			{
				if (cur->_kv.first == key) //key值匹配，则查找成功
				{
					//3、若找到了待删除结点，则删除该结点
					if (prev == nullptr) //待删除结点是哈希桶中的第一个结点
					{
						_table[index] = cur->_next; //将第一个结点从该哈希桶中移除
					}
					else //待删除结点不是哈希桶的第一个结点
					{
						prev->_next = cur->_next; //将该结点从哈希桶中移除
					}
					delete cur; //释放该结点
					//4、删除结点后，将哈希表中的有效元素个数减一
					_n--;
					return true; //删除成功
				}
				prev = cur;
				cur = cur->_next;
			}
			//假删除可能会导致迭代器失效
			
			return false; //直到该桶全部遍历完毕还没有找到待删除元素，删除失败
		}
	private:
		vector<Node*> _table;
		size_t _n;
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
		vector<string> v{ "苹果", "香蕉", "苹果", "榴莲", "苹果", "香蕉", "苹果", "香蕉", "苹果", "苹果"
			, "番茄", "橘子", "榴莲", "苹果", "香蕉", "苹果", "香蕉", "琵琶", "苹果" 
			, "香蕉", "葡萄", "榴莲", "菠萝", "香蕉", "西瓜", "香蕉", "草莓", "橙子" };
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
		HashTable<string, int> tmp(ht);
		//ht.~HashTable();
		auto ret = tmp.Find("香蕉");
		ret->_kv.second = 2022;

	}
}