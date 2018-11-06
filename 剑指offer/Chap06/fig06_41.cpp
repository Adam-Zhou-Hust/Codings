// 和为s的两个数字  VS 和为s的连续正数序列
// 输入一个递增排序的数组和一个数字s，在数组中查找两个数，使得他们的和正好为s
// 如果存在多对数字的和为s，输出任意一对即可
// 不难想到，暴力破解方法，针对每一个数对，考虑计算其和为多少
// 那么时间复杂度为O(n^2)
// 很显然，没有用到数组是递增排序这一非常重要的特点
// 考虑最终的结果，数组中两个数的和为s
// 必然存在p1 p2指针分别指向这两个数字，那么我们可以这么考虑
// 让一个指针指向第一个元素，另一个指向最后一个元素
// 一个向前进，一个向后退，那么针对一定的比较规则
// 最终这两个指针一定是能够找到我们需要的两个数字的
// 比较的规则，显然是根据指针指向的两个数和和s的大小关系
// 如果和大于s，那么指向大数的指针往后退，如果小于，指向小数的指针往前进
// 如果相同，则直接退出（因为题目仅仅要求找到一对即可）
// 如果要找到全部，则设置循环终止条件，根据两个指针的大小关系设置终止条件即可
// 实现代码如下

#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;

bool findNumbersWithSum(int data[], int length, int sum, int *n1, int *n2) {
	int *pHead = data;
	int *pTail = data + length - 1;
	while (pHead < pTail) {
		int currSum = *pHead + *pTail;
		if (currSum == sum) {
			*n1 = *pHead;
			*n2 = *pTail;
			return true;
		} else if (currSum > sum) {
			pTail--;
		} else {
			pHead++;
		}
	}
	return false;
}

int main(void) {
	int data[] = {1, 2, 4, 7, 11, 15};
	int n1, n2;
	int sum = 18;
	bool result = findNumbersWithSum(data, sizeof(data) / sizeof(data[0]), sum, &n1, &n2);
	if (result)
		std::cout << "两个数分别为 " << n1 << " " << n2 << std::endl;
	else
		std::cout << "不存在这样的两个数使得和为 " << sum << std::endl;
	return 0;
}
