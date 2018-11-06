//fig04_10.cpp

// 二叉树的镜像问题，输入一个二叉树，输出他的镜像树
// 首先理解清楚镜像这个概念，画个图也就大概清楚
// 再考察原二叉树和镜像二叉树之间的差别
// 得出结论：原二叉树的自顶向下的每个非叶子节点，其左右孩子指针交换一下
// 就形成了要求得到的镜像树

// 思路很清晰，利用递归，对于每个非叶子节点，交换其左右孩子节点的指针，最后返回这个树
// 既然是递归，要明确递归情况和基准情况
// 首先，基准情况，当一个节点是空，则直接返回空
// 当一个节点非空，则先递归完成左子树的交换，再递归完成右子树的交换，最后完成这两个
// 孩子节点的交换，返回树的根节点
// 算法实现也比较简洁

#include <iostream>
#include <string>
#include <stdexcept>

struct BinaryTreeNode {
	int value;
	BinaryTreeNode *left;
	BinaryTreeNode *right;
};

// 自顶向下，采用尾递归的形式
// 如果采用首递归，则是自底向上的递归做法
void MirrorRecursively(BinaryTreeNode *root) {
	if (root == nullptr)
		return;
	if (root->left == nullptr && root->right == nullptr)
		return;
	// 交换左右孩子的指针
	BinaryTreeNode *tmp = root->left;
	root->left = root->right;
	root->right = tmp;
	// 自顶向下递归完成左子树和右子树的镜像转换
	if (root->left)
		MirrorRecursively(root->left);
	if (root->right)
		MirrorRecursively(root->right);
}
