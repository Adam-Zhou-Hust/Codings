#include <iostream>
#include <string>
#include <vector>

void FindPath(BinaryTreeNode *root, int expectedSum);
void FindPath(BinaryTreeNode *root,
			  int expectedSum,
			  std::vector<int> &path,
			  int currentSum);

void FindPath(BinaryTreeNode *root, int expectedSum) {
	if (root == NULL)
		return;
	std::vector<int> path;
	int currentSum = 0;
	FindPath(root, expectedSum, path, currentSum);
}

void FindPath(BinaryTreeNode *root,
			  int expectedSum,
			  std::vector<int> &path,
			  int currentSum) {
	currentSum += root->value;
	path.push_back(root->value);
	// 判断是否是叶子结点，是则判断路径和是否满足要求
	// 是满足expectedSum的叶子则打印整个路径
	bool isLeaf = root->left == nullptr && root->right == nullptr;
	if (currentSum == expectedSum && isLeaf) {
		std::cout << "A path is found:";
		auto it = path.begin();
		for (; it != path.end(); it++)
			std::cout << *it << " ";
		std::cout << std::endl;
	}
	// 若不是叶子节点，递归在左右子树中寻找路径
	if (root->left != nullptr)
		FindPath(root->left, expectedSum, path, currentSum);
	if (root->right != nullptr)
		FindPath(root->right, expectedSum, path, currentSum);
	// 返回父节点之前必须把当前节点出栈
	path.pop_back();

}