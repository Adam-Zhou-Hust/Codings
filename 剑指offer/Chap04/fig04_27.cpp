// 二叉搜索树和双向链表
// 输入一颗二叉搜索树，通过只调整树中结点指针的指向，得到一个转换之后的排序双向链表
// 要得到的链表是有序链表，显然应当中序遍历原来的二叉搜索树
// 并且在遍历的过程中，调整节点的left和right指针
// 考虑当遍历到某个非叶节点之时，考虑其左子树上的所有节点，应当已经完成了链接，构成
// 了一个部分的有序双向链表，接下来则需要把这个节点链接到双向链表的尾部
// 因此，需要直到当前链表的尾节点指针，然后更改相应的指针
// 包括让原尾节点的right指向这个非叶子结点，让非叶子节点链接到链表尾部成为新的尾结点
// 同时，更改这个非叶子节点的left指针(双向链表)
// 最后，考虑对这个非叶子节点的右子树，仍然按照上述操作递归即可


struct BinaryTreeNode {
	int value;
	BinaryTreeNode *left;
	BinaryTreeNode *right;
};

BinaryTreeNode *Convert(BinaryTreeNode *root) {
	BinaryTreeNode *lastOfLinkedList = nullptr;
	ConvertNode(root, &lastOfLinkedList);
	BinaryTreeNode *headOfLinkedList = lastOfLinkedList;
	while (headOfLinkedList != nullptr && headOfLinkedList->left != nullptr)
		headOfLinkedList = headOfLinkedList->left;
	return headOfLinkedList;
}

void ConvertNode(BinaryTreeNode *root, BinaryTreeNode **lastOfLinkedList) {
	if (root == nullptr)
		return;

	if (root->left != nullptr)
		ConvertNode(root->left, lastOfLinkedList);

	root->left = *lastOfLinkedList;
	if (*lastOfLinkedList != nullptr)
		(*lastOfLinkedList)->right = root;
	*lastOfLinkedList = root;

	if (root->right != nullptr)
		ConvertNode(root->right, lastOfLinkedList);
}