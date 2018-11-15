#include <iostream>
#include <map>
#include <algorithm>
#include <vector>
#include <string>
#include <set>
using namespace std;

// 找单词集合，保证集合中，针对每个单词，对其字符重排序，都不能在原词语集合中找到（忽略大小写的差异）
// 思路：保存输入的单词，

class Solution {
public:
	Solution();
	set<string> findAnanagrams();
	string uniform(const string& word);
private:
	vector<string> wordSet;
	map<string, int> cnt;
};

Solution::Solution() {
	string word;
	while (cin >> word) {
		wordSet.push_back(word);
		if (cnt.find(uniform(word)) == cnt.end()) {
			cnt[uniform(word)] = 0;
		}
		cnt[uniform(word)]++;
//		cnt[uniform(word)]++;
	}
}

// 问题中说的是，单词字符忽略大小重组后不能重合
// 实际上主要考虑两者的字符集不一样就行，因此一个tricky的做法就是，先把单词字符全部变成小写
// 然后重排序即可
string Solution::uniform(const string& word) {
	string ret = word;
	for (int i = 0; i < ret.size(); i++) {
		ret[i] = tolower(ret[i]);
	}
	sort(ret.begin(), ret.end());
	return ret;
}

set<string> Solution::findAnanagrams() {
	set<string> ret;
	for (int i = 0; i < wordSet.size(); i++) {
		if (cnt[uniform(wordSet[i])] == 1) {
			ret.insert(wordSet[i]);
		}
	}
	return ret;
}

int main(void) {
	Solution solution;
	set<string> ret = solution.findAnanagrams();
	for_each(ret.begin(), ret.end(), [] (const string& word) {
		cout << word << endl;
	});
	return 0;
}