#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stack>
#include <set>
#include <cassert>
using namespace std;

// 先用笨方法试一下

class setStack {
private:
	stack<multiset<string>> stk;
public:
	setStack() = default;
	void Push();
	void Dup();
	void Union();
	void Intersect();
	void Add();
	size_t Length() const;
	// 打印栈中的所有集合
	void PrintStack();
};

void setStack::Push() {
	// push直接放入空栈即可
	stk.push(multiset<string> ());
}

void setStack::Dup() {
	// dup操作则是复制栈顶元素，然后放入栈中
	assert(!stk.empty());
	auto t = stk.top();
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
		multiset<string> res;
		for (auto &var : s1) {
			if (s2.find(var) != s2.end()) {
				res.insert(var);
			}
		}
		stk.push(res);
	}
}

void setStack::Add() {
	// 添加操作
	assert(stk.size() >= 2);
	auto s1 = stk.top(); stk.pop();
	auto s2 = stk.top(); stk.pop();
	string s;
	for (auto it = s1.begin(); it != s1.end(); it++) {
		s.append(*it);
		s.append(",");
	}
	if (!s.empty()) {
		s.pop_back();
	}
	s2.insert("{" + s + "}");
	stk.push(s2);

}

size_t setStack::Length() const {
	return stk.size();
}

// 打印栈元素的思路，采用了递归的思路去做
// 从栈顶部开始打印
void setStack::PrintStack(){
	if (stk.empty()) {
		return;
	} else {
		auto s = stk.top(); stk.pop();
		cout << "{";
		string line;
		for (auto &var : s) {
			line.append(var);
			line.append(",");
		}
		// 去掉最后一个逗号
		if (!line.empty()) {
			line.pop_back();
		}
		cout << line;
		cout << "}" << endl;
		//接下来打印其他元素
		PrintStack();
		// 恢复原来的栈的内容
		stk.push(s);
	}
}

int main(void) {
	// 主要是操作的解析，然后调用相应接口即可
	setStack stk;
	string ops;
	while (cin >> ops) {
		if (ops[0] == 'P') {
			stk.Push();
		} else if (ops[0] == 'D') {
			stk.Dup();
		} else {
			if (ops[0] == 'U') stk.Union();
			if (ops[0] == 'I') stk.Intersect();
			if (ops[0] == 'A') stk.Add();
		}
		stk.PrintStack();
		cout << endl << endl;
	}
}

/**
 * 测试用例
 * PUSH
 * DUP
 * ADD
 * PUSH
 * ADD
 * DUP
 * ADD
 * DUP
 * UNION
 */

// 对应的输出

/**
{}              
                
                
{}              
{}              
                
                
{{}}            
                
                
{}              
{{}}            
                
                
{{},{}}         
                
                
{{},{}}         
{{},{}}         
                
                
{{{},{}},{},{}} 
                
                
{{{},{}},{},{}} 
{{{},{}},{},{}} 
                
                
{{{},{}},{},{}} 
**/