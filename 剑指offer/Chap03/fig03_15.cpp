/**
 * 输入一个链表，输出此链表中倒数第K个结点
 * 为了符合大多数人的习惯，本题从1开始计数
 */

// 主要考虑代码的健壮性
// 仅仅给出一个链表，倒数第K个结点，很可能结点根本是超出链表的长度而不存在
// 这一点必须要考虑到

// 其次，利用两次遍历固然可以完成题目，但是是否存在效率更高一些的办法呢？
// 实际上，对于存在N个节点的链表来说(我们先假设倒数第K个节点一定存在)，那么倒数第K个节点
// 也就是顺数的第N-K+1个节点
// 那么，在不知道N的情况下，仅仅利用一个指针，遍历一次，显然是不可能一步步走到N-k+1处的
// 显然，我们需要一个参照，或者计数的
// 这里我们应该想到，能否再度利用一个指针，和前一个指针具有K-1的间隔，那么，当其中一个指针走到
// 表尾，另一个也就到达了第N-K+1处，显然，我们利用一次遍历就找到相应的节点了

// 当然，要注意倒数第K个节点可能并不存在，在移动指针的过程中，适当的时间节点判断
// 同时，对于输入的K可能的取值为0 或者负数的情况，为了增加代码的健壮性，最好在代码里有所体现
// 不难得出下列代码

#include <iostream>
#include <string>
#include "fig03_13.cpp"
using namespace std;

/*
struct ListNode {
	int value;
	ListNode *next;
	ListNode(int _value = 0) :
		value(_value), next(nullptr) { }
};*/

ListNode *FindConverseK(List *list, int k) {
	if (*list == nullptr || k <= 0) 
		return nullptr;
	ListNode *first = *list;
	ListNode *second = *list;
	int i = 0;
	for (; i < k-1 && first != nullptr; i++) {
		first = first->next;
	}
	if (i != k-1) {
		// cout << "Converse K element dose not exist" << endl;
		return nullptr;
	}
	while (first->next != nullptr) {
		first = first->next;
		second = second->next;
	}
	return second;
}

int main(void) {
	List list;
	CreateList(&list);
	cout << "List : ";
	PrintList(&list);
	int k = 10;
	ListNode *result = FindConverseK(&list, k);
	if (result) {
		cout << "The converse K element is " << result->value << endl;
	} else {
        cout << "Converse K element dose not exist" << endl;
	}
	return 0;
}

// 思维扩展
// 实际上，两个指针解决的问题还可以有另外的应用

// 1.求链表中间的节点的指针，在两个指针的情况下，当其中一个指针到达中间，那么另外一个必然在尾节点
//   如何达到这个要求呢？显然是倍数关系，快的指针一次两步，慢的一次一步，接下来很显然。

// 2.判断一个单链表是否形成了环庄结构，显然是利用两个指针时，一个一次一步，另一个两步
//   就成了追及问题，指针已一快一慢，快的能追上慢的，则说明存在。
//   否则，如果快的的已经走到尾节点，还没追上过慢的，则说明，单链表不是环状
//   (注明:之所以指明单链表是因为单链表仅仅一个指针,不可能在链表中包含一个环，要么整个是一个环，要么不存在)







