//#include <iostream>
//#include <string>
//#include <vector>
//using namespace std;
////前缀树
//class Trie {
//public:
//	//前缀树中每个结点的类型
//	struct TrieNode{
//		vector<TrieNode*> childPtr;
//		bool isEnd;
//		TrieNode()
//			:childPtr(26, nullptr)
//			, isEnd(false)
//		{}
//	};
//	/** Initialize your data structure here. */
//	Trie() {
//		root = new TrieNode;
//	}
//
//	/** Inserts a word into the trie. */
//	void insert(string word) {
//		TrieNode* cur = root;
//		for (auto ch : word)
//		{
//			if (cur->childPtr[ch - 'a'] == nullptr)
//				cur->childPtr[ch - 'a'] = new TrieNode;
//			cur = cur->childPtr[ch - 'a'];
//		}
//		cur->isEnd = true;
//	}
//
//	/** Returns if the word is in the trie. */
//	bool search(string word) {
//		TrieNode* ret = findEnd(word);
//		return ret != nullptr&&ret->isEnd == true;
//	}
//
//	/** Returns if there is any word in the trie that starts with the given prefix. */
//	bool startsWith(string prefix) {
//		return findEnd(prefix) != nullptr;
//	}
//private:
//	TrieNode* findEnd(string word)
//	{
//		TrieNode* cur = root;
//		for (auto ch : word)
//		{
//			if (cur->childPtr[ch - 'a'] == nullptr)
//				return nullptr;
//			cur = cur->childPtr[ch - 'a'];
//		}
//		return cur;
//	}
//	TrieNode* root; //前缀树根结点
//};
//int main()
//{
//	Trie t;
//	t.insert("dragon");
//	cout << t.search("dragon") << endl;
//	cout << t.startsWith("dra") << endl;
//	return 0;
//}


#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Trie {
	struct TrieNode {
		vector<TrieNode*> childPtr;
		bool isEnd;
		TrieNode()
			:childPtr(26, nullptr)
			, isEnd(false)
		{}
	};
public:
	Trie() {
		root = new TrieNode;
	}
	void insert(string word) {
		TrieNode* cur = root;
		for (auto ch : word) {
			if (cur->childPtr[ch - 'a'] == nullptr) {
				cur->childPtr[ch - 'a'] = new TrieNode;
			}
			cur = cur->childPtr[ch - 'a'];
		}
		cur->isEnd = true;
	}
	string findFirstPrefix(string word) {
		TrieNode* cur = root;
		size_t pos = 0;
		while (pos < word.size()) {
			if (cur->isEnd)
				break;
			if (cur->childPtr[word[pos] - 'a'] == nullptr)
				return word;
			cur = cur->childPtr[word[pos] - 'a'];
			pos++;
		}
		return word.substr(0, pos);
	}
private:
	TrieNode* root;
};
class Solution {
public:
	string replaceWords(vector<string>& dictionary, string sentence) {
		Trie t;
		for (auto& prefix : dictionary)
			t.insert(prefix);
		vector<string> words = splitSentence(sentence);
		string ret;
		for (int i = 0; i < words.size(); i++)
		{
			ret += t.findFirstPrefix(words[i]);
			ret += " ";
		}
		ret.resize(ret.size() - 1);
		return ret;
	}
	vector<string> splitSentence(string sentence) {
		vector<string> ret;
		size_t start = 0;
		size_t pos = sentence.find(' ', start);
		while (pos != string::npos) {
			string sub = sentence.substr(start, pos - start);
			ret.push_back(sub);
			start = pos + 1;
			pos = sentence.find(' ', start);
		}
		string sub = sentence.substr(start);
		ret.push_back(sub);
		return ret;
	}
};
int main()
{
	vector<string> dict = { "cat", "bat", "rat" };
	string sentence = "the cattle was rattled by the battery";
	cout << Solution().replaceWords(dict, sentence) << endl;
	return 0;
}


//class MagicDictionary {
//public:
//	struct TrieNode
//	{
//		vector<TrieNode*> childPtr;
//		bool isEnd;
//		TrieNode()
//			:childPtr(26, nullptr)
//			, isEnd(false)
//		{}
//	};
//	/** Initialize your data structure here. */
//	MagicDictionary() {
//		root = new TrieNode;
//	}
//
//	void buildDict(vector<string> dictionary) {
//		//将字典中的单词添加到前缀树当中
//		for (auto& word : dictionary)
//		{
//			TrieNode* cur = root;
//			for (auto ch : word)
//			{
//				if (cur->childPtr[ch - 'a'] == nullptr)
//					cur->childPtr[ch - 'a'] = new TrieNode;
//				cur = cur->childPtr[ch - 'a'];
//			}
//			cur->isEnd = true;
//		}
//	}
//
//	bool search(string searchWord) {
//		return dfs(root, 0, false, searchWord);
//	}
//	//当前遍历到的前缀树结点  当前比较的字符串字符的位置  是否已经变换过一个字符  用于比较的字符串
//	bool dfs(TrieNode* node, int pos, bool isChanged, const string& searchWord)
//	{
//		if (pos == searchWord.size()) //无论是否找到匹配单词，都应该结束递归
//			return isChanged&&node->isEnd; //已经变换过一个字符，并且当前前缀树节点是一个结束结点
//		if (node->childPtr[searchWord[pos] - 'a'])
//		{
//			if (dfs(node->childPtr[searchWord[pos] - 'a'], pos + 1, isChanged, searchWord))
//				return true;
//		}
//		if (isChanged == false)
//		{
//			for (int i = 0; i < 26; i++)
//			{
//				if (i != searchWord[pos] - 'a'&&node->childPtr[i])
//				if (dfs(node->childPtr[i], pos + 1, true, searchWord))
//					return true;
//			}
//		}
//		return false;
//	}
//private:
//	TrieNode* root;
//};
