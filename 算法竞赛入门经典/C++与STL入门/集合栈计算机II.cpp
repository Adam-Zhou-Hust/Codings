#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
using namespace std;

#define ALL(x) x.begin(), x.end()
#define INS(x) inserter(x, x.begin())

typedef set<int> Set;
map<Set, int> IDCache; // 把集合映射成ID
vector<Set> SetCache;  // 根据ID取集合

// 查找给定集合x的ID，如果找不到，则分配一个新的ID
int ID(Set x) {
	// 查找Cache中是否已经映射了这个集合
	if (IDCache.find(x) != IDCache.end()) {
		return IDCache[x];
	}
	// 说明，集合之前还没有映射到ID
	return IDCache[x] = SetCache.size() - 1;
}

// 本题的思路则是，由于题目中，栈中的元素是集合的集合，如果暴力操作，不是很方便
// 文中的做法则是，让每个集合拥有唯一的ID标识
// 这样题目中定义的ADD操作就能很方便的实现
// 其他的集合的交，并操作本身STL也有提供接口

int main(int argc, char **argv) {
	int t;
	cin >> t;
	while (t--) {
		stack<int> s;
		int n;
		cin >> n;
		for (int i = 0; i < n; i++) {
			string op;
			cin >> op;
			if (op[0] == 'P') {
				s.push(ID(Set()));
			} else if (op[0] == 'D') {
				s.push(s.top());
			} else {
				Set x1 = SetCache[s.top()]; s.pop();
				Set x2 = SetCache[s.top()]; s.pop();
				Set x;
				if (op[0] == 'U') {
					set_union(ALL(x1), ALL(x2), INS(x));
				} else if (op[0] == 'I') {
					set_intersaction(ALL(x1), ALL(x2), INS(x));
				} else if (op[0] == 'A') {
					x = x2;
					x.insert(ID(x1));
				}
				s.push(ID(x));
			}
		}
	} 
	cout << SetCache[s.top()].size() << endl;
}