/**
 * 合并排序的链表
 */

// 很容易想到和二路归并排序中的Merge操作相类似
// 也是把有序的两个列合并成一个有序的列，但是排序中，基本上是数组，此题则是链表
// 因此，对于数组，我们一般使用额外空间，把合并结果放在新的空间
// 但是链表这样做效率比较低
// 因此，操作肯定涉及很多指针之间的操作，一定要小心
// 第一，指针访问不能越界
// 第二，注意不要使得链表断裂
// 第三，考虑各种测试用例 ---- 比如一方为空链表，双方都是空链表，链表元素个数为一个
// 针对以上情况，代码要具备健壮性

// 画简图分析好合并过程中的指针指向的变化

#include <iostream>
#include "fig03_13.cpp"
using namespace std;

// #define RECURRSION

// 迭代思路
// 1.0 版本 及其简陋，不忍直视的垃圾代码
#ifndef RECURRSION
List MergeList(List *first, List *second) {
	// 先处理特殊情况，两个链表均为空或其中一个链表为空
	if (*first == nullptr)
		if (*second == nullptr)
			return nullptr;
		else
			return *second;
	if (*second == nullptr)
		return *first;
	// 两个链表都不为空
	List merged;
	List p1 = *first;
	List p2 = *second;
	List mergedTail;
	// 先处理第一个合并后的节点
	if (p1->value < p2->value) {
		merged = p1;
		mergedTail = p1;
		p1 = p1->next;
	} else {
		merged = p2;
		mergedTail = p2;
		p2 = p2->next;
	}
	// 处理接下来的节点
	while (p1 != nullptr && p2 != nullptr) {
		if (p1->value < p2->value) {
			mergedTail->next = p1;
			mergedTail = p1;
			p1 = p1->next;
		} else {
			mergedTail->next = p2;
			mergedTail = p2;
			p2 = p2->next;
		}
	}
	// 处理最后剩下的一个链表的节点
	if (p1 == nullptr)
		mergedTail->next = p2;
	else
		mergedTail->next = p1;

	return merged;
}

#else
// 递归思路

List MergeList(List *first, List *second) {
	// 处理递归的基准情形，两个链表其中一个或者都是空链表
	if (*first == nullptr)
		return *second;
	else if (*second == nullptr)
		return *first;
	// 处理两个链表都不为空的递归情况
	// 找到较小节点，让它成为合并有序链表的尾部节点
	List MergeSortedList = nullptr;
	if ((*first)->value < (*second)->value) {
		MergeSortedList = *first;
		MergeSortedList->next = MergedList(&(*first)->next, second);
	} else {
		MergeSortedList = *second;
		MergeSortedList->next = MergedList(first, &(*second)->next);
	}
}

#endif

int main(int argc, char **argv) {
	List list1, list2;
	cout << "list 1 :" << endl;
	CreateList(&list1);
	cin.clear();
	cout << "list 2 :" << endl;
	CreateList(&list2);
	cout << "Two List:" << endl;
	PrintList(&list1);
	PrintList(&list2);
	List merged = MergeList(&list1, &list2);
	cout << "Merged Sorted List:" << endl;
	PrintList(&merged);
	return 0;
}










