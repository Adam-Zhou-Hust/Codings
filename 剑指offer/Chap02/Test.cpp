#include <vector>
#include <string>
#include <iostream>
#include <stdexcept>
// 这道题，很诡异，之前也是用指针和size 去写，一直段错误，找不到原因
// 再次写，就发现又可以了
// 总之，思路肯定是对的，就是指针这东西，真是不好惹啊，慎用，慎用
// 要使用指针，一定要搞清楚指针是否 越界，指针作用域，指针生存周期，甚至指针的指向的位置（堆还是栈）
// 指向栈很危险，如果栈退出，栈变量被销毁，指针变成野指针

struct BinaryTreeNode {
	BinaryTreeNode(int t) : data(t), left(0), right(0) { } 
	int	data;
	BinaryTreeNode *left;
	BinaryTreeNode *right;
};

inline
int *find(int *inOrder, int length, int value) {
	auto p = inOrder;
	while (p != inOrder + length && *p != value)
		p++;
	return p;
}


BinaryTreeNode *createBinaryTree(int *preOrder, int *inOrder, int length) {
	if (length == 0)
		return nullptr;
	else {
		// 创建根节点
		BinaryTreeNode *root = new BinaryTreeNode(*preOrder);
		// 找到根节点在中序中的位置
		/*
		auto p = inOrder;
		while (p != inOrder + length && *p != root->data)
			p++;
		*/	
		auto p = find(inOrder, length, root->data);
		if (p == inOrder + length)
			throw std::out_of_range("Invalid Input Data");
		// 递归建立左右子树
		auto leftSize = p - inOrder;
		auto rightSize = length - (p - inOrder) - 1;
		//if (leftSize > 0)
			root->left = createBinaryTree(preOrder+1, inOrder, leftSize);
		//if (rightSize > 0)
			root->right = createBinaryTree(preOrder+leftSize+1, p + 1, rightSize);
		return root;
	}
}


template <typename T>
void preOrder(const T *tree) {
	if (tree) {
		std::cout << tree->data << '\t';
		preOrder(tree->left);
		preOrder(tree->right);
	}
}

template <typename T>
void inOrder(const T *tree) {
	if (tree) {
		inOrder(tree->left);
		std::cout << tree->data << '\t';
		inOrder(tree->right);
	}
} 

int main(void) {
	int pre[] = {1,2,4,7,3,5,6,8};
	int mid[] = {4,7,2,1,5,3,8,6};
	int size = sizeof(pre)/sizeof(pre[0]);
	BinaryTreeNode *root = createBinaryTree(pre, mid, size);
	preOrder(root);
	std::cout << std::endl;
	inOrder(root);
	return 0;
}