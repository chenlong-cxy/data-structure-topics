//#include <iostream>
//#include <string>
//#include <vector>
//using namespace std;
////ǰ׺��
//class Trie {
//public:
//	//ǰ׺����ÿ����������
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
//	TrieNode* root; //ǰ׺�������
//};
//int main()
//{
//	Trie t;
//	t.insert("dragon");
//	cout << t.search("dragon") << endl;
//	cout << t.startsWith("dra") << endl;
//	return 0;
//}


//#include <iostream>
//#include <string>
//#include <vector>
//using namespace std;
//
//class Trie {
//	struct TrieNode {
//		vector<TrieNode*> childPtr;
//		bool isEnd;
//		TrieNode()
//			:childPtr(26, nullptr)
//			, isEnd(false)
//		{}
//	};
//public:
//	Trie() {
//		root = new TrieNode;
//	}
//	void insert(string word) {
//		TrieNode* cur = root;
//		for (auto ch : word) {
//			if (cur->childPtr[ch - 'a'] == nullptr) {
//				cur->childPtr[ch - 'a'] = new TrieNode;
//			}
//			cur = cur->childPtr[ch - 'a'];
//		}
//		cur->isEnd = true;
//	}
//	string findFirstPrefix(string word) {
//		TrieNode* cur = root;
//		size_t pos = 0;
//		while (pos < word.size()) {
//			if (cur->isEnd)
//				break;
//			if (cur->childPtr[word[pos] - 'a'] == nullptr)
//				return word;
//			cur = cur->childPtr[word[pos] - 'a'];
//			pos++;
//		}
//		return word.substr(0, pos);
//	}
//private:
//	TrieNode* root;
//};
//class Solution {
//public:
//	string replaceWords(vector<string>& dictionary, string sentence) {
//		Trie t;
//		for (auto& prefix : dictionary)
//			t.insert(prefix);
//		vector<string> words = splitSentence(sentence);
//		string ret;
//		for (int i = 0; i < words.size(); i++)
//		{
//			ret += t.findFirstPrefix(words[i]);
//			ret += " ";
//		}
//		ret.resize(ret.size() - 1);
//		return ret;
//	}
//	vector<string> splitSentence(string sentence) {
//		vector<string> ret;
//		size_t start = 0;
//		size_t pos = sentence.find(' ', start);
//		while (pos != string::npos) {
//			string sub = sentence.substr(start, pos - start);
//			ret.push_back(sub);
//			start = pos + 1;
//			pos = sentence.find(' ', start);
//		}
//		string sub = sentence.substr(start);
//		ret.push_back(sub);
//		return ret;
//	}
//};
//int main()
//{
//	vector<string> dict = { "cat", "bat", "rat" };
//	string sentence = "the cattle was rattled by the battery";
//	cout << Solution().replaceWords(dict, sentence) << endl;
//	return 0;
//}


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
//		//���ֵ��еĵ�����ӵ�ǰ׺������
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
//	//��ǰ��������ǰ׺�����  ��ǰ�Ƚϵ��ַ����ַ���λ��  �Ƿ��Ѿ��任��һ���ַ�  ���ڱȽϵ��ַ���
//	bool dfs(TrieNode* node, int pos, bool isChanged, const string& searchWord)
//	{
//		if (pos == searchWord.size()) //�����Ƿ��ҵ�ƥ�䵥�ʣ���Ӧ�ý����ݹ�
//			return isChanged&&node->isEnd; //�Ѿ��任��һ���ַ������ҵ�ǰǰ׺���ڵ���һ���������
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

//#include <iostream>
//#include <unordered_map>
//#include <string>
//#include <vector>
//using namespace std;
//
////class Solution {
////public:
////	struct TrieNode
////	{
////		vector<TrieNode*> childPtr;
////		bool isEnd;
////		TrieNode()
////			:childPtr(26, nullptr)
////			, isEnd(false)
////		{}
////	};
////	int minimumLengthEncoding(vector<string>& words) {
////		int ret = 0;
////		TrieNode* root = new TrieNode;
////		for (auto& word : words)
////		{
////			TrieNode* cur = root;
////			int len = 1;
////			bool isNewPath = false;
////			for (int i = word.size() - 1; i >= 0;i--)
////			{
////				char ch = word[i];
////				if (cur->childPtr[ch - 'a'] == nullptr)
////				{
////					cur->childPtr[ch - 'a'] = new TrieNode;
////					isNewPath = true;
////				}
////				cur = cur->childPtr[ch - 'a'];
////				len++;
////				if (cur->isEnd&&i != 0)
////				{
////					ret -= len;
////					cur->isEnd = false;
////				}
////			}
////			if (isNewPath)
////			{
////				ret += len;
////				cur->isEnd = true;
////			}
////		}
////		return ret;
////	}
////};
//class TrieNode {
//	vector<TrieNode*> childPtr;
//public:
//	int count;
//	TrieNode()
//		:childPtr(26, 0)
//		, count(0)
//	{}
//	TrieNode* getNext(char ch)
//	{
//		if (childPtr[ch - 'a'] == nullptr)
//		{
//			childPtr[ch - 'a'] = new TrieNode;
//			count++; //�ý��ĺ�������
//		}
//		return childPtr[ch - 'a'];
//	}
//};
//class Solution {
//public:
//	int minimumLengthEncoding(vector<string>& words) {
//		unordered_map<TrieNode*, int> um; //��Ӧ����ǵڼ�������
//		TrieNode* root = new TrieNode;
//		for (int i = 0; i < words.size(); i++)
//		{
//			TrieNode* cur = root;
//			string word = words[i];
//			for (int j = word.size() - 1; j >= 0; j--)
//			{
//				cur = cur->getNext(word[j]);
//			}
//			um[cur] = i;
//		}
//		int ret = 0;
//		for (auto[node, index] : um) //C++17
//		{
//			if (node->count == 0) //Ҷ�ӽ��
//				ret += words[index].size() + 1;
//		}
//		return ret;
//	}
//};
//int main()
//{
//	vector<string> words = { "time", "atime", "btime" };
//	cout << Solution().minimumLengthEncoding(words) << endl;
//	return 0;
//}

//class MapSum {
//public:
//	struct TrieNode {
//		vector<TrieNode*> childPtr;
//		bool isEnd;
//		TrieNode()
//			:childPtr(26, nullptr)
//			, isEnd(false)
//		{}
//	};
//	/** Initialize your data structure here. */
//	MapSum() {
//		root = new TrieNode;
//	}
//
//	void insert(string key, int val) {
//		TrieNode* cur = root;
//		for (auto ch : key)
//		{
//			if (cur->childPtr[ch - 'a'] == nullptr)
//				cur->childPtr[ch - 'a'] = new TrieNode;
//			cur = cur->childPtr[ch - 'a'];
//		}
//		cur->isEnd = true;
//		um[cur] = val;
//	}
//
//	int sum(string prefix) {
//		TrieNode* cur = root;
//		for (auto ch : prefix)
//		{
//			if (cur->childPtr[ch - 'a'] == nullptr)
//				cur->childPtr[ch - 'a'] = new TrieNode;
//			cur = cur->childPtr[ch - 'a'];
//		}
//		return dfs(cur);
//	}
//	int dfs(TrieNode* cur)
//	{
//		int ret = 0;
//		if (cur->isEnd)
//			ret += um[cur];
//		for (int i = 0; i < 26; i++)
//		{
//			if (cur->childPtr[i])
//				ret += dfs(cur->childPtr[i]);
//		}
//		return ret;
//	}
//private:
//	TrieNode* root;
//	unordered_map<TrieNode*, int> um;
//};
//class MapSum {
//public:
//	struct TrieNode {
//		vector<TrieNode*> childPtr;
//		int val;
//		TrieNode()
//			:childPtr(26, nullptr)
//			, val(0)
//		{}
//	};
//	/** Initialize your data structure here. */
//	MapSum() {
//		root = new TrieNode;
//	}
//
//	void insert(string key, int val) {
//		int addVal = val;
//		if (um.count(key))
//			addVal -= um[key]; //���val��֮ǰ��ֵС�����൱��Ҫ��ȥ��ֵ
//		um[key] = val; //��������
//		TrieNode* cur = root;
//		for (auto ch : key) {
//			if (cur->childPtr[ch - 'a'] == nullptr)
//				cur->childPtr[ch - 'a'] = new TrieNode;
//			cur = cur->childPtr[ch - 'a'];
//			cur->val += addVal;
//		}
//	}
//
//	int sum(string prefix) {
//		TrieNode* cur = root;
//		for (auto ch : prefix) {
//			if (cur->childPtr[ch - 'a'] == nullptr)
//				return 0; //��������prefixΪǰ׺��key
//			cur = cur->childPtr[ch - 'a'];
//		}
//		return cur->val;
//	}
//private:
//	TrieNode* root;
//	unordered_map<string, int> um;
//};

////�������
//class Solution {
//public:
//	int findMaximumXOR(vector<int>& nums) {
//		int x = 0;
//		for (int k = 30; k >= 0; k--) //31������λ
//		{
//			unordered_set<int> us; //��ÿ������ǰ31-k������λ�����
//			for (auto num : nums) {
//				us.insert(num >> k);
//			}
//			int next_x = (x << 1) + 1; //����x�ĵ�kλ��1
//			bool flag = false;
//			for (auto num : nums) {
//				if (us.count(next_x ^ (num >> k))) {
//					flag = true;
//					break;
//				}
//			}
//			if (flag)
//				x = next_x;
//			else
//				x = next_x - 1; //���費��������kλ����Ϊ0
//		}
//		return x;
//	}
//};
//class Solution {
//public:
//	struct TrieNode {
//		TrieNode* left = nullptr; //0
//		TrieNode* right = nullptr; //1
//	};
//	int findMaximumXOR(vector<int>& nums) {
//		TrieNode* root = new TrieNode;
//		for (auto num : nums) {
//			TrieNode* cur = root;
//			for (int k = 30; k >= 0; k--) {
//				if ((num >> k) & 1) { //1������
//					if (cur->right == nullptr)
//						cur->right = new TrieNode;
//					cur = cur->right;
//				}
//				else { //0������
//					if (cur->left == nullptr)
//						cur->left = new TrieNode;
//					cur = cur->left;
//				}
//			}
//		}
//		int maxXor = 0;
//		for (auto num : nums) {
//			TrieNode* cur = root;
//			int x = 0;
//			for (int k = 30; k >= 0; k--) {
//				bool flag = false;
//				if ((num >> k) & 1) { //1����������
//					if (cur->left) {
//						flag = true;
//						cur = cur->left;
//					}
//					else
//						cur = cur->right;
//				}
//				else { //0����������
//					if (cur->right) {
//						flag = true;
//						cur = cur->right;
//					}
//					else
//						cur = cur->left;
//				}
//				x *= 2;
//				if (flag)
//					x += 1;
//			}
//			maxXor = max(maxXor, x);
//		}
//		return maxXor;
//	}
//};
