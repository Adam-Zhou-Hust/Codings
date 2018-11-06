// fig04_23.cpp

// 从上到下按照层次打印二叉树

// 这道题很明显的按照层序遍历的思路了，是一道基本功的送分题
// 利用队列，从根节点开始，访问根节点，如果有孩子，则孩子节点依次入队
// 根节点出队
// 如果队列不为空，则访问队头节点，队头如果有孩子，则孩子节点依次入队
// 头节点出队
// 按照上述过程迭代，直到队列为空

#include <iostream>
#include <deque>
#include <stdexcept>
using namespace std;

struct BinaryTreeNode {
	int value;
	BinaryTreeNode *left;
	BinaryTreeNode *right;
};

typedef BinaryTreeNode *BinaryTree;

void levelTravel(BinaryTree *T) {
	if (T == nullptr)
		return;
	deque<BinaryTreeNode *> q;
	q.push_back(T);
	while (q.size()) {
		BinaryTreeNode *tmp = q.front();
		std::cout << tmp->value << ' ';
		if (tmp->left)
			q.push_back(tmp->left);
		if (tmp->right)
			q.push_back(tmp->right);
		q.pop_front();
	}
}
