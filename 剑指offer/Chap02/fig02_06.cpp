/** 
 * 根据给定的前序遍历 中序遍历的结果，重建二叉树的结构
 * 并打印出来
 * 前序 1 2 4 7 3 5 6 8
 * 中序 4 7 2 1 5 3 8 6
 */

#include <vector>
#include <string>
#include <iostream>
#include <stdexcept>

struct BinaryTreeNode {
	BinaryTreeNode(int t) : data(t), left(0), right(0) { } 
	int	data;
	BinaryTreeNode *left;
	BinaryTreeNode *right;
};

// 最后写一遍

BinaryTreeNode *
createBinaryTree(int *preStart, int *preEnd,
				 int *inStart, int *inEnd) {
		// 创建根
		BinaryTreeNode *root = new BinaryTreeNode(*preStart);
		if (preStart == preEnd) {
			if (inStart == inEnd) 
				return root;
			else 
				throw std::out_of_range("Invalid Input Data");
		} else {
		// 在中序中找到根节点的位置
			auto p = inStart;
			while (p <= inEnd && *p!= root->data)
				p++;
			if (p == inEnd && *p != root->data)
				throw std::out_of_range("Invalid Input Data");
			// 递归构造左右子树
			int leftSize = p - inStart;
			if (leftSize > 0)
				root->left = createBinaryTree(preStart + 1, preStart + leftSize,
											  inStart, p -1);
			int rightSize = preEnd - preStart -(leftSize);
			if (rightSize > 0)
				root->right = createBinaryTree(preStart + leftSize + 1, preEnd,
											   p + 1, inEnd);
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

int main(int argc, char *argv[]) {
	int pre[] = {1,2,4,7,3,5,6,8};
	int mid[] = {4,7,2,1,5,3,8,6};
	int size = sizeof(pre)/sizeof(pre[0]);
	BinaryTreeNode *root = createBinaryTree(pre, pre+size-1, mid, mid+size-1);
	preOrder(root);
	std::cout << std::endl;
	inOrder(root);
	return 0;
}