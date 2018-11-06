// fig04_24.cpp

// 二叉搜索树的后序遍历序列
// 输入某个序列，判断这个序列能否是一颗二叉搜索树的后续遍历的结果

// 这种和树相关的问题，很显然用递归去写是比较方便的
// 那么就考虑递归情形和基准情形

#include <iostream>
#include <string>
#include <stdexcept>


bool isValidPostOrderOfBST(int *PostOrder, int length) {
	if (PostOrder == nullptr || length <= 0)
		return false;
	int root = PostOrder[length - 1];
	// 判断序列的合法性
	int i = 0;
	for (; i < length - 1; i++)
		if (PostOrder[i] > root)
			break;
	int j = i;
	for (; j < length - 1; j++)
		if (PostOrder[j] < root)
			return false;
	// 递归判断左右子树是否是合法的二叉搜索树的后续遍历序列
	// 考虑到左子树和右子树并不是一定存在的，因此先判断是否存在相应的左右子树的序列
	bool left = true;
	bool right = true;
	if (i > 0)
		left = isValidPostOrderOfBST(PostOrder, i);
	if (j < length - 1)
		right = isValidPostOrderOfBST(PostOrder + i, length - i - 1);
	return left && right;
}