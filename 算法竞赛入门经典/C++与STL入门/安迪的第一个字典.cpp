#include <string>
#include <iostream>
#include <set>
#include <algorithm>
#include <vector>
#include <sstream>

using namespace std;

// 注意题目要求，不区分大小写

class Dictionary {
public:
	Dictionary(istream& is = cin);
	void Print(void) const;
private:
	set<string> wordSet;
private:
	static const int MOD = 5;
};

const int Dictionary::MOD;

Dictionary::Dictionary(istream& is) {
	string lineContent;
	string word;
	while (getline(cin, lineContent)) {
		istringstream input(lineContent);
		while (input >> word) {
			if (isupper(word[0]))
				word[0] = tolower(word[0]);
			wordSet.insert(word);
		}
	}
}

void Dictionary::Print(void) const {
	int count = 0;
	for_each(wordSet.begin(), wordSet.end(), [&count](const string& word) {
		if (!(count % MOD))
			cout << endl;
		cout << word << ' ';
	});
}

int main(void) {
	Dictionary dict;
	dict.Print();
	return 0;
}