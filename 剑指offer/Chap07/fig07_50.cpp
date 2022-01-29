#include <iostream>
#include <string>
#include <list>
#include <stack>
#include <queue>
#include <cassert>
using namespace std;

struct TreeNode {
	char value;
	TreeNode *left;
	TreeNode *right;
	TreeNode(char var, TreeNode *l = nullptr, TreeNode *r = nullptr) : 
	    value(var), left(l), right(r) { }
};

TreeNode *createTree() {
	TreeNode *root = new TreeNode('A');

	TreeNode *n1 = new TreeNode('B'), *n2 = new TreeNode('C');
	root->left = n1, root->right = n2;

	TreeNode *n3 = new TreeNode('D'), *n4 = new TreeNode('E');
	n1->left = n3, n1->right = n4;

	TreeNode *n5 = new TreeNode('F'), *n6 = new TreeNode('G');
	n3->left = n5, n3->right = n6;

	TreeNode *n7 = new TreeNode('H'), *n8 = new TreeNode('I');
	n4->left = n7, n4->right = n8;

	TreeNode *n9 = new TreeNode('J');
	n2->right = n9;
    
    return root;
}

// 1.遍历算法
void preOrder(TreeNode *root) {
	if (root) {
		cout << root->value << ' ';
		preOrder(root->left);
		preOrder(root->right);
	}
}

void inOrder(TreeNode *root) {
	if (root) {
		inOrder(root->left);
		cout << root->value << ' ';
		inOrder(root->right);
	}
}
// 层序遍历，并每一层打印完毕后，输出换行
// 思路，每次要统计一下下一层的节点个数，用两个while循环，用队列保存未遍历的节点即可
void levelOrder(TreeNode *root) {
	queue<TreeNode *> que;
	que.push(root);
	int countCurr = 1;    // 用于指示当前层的个数
	int countNext = 0;    // 用于指示下一层的个数 
	while (!que.empty()) {
		while (countCurr--) {
			auto t = que.front();
			que.pop();
			cout << t->value << ' ';
			if (t->left) {
				countNext++;
				que.push(t->left);
			}
			if (t->right) {
				countNext++;
				que.push(t->right);
			}
		}
		cout << endl;
		countCurr = countNext;
		countNext = 0;
	}
}

// 对普通一般的二叉树，找到第一个公共祖先节点

// 先通过遍历，找到到某个节点的路径
// 采取先根遍历的方式
// 对于一个节点，递归的寻找其路径
// 先判断当前节点是否是需要查找的节点，如果是，则直接return true
// 否则，分别在它的左子树中查找，找到则返回true，否则在右子树中寻找，找到则返回
// 如果都找不到，说明以当前节点为根节点的树中，不存在需要查找的节点，则回溯
// 把当前节点出栈，并return false
bool findPath(TreeNode *root, TreeNode *node, stack<TreeNode *> &path) {
	if (root == node)
		return true;
	path.push(root);

	bool findResult = false;
	if (root->left) {
		findResult = findPath(root->left, node, path);
		if (findResult)
			return true;
		else if (root->right) {
			findResult = findPath(root->right, node, path);
			if (findResult)
				return true;
		}
	}
	path.pop();
	return findResult;
}

TreeNode *findCommon(TreeNode *root, TreeNode *node1, TreeNode *node2) {
	stack<TreeNode *> path1;
	stack<TreeNode *> path2;
	findPath(root, node1, path1);
	findPath(root, node2, path2);
	// 查找路径中最后一个个公共节点，按照栈来说，则是出栈中第一个相同的点
	// 其实对于链表也是一样的，求解两个单链表的第一个公共节点
	TreeNode *common = nullptr;
	int size1 = path1.size();
	int size2 = path2.size();
	if (size1 > size2) {
		while (size1 > size2) {
			path1.pop();
			size2++;
		}
	} else if (size1 < size2) {
		while (size1 < size2) {
			path2.pop();
			size1++;
		}
	}
	while (!path1.empty() && !path2.empty()) {
		if (path1.top() != path2.top()) {
			path1.pop();
			path2.pop();
		} else {
			common = path1.top();
			break;
		}
	}
	return common;
}

// 2021.02.14
// 以上写法非常不简洁，今日又刷到，给出上述方法的简化代码版本
// 同时给出另一种递归思路版本
class Solution2 {
public:
    TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q);
private:
    void findPath(TreeNode *root, TreeNode *targetA,TreeNode *targetB,
                            vector<TreeNode *> &currPath,
                            vector<TreeNode *> &pathA,
                            vector<TreeNode *> &pathB);
};

// 基本思路：找到从根结点到两个节点的路径，并将路径上的节点分别保存下来(比如用vector保存)
// 同时遍历路径，找到最后一个路径上的相同节点即为最近公共祖先
TreeNode *Solution2::lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q) {
    vector<TreeNode *> pathA, pathB, currPath;
    findPath(root, p, q, currPath, pathA, pathB);
    int i = 0;
    for (; i < pathA.size() && i < pathB.size(); i++) {
        if (pathA[i] != pathB[i]) break;
    }
    return pathA[i-1];
}

// 递归回溯，找到从根结点到目标节点的路径(先根遍历，如果找到直接返回，相当于剪枝)
void Solution2::findPath(TreeNode *root,
                        TreeNode *targetA,
                        TreeNode *targetB,
                        vector<TreeNode *> &currPath,
                        vector<TreeNode *> &pathA,
                        vector<TreeNode *> &pathB) {
    if (root == nullptr) return;
    currPath.push_back(root);
    if (root == targetA) pathA = currPath;
    if (root == targetB) pathB = currPath;
    findPath(root->left, targetA, targetB, currPath, pathA, pathB);
    findPath(root->right, targetA, targetB, currPath, pathA, pathB);
    currPath.pop_back();
}

// 另一种递归方法
TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q) {
    if (root == nullptr) {
        return nullptr;
    }
    if (root == p || root == q) {
        return root;
    }
    TreeNode *left = lowestCommonAncestor(root->left, p, q);
    TreeNode *right = lowestCommonAncestor(root->right, p, q);
    if (left != nullptr && right != nullptr) {
        // p q 一个在左，一个在右
        return root;
    }
    if (left != nullptr) {
        // p q 都在左子树
        return left;
    }
    if (right != nullptr) {
        // p q 都在右子树
        return right;
    }
    return nullptr;
}

int main(void) {
	TreeNode *root = createTree();
	TreeNode *node1 = root->left->left->left;
	TreeNode *node2 = root->left->right->right;
	cout << node1->value << ' ' << node2->value << endl;

	auto ret = findCommon(root, node1, node2);
	assert(ret);

	cout << ret->value <<endl;
	return 0;
}
