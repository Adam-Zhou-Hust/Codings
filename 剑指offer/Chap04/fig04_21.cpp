// fig04_21.cpp

// 定义栈的数据结构，请在该类型中实现一个能够得到栈的最小元素的 min 函数
// 同时，调用 min push pop 的时间复杂度都是 O(1)

// 思考，一道栈数据结构的问题
// 特色在于利用 O(1) 时间复杂度完成栈的 pop push min 操作
// 最开始思路：想到利用一个额外的变量保存当前栈的最小值
// 但是一旦，出栈后，剩下栈中的最小值便不得而知，除非遍历，这样时间复杂度不满足要求
// 因此，单个的额外变量是不够的
// 考虑利用一个额外的辅助栈，从栈顶到栈底，依次保存当前栈的最小元素
// pop 掉最小元素后，剩下的辅助栈的栈顶则是 pop 后的当前数据栈中的最小元素

// 可以使用数学归纳法证明算法的正确性

#include <iostream>
#include <string>
#include <stack>
#include <cassert>


template <typename T>
class StackWithMin {
public:
	const T& min() const;
	void pop();
	void push(const T &);
	std::size_t size() const { return dataStack.size(); }
	bool empty() const { return dataStack.empty(); }
private:
	std::stack<T> dataStack;
	std::stack<T> minStack;
};

template <typename T>
const T& StackWithMin<T>::min() const {
	//std::assert(minStack.size() > 0);
	return minStack.top();
}

template <typename T>
void StackWithMin<T>::pop() {
	//std::assert(dataStack.size() > 0 && minStack.size() > 0);
	if (dataStack.top() == minStack.top())
		minStack.pop();
	dataStack.pop();
}

template <typename T>
void StackWithMin<T>::push(const T &e) {
	if (minStack.size() == 0 || e < minStack.top())
		minStack.push(e);
	dataStack.push(e);
}

int main(int argc, char **argv) {
	int val;
	StackWithMin<int> stk;
	while (std::cin >> val) 
		stk.push(val);
	std::cout << stk.min() << std::endl;
	return 0;
}