/**
 * 从尾到头打印一个链表
 * 能够想到的方法有哪些？
 * 先顺序遍历，每个访问结果放入栈中，最后出栈
 * 利用递归的思路，比较简洁的方法---不足则是，如果链表非常长，递归深度会很大，栈开销，栈溢出要考虑到
 * 复习基本的链表操作
 */

// 暂时不考虑封装，所以我先把操作全部写成函数形式了
// 其次，考虑带头节点的链表
// 带头节点的链表，对于插入和删除的操作，代码比较清晰简洁，不用特意为链表完全为空的情况作出特殊处理

#include <vector>
#include <stack>
#include <iostream>
#include <initializer_list>

struct ListNode {
	int data;
	ListNode *next;
};

// 尾部插入法--针对带Head节点的链表的插入操作
void AddToTail(ListNode **List, int value) {
	// 创建新节点
	ListNode *pNode = new ListNode();
	pNode->data = value;
	pNode->next = nullptr;
	// 找到尾节点
	auto p = *List;
	while (p->next)
		p = p->next;
	// 元素插入
	p->next = pNode;
}

// 删除链表中的元素
void RemoveNode(ListNode **List, int value) {
	auto p = *List;
	while (p->next && p->next->data != value)
		p = p->next;
	if (!p) {
		std::cout << value << "不存在于链表中" << std::endl;
		return;
	} else {
		auto tmp = p->next;
		p->next = tmp->next;
		delete p;
	}
}

// 采取尾部插入法
// 特别要注意，栈变量和堆变量
// 栈变量出了作用域就被销毁，其值没有意义，因此不能再度引用栈变量的地址，会导致内存引用出错

ListNode ** InitList(std::initializer_list<int> il) {
	ListNode **list = new ListNode *;
	*list = new ListNode();
	(*list)->next = nullptr;
	for (auto it = il.begin(); it != il.end(); it++) {
		// std::cout << "插入" << *it << ' ';
		AddToTail(list, *it);
	}
	return list;
}

// 链表的销毁，释放内存空间
void DestroyList(ListNode **List) {
	auto it = *List;
	while (it) {
		auto tmp = it;
		it = it->next;
		delete tmp;
	}
	// 那个间接的指针也要销毁
	delete List;
}

#define RECUR
/**
 * 本题题目，从尾到头打印链表元素
 */
 // 使用栈
#ifndef RECUR

void PrintFromTail(ListNode **List) {
	// std::cout << "使用非递归函数" << std::endl;
	std::stack<ListNode *> nodeStack;
	// 注意链表由于是带有头节点的，因此头节点不要入栈，从第一个节点开始
	for (auto it = (*List)->next; it != nullptr; it = it->next)
		nodeStack.push(it);
	while (!nodeStack.empty()) {
		auto p = nodeStack.top();
		std::cout << p->data << '\t';
		nodeStack.pop();
	}
	// std::cout << "栈大小 "  << nodeStack.size() << std::endl;
}

#else 

// 使用递归函数
void PrintFromTail(ListNode **List) {
	if ((*List)->next) {
		PrintFromTail(&(*List)->next);
		std::cout << (*List)->next->data << '\t';
	} 
}

#endif

/**
 * 测试
 */

// 有一个坑点，我用的 zsh ，每次输出，自己不佳换行，就会末尾自动输出一个 % 
// 扰乱视线，以为是程序出了问题


int main(void) {
	ListNode **list = InitList({1,2,3,4,5,6,7,8,9});
	PrintFromTail(list);
	DestroyList(list);
	// std::cout << std::endl;
	return 0;
}