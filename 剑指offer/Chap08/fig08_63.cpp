#include <iostream>
using namespace std;

// 查找二叉搜索树中的第k大的节点
// 思路
// 二叉搜索树，肯定是有序的，同时，查找的也是有序的第k大个数字
// 按照中序遍历，则是从小到大，那么，如果左右子树遍历顺序反一下
// 则变成从大到小了
// 因此，采用微调的中序遍历，思路，便利到第k个节点则返回
// 代码使用递归完成

TreeNode* findMaxK(TreeNode *root, int &count) {

}