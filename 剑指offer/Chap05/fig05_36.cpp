// 数组中的逆序对的计算
// 暴力破解算法，时间复杂度为 O(n^2)，显然不能满足要求
// 考虑算法的优化，首先理解好逆序的概念
// 结合排序思想，排序就是消除所有的逆序，能否在排序过程中，计算逆序的对数
// 基于比较的排序算法，可以达到 O(nlogn)的时间复杂度
// 考虑归并排序，在Merge过程中，计算逆序
// 此外，归并排序并不是原址排序

// 代码实现如下

#include <iostream>
#include <string>
using namespace std;


int merge(int *arr, int p, int q, int r) {
	// merge过程中，使用辅助数组，初始化两个辅助数组
	int leftSize = q - p + 1;
	int rightSize = r - q;
	int *left = new int[leftSize];
	int *right = new int[rightSize];
	for (int i = 0; i < leftSize; ++i)
		left[i] = arr[p + i];
	for (int j = 0; j < rightSize; ++j)
		right[j] = arr[q + 1 + j];

	// 开始merge过程，同时统计逆序对的数量
	// 关键理解一点，逆序数怎么计算，归并中，逆序的意义在哪
	// 首先，left[i] <= right[j] 时，两个数，并不产生逆序，
	// 如果 left[i] > right[j]，显然这一对数字产生了逆序
	// 然而，不止于此，并不仅仅这一对
	// 考虑每个left right都是已经排序好的，所以，当 left[i] > right[j]
	// left 数组后面的每个数都会 > right[j]，因此都会产生逆序对
	// 一共 leftSize-i 个，当我们把相应的数放好，也就消除了这些所有的逆序
	// 然后进行下一轮次的比较

	int count = 0;
	int i = 0, j = 0, k = p;
	for (; k <= r; ++k) {
		if (i < leftSize && j <rightSize) {
			if (left[i] <= right[j]) {
				arr[k] = left[i];
				++i;
			} else {
				count += leftSize - i;
				arr[k] = right[j];
				++j;
			}
		} else
			break;
	}
	if (i == leftSize) {     // 说明左边先遍历完，剩下右边的数	
		while (k <= r) 
			arr[k++] = right[j++];
	} else {
		while (k <= r)
			arr[k++] = left[i++];
	}
	delete [] left;
	delete [] right;
	return count;
}


int partition(int *arr, int p, int q, int r) {
	if (arr == nullptr || (r - p) <= 0)
		return 0;
	
	int leftCount = partition(arr, p, (p + q) / 2, q);
	int rightCount = partition(arr, q + 1, (q + 1 + r) / 2, r);

	return leftCount + rightCount + merge(arr, p, q, r);
}

int inverseCount(const int *arr, int length) {
	int *helpArr = new int[length];
	for (int i = 0; i < length; ++i)
		helpArr[i] = arr[i];
	int count = partition(helpArr, 0, (length - 1) / 2 , length - 1);
	for (int i = 0; i < length; i++)
		std::cout << helpArr[i] << " ";
	std::cout << std::endl;
	delete [] helpArr;
	return count;
}

int main(int argc, char **argv) {
	int arr[] = {1, 3, 5, 7, 9, 2, 4, 6, 8, 10};
	int inverseNum = inverseCount(arr, sizeof(arr) / sizeof(arr[0]));
	std::cout << "inverse number is " << inverseNum << std::endl;
	return 0;
}
