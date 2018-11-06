// fig04_22.cpp

// 判断栈的输出是否合法
// 给定一个输入序列，判断输出序列是否是这个输入序列压入栈后的一个合法输出
// 刚开始看到题目，肯定一下子没有思路或者思路并不清晰
// 对于栈，我们知道，后进先出这一约束，但是实际上，如果输入顺序12345
// 输出也可能是12345,仍然是合理的
// 岂不是不满足LIFO的约束？并不是，因为并没有说一起入栈的数据要一次性全部进入
// 然后一次性全部输出
// 因此，LIFO 实际上的约束是指，一次性进入栈的一系列数，在逐个出栈后
// 满足 LIFO 关系
// 考虑下，手动判断给定的输入序列是否合法时执行的一些步骤或者说是思考过程
// 首先，判断给定输出的第一个元素，考虑在对应的输入序列中，这个元素之前是否还存在
// 数据，如果存在，那么这些数据肯定还在栈中没有输出(因为栈的LIFO)
// 那么，这部分连同第一个输出元素一起入栈，再把这个元素弹出作为第一个输出
// 接下来的过程类似
// 考虑第二个输出，及其在输入中的位置，第二个输出元素可能是已经在栈中的数据
// 也可能是还没有入栈的数据
// 如果是已经入栈的，根据 LIFO 这个元素必然是栈顶元素，如果是还没有输入的，则继续
// 把第二个输出元素在输入序列中的位置以及它之前的数据再入栈，直到遇到第二个输出元素
// 如果在输入队列中遇到第二个输出元素之前就已经消耗完毕，那么可以肯定，输出是不合法的
// 然后从栈中弹出这个元素
// 依次执行下去
// 当输入已经消耗完时，剩余输出序列和栈中元素的出栈序列应该是一致的
// 否则，说明输入是不合法的

// 综合上述，就能判断给定的输出是否合法

#include <iostream>
#include <stack>
using namespace std;

bool isValid(const int *input, const int *output, int length) {
	bool result = false;
	if (input && output && length > 0) {
		const int *currInput = input;
		const int *currOutput = output;
		stack<int> ostk;
		while (currOutput != output + length) {
			while (ostk.empty() || ostk.top() != *output) {
				if (currInput == input + length)
					break;
				ostk.push(*currInput++)
			}
			if (ostk.top() != *output)
				break;
			ostk.pop();
			output++;
		}
		if (ostk.empty() && currOutput == output + length)
			result = true;
	}
	return result;
}
