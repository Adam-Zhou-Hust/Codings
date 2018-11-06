/**
 * 反转链表(注意审题，反转和倒序的区别，不要搞反)
 */

// 思路：画简图，分析反转中的每一步，节点的指针的指向的变化，基本思路就有了
// 需要主题的就是一些特殊的测试用例，提前想到输入的链表的形态
// 比如空链表，一个元素的链表，多元素的链表
// 提前考虑好这些，增加代码的健壮性
// 同时，由于尾节点编程了第一个节点，其next域一定要置nullprtr

#include <iostream>
#include "fig03_13.cpp"

// 非常丑陋的写法
// 远不如书上简洁，看来还是基本功不够扎实
// 下面再附上书中的简洁的思路


List ReverseList(List *list);


#ifndef BOOK
List ReverseList(List *list) {
	if (*list == nullptr) {
		cout << "List is empty" << endl;
		return nullptr;
	} 
	ListNode *reverse = *list;
	ListNode *currListNode = (*list)->next;
	(*list)->next = nullptr;
	while (currListNode != nullptr) {
		ListNode *tmp;
		tmp = currListNode->next;
		currListNode->next = reverse;
		reverse = currListNode;
		currListNode = tmp;
	}
	return reverse;
}
#else
// 书上比较简洁的实现(思路很清晰)
// 直接把链表一个节点，链表为空的情况也直接考虑到，避免了讨论，使得代码简洁统一
// 以后写代码即使有了思路也要再考虑下，能不能再让代码简洁统一些，能不能重构使得代码结构清晰
// 不要一有思路，直接乱写，写出来功能实现了，但是可读性太差，也不易维护

List ReverseList(List *list) {
	ListNode *prev = nullptr;
	ListNode *reverseHead = nullptr;
	ListNode *curr = *list;
	while (curr != nullptr) {
		ListNode *tmp = curr->next;
		curr->next = prev;
		if (curr->next == nullptr)
			reverseHead = curr; 
		prev = curr;
		curr = tmp;
	}
	return reverseHead;
}

#endif

void Test() {
	List list;
	CreateList(&list);
	cout << "before reverse :" << endl;
	PrintList(&list);
	list = ReverseList(&list);
	cout << "after reverse :" << endl;
	PrintList(&list);
}

int main(void) {
	Test();
}

