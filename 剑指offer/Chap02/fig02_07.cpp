/**
 * 利用两个栈实现一个队列
 * 要求队列实现两个函数
 * appendTail deleteHead 
 * 队列尾部插入 队列头部删除
 */

// 思路：
// 栈 FILO 队列 FIFO
// 这种问题可以先模拟一下，现在两个栈，假设连续插入三个元素到一个栈，那么现在要出队，则必然是栈底的元素
// 就要一直pop ,直到栈底元素出来，这个栈底相当于队头，而前面pop出来的，不需要删除的元素，放到另一个栈
// 恰好，这些元素 改变了次序，出栈的顺序和队列顺序是一样的了
// 思路就出来了，一个栈用于插入，一个栈用作删除，插入直接插入插入栈
// 删除则，先判断删除栈是否空，非空直接pop ,为空，则把插入栈元素全部pop到删除栈，最后删除栈pop，即为所求

#include <stack>
#include <iostream>
#include <string>

template <typename T>
class ZqQueue {
public:
	bool empty() const;
	ZqQueue() = default;
	void appendTail(const T &);
	T deleteHead();
private:
	std::stack<T> input;
	std::stack<T> output;
};

template <typename T>
bool ZqQueue<T>::empty() const {
	return input.empty() && output.empty();
}

template <typename T>
void ZqQueue<T>::appendTail(const T &t) {
	input.push(t);
}

template <typename T>
T ZqQueue<T>::deleteHead() {
	if (output.empty()) {
		if (input.empty()) 
			throw std::runtime_error("ZqQueue is empty");
		else {
			while (!input.empty()) {
				T tmp = input.top();
				input.pop();
				output.push(tmp);
			}
		}
	}
	T t = output.top();
	output.pop();
	return t;
}


// =========================测试===========================
int main(void) {
	std::string arr[] = {"CppPrimer", "Java", "Apue", "Csapp", "TCP/IP"};
	ZqQueue<std::string> queue;
	for (auto it = std::begin(arr); it != std::end(arr); it++)
		queue.appendTail(*it);
	while (!queue.empty()) 
		std::cout << queue.deleteHead() << '\t';
	std::cout << std::endl;
	return 0;
}