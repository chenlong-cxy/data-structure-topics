#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;

namespace CloseHash
{
	//ö�٣���ʶÿ��λ�õ�״̬
	enum State
	{
		EMPTY,
		EXIST,
		DELETE
	};
	//ÿ��λ�ó�����Ҫ�洢KV�ṹ�⣬����洢��λ�õ�ǰ��״̬
	//��ϣ��ÿ��λ�ô洢�Ľṹ
	template<class K, class V>
	struct HashData
	{
		pair<K, V> _kv;
		State _state = EMPTY; //״̬
	};
	//��keyͨ���÷º����õ�һ������ȡģ������
	template<class K>
	struct Hash
	{
		size_t operator()(const K& key)
		{
			return key;
		}
	};
	//string���͵��ػ��º�����string��key�Ƚϳ�����
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
	//��ϣ��
	template<class K, class V, class HashFunc=Hash<K>>
	class HashTable
	{
	public:
		//���뺯��
		bool Insert(const pair<K, V>& kv)
		{
			//1���鿴��ϣ�����Ƿ���ڸü�ֵ�ļ�ֵ��
			HashData<K, V>* ret = Find(kv.first);
			if (ret) //��ϣ�����Ѿ����ڸü�ֵ�ļ�ֵ�ԣ��������������ࣩ
			{
				return false; //����ʧ��
			}

			//2���ж��Ƿ���Ҫ������ϣ��Ĵ�С
			if (_table.size() == 0) //��ϣ���СΪ0
			{
				_table.resize(10); //���ù�ϣ���ʼ�ռ��С
			}
			else if ((double)_n / (double)_table.size() > 0.7) //�������Ӵ���0.7��Ҫ����
			{
				//����
				//a������һ���µĹ�ϣ���¹�ϣ��Ĵ�С����Ϊԭ��ϣ���2��
				HashTable<K, V, HashFunc> newHT;
				newHT._table.resize(2 * _table.size());
				//b����ԭ��ϣ���е����ݲ��뵽�¹�ϣ��
				for (auto& e : _table)
				{
					if (e._state == EXIST)
					{
						newHT.Insert(e._kv);
					}
				}
				//c��������������ϣ��
				_table.swap(newHT._table);
			}

			//3������ֵ�Բ����ϣ��
			HashFunc hf;
			size_t start = hf(kv.first)%_table.size(); //ͨ����ϣ���������ϣ��ַ������������capacity��
			size_t index = start;
			size_t i = 1;
			int base = index;
			//a���ҵ�һ��״̬ΪEMPTY��DELETE��λ��
			while (_table[index]._state == EXIST)
			{
				index = start + i; //����̽��
				//index = start + i*i; //����̽��
				index %= _table.size(); //��ֹ�±곬����ϣ��Χ
				i++;
			}
			//b�������ݲ����λ�ã�������λ�õ�״̬����ΪEXIST
			_table[index]._kv = kv;
			_table[index]._state = EXIST;
			
			//4����ϣ���е���ЧԪ�ظ�����һ
			_n++;
			return true;
		}
		//���Һ���
		HashData<K, V>* Find(const K& key)
		{
			if (_table.size() == 0) //��ϣ���СΪ0������ʧ��
			{
				return nullptr;
			}

			HashFunc hf;
			size_t start = hf(key) % _table.size(); //ͨ����ϣ���������ϣ��ַ������������capacity��
			size_t index = start;
			size_t i = 1;
			//ֱ���ҵ���λ��Ϊֹ
			while (_table[index]._state != EMPTY)
			{
				//����λ�õ�״̬ΪEXIST������keyֵƥ�䣬����ҳɹ�
				if (_table[index]._state == EXIST&&_table[index]._kv.first == key)
				{
					return &_table[index];
				}
				index = start + i; //����̽��
				//index = start + i*i; //����̽��
				index %= _table.size(); //��ֹ�±곬����ϣ��Χ
				i++;
			}
			return nullptr; //ֱ���ҵ���λ�û�û���ҵ�Ŀ��Ԫ�أ�����ʧ��
		}

		//ɾ������
		bool Erase(const K& key)
		{
			//1���鿴��ϣ�����Ƿ���ڸü�ֵ�ļ�ֵ��
			HashData<K, V>* ret = Find(key);
			if (ret)
			{
				//2�������ڣ��򽫸ü�ֵ������λ�õ�״̬��ΪDELETE����
				ret->_state = DELETE;
				//3����ϣ���е���ЧԪ�ظ�����һ
				_n--;
				return true;
			}
			return false;
		}
	private:
		vector<HashData<K, V>> _table; //��ϣ��
		size_t _n = 0; //��ϣ���е���ЧԪ�ظ���
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
	//	//vector<string> v{ "ƻ��", "�㽶", "ƻ��", "����", "ƻ��", "�㽶", "ƻ��", "�㽶", "ƻ��" };
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
	//ÿ����ϣͰ�д洢���ݵĽṹ
	template<class K, class V>
	struct HashNode
	{
		pair<K, V> _kv;
		HashNode<K, V>* _next;

		//���캯��
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
		//���캯��
		HashTable()
			:_n(0)
		{}
		//�������캯��
		HashTable(const HashTable<K, V>& ht)
		{
			//1���Ƚ�ԭ���Ĺ�ϣ���ͷ�
			_Destroy(_table);
			//2������ϣ��Ĵ�С����Ϊht._table�Ĵ�С
			_table.resize(ht._table.size());
			//3����ht._tableÿ��Ͱ���еĽ��һ�����������Լ��Ĺ�ϣ���У������
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
			//4�����Ĺ�ϣ���е���Ч���ݸ���
			_n = ht._n;
		}
		//��ֵ��������غ���
		HashTable<K, V>& operator=(const HashTable<K, V> ht)
		{
			_table.swap(ht._table);
			swap(_n, ht._n);
			return *this;
		}
		void _Destroy(vector<Node*>& v)
		{
			//����ϣ���еĽ��һ�����ͷ�
			for (size_t i = 0; i < v.size(); i++)
			{
				if (v[i]) //Ͱ��Ϊ��
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
		//��������
		~HashTable()
		{
			//�ͷŹ�ϣ��
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
		//���뺯��
		bool Insert(const pair<K, V>& kv)
		{
			//1���鿴��ϣ�����Ƿ���ڸü�ֵ�ļ�ֵ��
			Node* ret = Find(kv.first);
			if (ret) //��ϣ�����Ѿ����ڸü�ֵ�ļ�ֵ�ԣ��������������ࣩ
			{
				return false; //����ʧ��
			}

			//2���ж��Ƿ���Ҫ������ϣ��Ĵ�С
			if (_n == _table.size()) //��ϣ��Ĵ�СΪ0���������ӳ���1
			{
				//����
				//a������һ���µĹ�ϣ���¹�ϣ��Ĵ�С����Ϊԭ��ϣ���2��������ϣ���СΪ0���򽫹�ϣ��ĳ�ʼ��С����Ϊ10��
				HashFunc hf;
				vector<Node*> newtable;
				size_t newsize = _table.size() == 0 ? 10 : _table.size() * 2;
				newtable.resize(newsize);

				//newtable.resize(GetNextPrime(_table.size()));
				
				//b����ԭ��ϣ���еĽ����뵽�¹�ϣ��
				for (size_t i = 0; i < _table.size(); i++)
				{
					if (_table[i]) //Ͱ��Ϊ��
					{
						Node* cur = _table[i];
						while (cur) //����Ͱ�Ľ��ȡ��Ϊֹ
						{
							Node* next = cur->_next; //��¼cur����һ�����
							size_t index = hf(cur->_kv.first)%newtable.size(); //ͨ����ϣ�����������Ӧ�Ĺ�ϣͰ���index������������capacity��
							//���ý��ͷ�嵽�¹�ϣ���б��Ϊindex�Ĺ�ϣͰ��
							cur->_next = newtable[index];
							newtable[index] = cur;

							cur = next; //ȡԭ��ϣ���и�Ͱ����һ�����
						}
						_table[i] = nullptr; //��Ͱȡ��󽫸�Ͱ�ÿ�
					}
				}
				//c��������������ϣ��
				_table.swap(newtable);
			}

			//3������ֵ�Բ����ϣ��
			HashFunc hf;
			size_t index = hf(kv.first) % _table.size(); //ͨ����ϣ�����������Ӧ�Ĺ�ϣͰ���index������������capacity��
			Node* newnode = new Node(kv); //�����������ݴ���һ����������
			//���ý��ͷ�嵽�¹�ϣ���б��Ϊindex�Ĺ�ϣͰ��
			newnode->_next = _table[index];
			_table[index] = newnode;

			//4����ϣ���е���ЧԪ�ظ�����һ
			_n++;
			return true;
		}
		//���Һ���
		HashNode<K, V>* Find(const K& key)
		{
			if (_table.size() == 0) //��ϣ���СΪ0������ʧ��
			{
				return nullptr;
			}

			HashFunc hf;
			size_t index = hf(key) % _table.size(); //ͨ����ϣ�����������Ӧ�Ĺ�ϣͰ���index������������capacity��
			//�������Ϊindex�Ĺ�ϣͰ
			HashNode<K, V>* cur = _table[index];
			while (cur) //ֱ������Ͱ������Ϊֹ
			{
				if (cur->_kv.first == key) //keyֵƥ�䣬����ҳɹ�
				{
					return cur;
				}
				cur = cur->_next;
			}
			return nullptr; //ֱ����Ͱȫ��������ϻ�û���ҵ�Ŀ��Ԫ�أ�����ʧ��
		}
		//ɾ������
		bool Erase(const K& key)
		{
			//1��ͨ����ϣ�����������Ӧ�Ĺ�ϣͰ���index������������capacity��
			HashFunc hf;
			size_t index = hf(key) % _table.size();
			//2���ڱ��Ϊindex�Ĺ�ϣͰ��Ѱ�Ҵ�ɾ�����
			Node* prev = nullptr;
			Node* cur = _table[index];
			while (cur) //ֱ������Ͱ������Ϊֹ
			{
				if (cur->_kv.first == key) //keyֵƥ�䣬����ҳɹ�
				{
					//3�����ҵ��˴�ɾ����㣬��ɾ���ý��
					if (prev == nullptr) //��ɾ������ǹ�ϣͰ�еĵ�һ�����
					{
						_table[index] = cur->_next; //����һ�����Ӹù�ϣͰ���Ƴ�
					}
					else //��ɾ����㲻�ǹ�ϣͰ�ĵ�һ�����
					{
						prev->_next = cur->_next; //���ý��ӹ�ϣͰ���Ƴ�
					}
					delete cur; //�ͷŸý��
					//4��ɾ�����󣬽���ϣ���е���ЧԪ�ظ�����һ
					_n--;
					return true; //ɾ���ɹ�
				}
				prev = cur;
				cur = cur->_next;
			}
			//��ɾ�����ܻᵼ�µ�����ʧЧ
			
			return false; //ֱ����Ͱȫ��������ϻ�û���ҵ���ɾ��Ԫ�أ�ɾ��ʧ��
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
		vector<string> v{ "ƻ��", "�㽶", "ƻ��", "����", "ƻ��", "�㽶", "ƻ��", "�㽶", "ƻ��", "ƻ��"
			, "����", "����", "����", "ƻ��", "�㽶", "ƻ��", "�㽶", "����", "ƻ��" 
			, "�㽶", "����", "����", "����", "�㽶", "����", "�㽶", "��ݮ", "����" };
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
		auto ret = tmp.Find("�㽶");
		ret->_kv.second = 2022;

	}
}