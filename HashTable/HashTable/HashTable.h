#pragma once
#include <iostream>
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

	template<class K, class V>
	class HashTable
	{
	public:
		bool Insert(const pair<K, V> kv)
		{
			int index = kv.first%_table.size(); //������capacity
			size_t i = 1;
			while (_table[index]._state == EXIST)
			{
				index = i;
				index %= _table.size();
				i++;
			}
			_table[index]._kv = kv;
			_table[index]._state = EXIST;
			_n++;
			return true;
		}
	private:
		vector<HashData> _table;
		size_t _n = 0; //��ЧԪ�ظ���
	};
}