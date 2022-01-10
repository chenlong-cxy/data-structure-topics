#include "HashTable.h"
#include <unordered_map>

int main()
{
	CloseHash::TestHashTable3();
	//struct Stu
	//{
	//	int _id;
	//	string _name;
	//};
	//struct HashFunc
	//{
	//	int operator()(Stu s)
	//	{
	//		return s._id;
	//	}
	//};
	//struct HashPred
	//{
	//	bool operator()(Stu s1, Stu s2)
	//	{
	//		return s1._id == s2._id;
	//	}
	//};
	//vector<Stu> v{ { 1, "zhangsan" }, { 2, "lisi" }, { 2, "lisi" } };
	//unordered_map<Stu, int, HashFunc, HashPred> ht;
	//for (auto e : v)
	//{
	//	auto ret = ht.find(e);
	//	if (ret != ht.end())
	//	{
	//		ret->second++;
	//	}
	//	else
	//	{
	//		ht.insert(make_pair(e, 1));
	//	}
	//}
	return 0;
}