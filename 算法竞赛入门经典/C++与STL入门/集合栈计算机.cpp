#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stack>
#include <cassert>
using namespace std;

class setStack {
private:
	stack<set<string>> stk;
public:
	setStack() = default;
	void Push();
	void Dup();
	void Union();
	void Intersect();
	void Add();
	size_t Length() const;
};

void setStack::Push() {
	// push直接放入空栈即可
	stk.push(set<string> ());
}

void setStack::Dup() {
	// dup操作则是复制栈顶元素，然后放入栈中
	assert(!stk.empty());
	auto t = dup.top();
	stk.push(t);
}

void setStack::Union() {
	// 求集合的并集
	assert(stk.size() >= 2);
	auto s1 = stk.top(); stk.pop();
	auto s2 = stk.top(); stk.pop();
	// 判断s1 s2是否为空的情况
	if (s1.empty() || s2.empty()) {
		if (s1.empty()) {
			stk.push(s2);
		} else {
			stk.push(s1);
		}
	} else {
		// 求两非空集合的并集
		for (auto &var : s2) {
			if (s1.find(var) == s1.end()) {
				s1.insert(var);
			}
		}
		stk.push(s1);
	}
}

void setStack::Intersect() {
	// 求集合交集
	assert(stk.size() >= 2);
	auto s1 = stk.top(); stk.pop();
	auto s2 = stk.top(); stk.pop();
	if (s1.empty() || s2.empty()) {
		if (s1.empty()) {
			stk.push(s2);
		} else {
			stk.push(s1);
		}
	} else {
		// 求交集
		set<string> res;
		for (auto &var : s1) {
			if (s2.find(var) != s2.end()) {
				res.push(var);
			}
		}
		stk.push(res);
	}
}

void setStack::add() {
	// 添加操作
	assert(stk.size() >= 2);
	auto s1 = stk.top(); stk.pop();
	auto s2 = stk.top(); stk.pop();
	string s;
	for (auto it = s1.begin(); it != s1.end(); it++) {
		s.append(*it).append(",");
	}
	if (!s.empty()) {
		s.pop_back();
	}
	s2.push("{" + s + "}");
	stk.push(s2);

}

int main(void) {
	// 主要是操作的解析，然后调用相应接口即可
	setStack stk;
	string ops;
	while (cin >> ops) {

	}
}