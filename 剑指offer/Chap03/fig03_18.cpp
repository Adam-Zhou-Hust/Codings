/**
 * 树的子结构问题
 * 输入两颗二叉树A和B，判断B是否是A的子结构
 */

// 首先审题，判断是否是子结构而非子树，子结构的范围更加广,同时，对于节点相同
// 比较的应该是值而非指向同一个节点(因为不是一定是子树)，可能A仅是B某部分的拷贝

// 其次，应当是一开始就有思路的
// 首先得找到B的根节点的在A中的位置，采用遍历就可以找到
// 第二部，就是比较B和以上一步A中找到的节点为根节点的子树开始的结构
// 看是否把B包含在其中

// 当然，注意输入的树的情况，空树如何处理？
// 因此，先对输入加以判断


// 考虑在A树的遍历过程中，找到值和B的根一样的节点
// 然后以此为基础，判断两个部分是否具有相同的结构
// 直到A树遍历完毕

// 判断两个部分是否具有相同的结构作为第二步，要仔细考虑一下，首先，如何比较或者判断
// 其次是终止条件(或者边界条件)
// 画草图加以明确解法
// 遍历判断每个节点是否相同
// 但是基准情况和普通的树的遍历不同
// 因为仅仅是判断结构是否相同，所以递归遍历的基准情况要修改
// 当两个指针其中一个没有儿子了，就可以作为基准情况，直接判断了

// 根据以上分析，容易得出代码如下



#include <iostream>
using namespace std;

struct BinaryTreeNode {
	int value;
	BinaryTreeNode *left;
	BinaryTreeNode *right;
};

typdefe BinaryTreeNode *BinaryTree;

bool judgeSameStructure(BinaryTree A, BinaryTree B) {
	// 考虑递归到某一步的情况
	// 1. 两个指针都是空的
	// 2. 其中一个为空，另一个非空
	// 3. 两个都是非空
	// 对于第一种 第二种 情况，都属于到达了其中一个叶节点的子节点(只不过子节点为空，不存在)
	// 先判断是否是基准情况，是则返回结果，否则递归调用
	// 基准情况就是两个节点中，其中一个或者两个都为叶子节点
	// 但是，如果B为叶子了，A反而不是叶子，那么可以肯定不是子结构

	// 基准情况
	if (A == nullptr)
		return true;
	if (B == nullptr)
		return false;
	// 处理递归情况
	if (A->value != B->value)
		return false;
	return judgeSameStructure(A->left, B->left) && judgeSameStructure(A->right, B->right);

}

// 利用递归，先根遍历查找B的根节点在A的位置，同时判断子结构是存在

bool HasSubStructure(BinaryTree A, BinaryTree B) {
	int result = false;
	if (A && B) {
		if (A->value == B->value)
			result = judgeSameStructure(A, B);
		if (!result)
			result = judgeSameStructure(A->left, B->left);
		if (!result)
			result = judgeSameStructure(A->right, B->right);
	}
	return result;
}

// 代码虽然很短，思维量却并不小，相关过程，判断方法，终止的条件，特殊输入都要考虑到
// 由于都采用了递归，因此显得代码非常简洁，思路清晰


