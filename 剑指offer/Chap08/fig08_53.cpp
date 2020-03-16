// 正则表达式的匹配
// 匹配含有.和*的正则表达式

// 思路
// 可以使用递归也可以使用迭代
// 给出递归的匹配思路
// 对于当前字符，如果matcher和pattern都到了末尾的'\0'则说明匹配完成并且匹配成功
// 如果pattern到了空字符，但是matcher还没完成，则必然是匹配失败
// 以上是递归的两种基准情况

// 现在考虑特殊元字符的匹配
// 考虑下一个字符是否是 * 字符
// 不是，则按照规则匹配当前字符，然后递归即可
// 如果下一个字符是 * 字符，则当前字符可以不匹配或者匹配多次，然后再递归执行
// 注意下一个字符是 * 同时当前字符是 .的情况
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

class Solution {
public:
	bool isMatch(string s, string p);
	bool dfs(string matcher, string pattern);
};

bool Solution::isMatch(string s, string p) {
	return dfs(s, p);
}

bool Solution::dfs(string matcher, string pattern) {
	// 基准情况，当pattern和matcher同时为空，匹配完成
	// 当pattern为空，但是matcher不为空，匹配失败
	if (pattern.empty())
		return matcher.empty();
	// 考虑pattern的当前字符的下一个字符不是*，下一个字符也可能并不存在
	if (pattern.size() == 1 || pattern[1] != '*') {
		if (matcher.empty())
			return false;
		if (pattern[0] == '.' || matcher[0] == pattern[0])
			return dfs(matcher.substr(1), pattern.substr(1));
		return false;
	}
	// 说明pattern下一个字符一定存在并且为*通配字符
	// 则考虑当前matcher字符可以乎略，可以匹配一次，也可以匹配多次
	if (matcher.empty())
		return dfs(matcher, pattern.substr(2));

	if (pattern[0] != '.' && pattern[0] != matcher[0])
		return dfs(matcher.substr(1), pattern.substr(2));
	else
		return dfs(matcher.substr(1), pattern.substr(2)) ||
			   dfs(matcher.substr(1), pattern) ||
			   dfs(matcher, pattern.substr(2));
}

int main(void) {
	string matcher, pattern;
	Solution solution;
	while (cin >> matcher >> pattern)
		cout << solution.isMatch(matcher, pattern) << endl;
	return 0;
}