// 求两个链表的第一个公共结点问题
// 首先明确一点，两个链表如果存在公共结点，那么在公共结点之后
// 两个链表的路径都是一致的，也就是形态上是之(Y形)字形，而不会是X形态
// 暴力破解我们可以直接不考虑，时间复杂度高，效率低
// 考虑两个链表的长度可能不一致，再联想到快慢指针的应用
// 先遍历两个链表，分别求其长度
// 让长链表的指针先走k步，然后两个链表的指针再一起走，从而保证一定会在
// 第一个公共结点相遇，从而得到结果

// 另一个思路
// 设置两个保存路径的栈，分别遍历两个链表，分别保存
// 显然，两个链表后半部分的路径一致
// 当两个链表遍历完成后，我们的到两个路径栈
// 分别出栈，比较，遇到第一个不同的路径结点，则说明，上一个出栈的
// 就是第一个公共结点

// 根据以上两种思路，可以分别写出如下代码

#include <iostream>
#include <string>
#include <stack>
using namespace std;

struct ListNode {
	int m_nKey;
	ListNode *m_pNext;
};

int getSizeOfList(const ListNode *lst) {
	const ListNode *p = lst;
	if (p == nullptr)
		return 0;
	int count = 0;
	while (p) {
		p = p->m_pNext;
		count++;
	}
	return count;
}

ListNode *findFirstCommonNode(const ListNode *lst1, const ListNode *lst2) {
	int lst1Length = getSizeOfList(lst1);
	int lst2Length = getSizeOfList(lst2);
	int diffOfLength = lst1Length - lst2Length;
	ListNode *p1 = lst1;
	ListNode *p2 = lst2;

	// 长的链表先走若干步
	if (diffOfLength > 0) {
		while(diffOfLength) {
			p1 = p1->m_pNext;
			diffOfLength--;
		} 
	} else {
		while (diffOfLength) {
			p2 = p2->m_pNext;
			diffOfLength++;
		}
	}
	// 齐步走
	while (p1 && p2 && p1 != p2) {
		p1 = p1->m_pNext;
		p2 = p2->m_pNext;
	}

	return p1;
}

// 思路二：利用栈保存遍历链表的路径

ListNode *findFirstCommonNode(const *lst1, const ListNode *lst2) {
	stack<ListNode *> lst1Path;
	stack<ListNode *> lst2Path;
	ListNode *p1 = lst1;
	ListNode *p2 = lst2;
	while (p1) {
		lst1Path.push(p1);
		p1 = p1->m_pNext;
	}
	while (p2) {
		lst2Path.push(p2);
		p2 = p2->m_pNext;
	}

	// 开始比较路径
	ListNode *preNode = nullptr;
	while (!lst1Path.empty() && !lst2Path.empty()) {
		p1 = lst1Path.top();
		p2 = lst1Path.top();
		lst1Path.pop();
		lst2Path.pop();
		if (p1 == p2)
			preNode = p1;
		else
			break;
	}
	return preNode;
}
