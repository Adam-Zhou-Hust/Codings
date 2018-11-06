/**
 * 在 O(1) 时间内删除链表的结点
 */

// 按照传统的思路，删除一个节点，先进行遍历，找到节点的前一个节点，然后才能执行删除操作，
// 因此时间复杂度为 O(n), 显然，为了找到时间复杂度更加优的算法，遍历的思路并不适用

// 换一种思路，链表的节点中对用户有效的信息是数据域，删除则是不需要这些信息
// 那么把下一个节点的信息部分存储在这个将要删除的节点(也就是用下个节点的信息替换将要删除的节点的信息)
// 先做一个逻辑上的删除，那么下个节点就空出来了，把本节点的删除改变为下一个节点的删除

// 从而不需要遍历链表找到前一个节点，但是仅仅针对不是删除尾节点的情况
// 如果删除尾节点，还是得从头遍历到此节点的前序节点才能删除
// 实践复杂度，从 O(n) -> O(1)

// 同时，对于链表的设计考虑好 是否带头节点
// 对于测试用例，考虑功能 边界  负面测试 (空链表 单个节点链表 删除尾节点 删除首元素节点等)

// 实际上，上述的思路也是并不完善的，因为单独给定一个结点指针，这个节点是否在链表中
// 我们仍然只能通过遍历才能确定，上述时间复杂度为O(1)的算法的前提，就是我们要保证
// 给定的结点是存在于给定的链表中的


#include <iostream>
#include <string>
#include <cassert>
using namespace std;

struct ListNode {
	int value;
	ListNode *next;
	ListNode(int _value = 0) :
		value(_value), next(nullptr) { }
};

// 这里考虑不带头节点的链表结构的节点删除实现

typedef struct ListNode *List;

void DeleteNode(List *list, ListNode *p) {
	if (*list == nullptr || p == nullptr)
		return;
	// 删除非尾部节点(此时，链表节点个数显然不为1)
	if (p->next != nullptr) {
		p->value = p->next->value;
		auto tmp = p->next;
		p->next = p->next->next;
		delete tmp;
	} else {
		// log debug : cout << "来到单个节点删除部分" << endl;
		// 删除的是尾部节点，只能从头遍历
		// 并且分情况讨论---单独一个节点的链表，其尾节点恰好也是头节点
		//             ---非单独一个节点的链表，常规处理
		struct ListNode *tmp = *list;
		while (tmp != p && tmp->next != p) 
			tmp = tmp->next;
		if (tmp == p) {    // 说明链表只有单个节点
			*list = nullptr;
			delete p;
		} else {
			tmp->next = nullptr;
			delete p;
		}
	}
}

// 采取尾部插入法
void CreateList(List *list) {
	int val;
    struct ListNode *tail;
	 
	// 插入第一个元素
	if (!(cin >> val)) {
		cout << "Invalid input" << endl;
		*list = nullptr;
		return;
	}
	struct ListNode *pnode = new struct ListNode;
	pnode->value = val;
	pnode->next = nullptr;
	// tail = *list = pnode;   // 这里非法内存访问了,list是否指向一个对象不得而知就解引用
	*list = pnode;
	tail = pnode;
	// 仍有后续元素，则插入
	while (cin >> val) {
		pnode = new struct ListNode;
		pnode->value = val;
		pnode->next = nullptr;
		tail->next = pnode;
		tail = pnode;
	}
}

void DestroyList(List *list) {
	// assert((*list) != nullptr);
	if (*list) {
		auto p = *list;
		struct ListNode *tmp = nullptr;
		while (p) {
			tmp = p;
			p = p->next;
			delete tmp;
		}
	}
}

void PrintList(List *list) {
	// assert((*list) != nullptr);
	if (*list) {
		auto p = *list;    // p point to first element
		while (p) {
			cout << p->value << "\t";
			p = p->next;
		}
	}
	cout << endl;
}
/*
void Test() {
	List list = nullptr;
	CreateList(&list);
	PrintList(&list);
	DeleteNode(&list, list);
	PrintList(&list);
	DestroyList(&list);
}
*/
/*
int main(int argc, char **argv) {
	Test();
	return 0;
}*/
