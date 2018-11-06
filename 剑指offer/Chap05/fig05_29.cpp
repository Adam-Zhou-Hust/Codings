#include <cmath>
#include <cassert>
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
using namespace std;

// 找出数组中出现次数超过一半的数字
// 我们先保证一定存在这样的数字

// 思路一
// 考虑如果这个数组是有序的，那么出现次数超过一般的数字，一定出现在n/2处
// 那么，如果把数组排序，直接输出即可，但是时间复杂度为O(nlogn)
// 考虑时间复杂度低一些的算法思路，想到快排的partition过程
// 随机选择一个数，利用partition找到最终这个数字在有序数组当中的位置
// 如果位置刚好为n/2，则就是我们要找到的数字
// 如果位置小于n/2，那么说明在右侧继续寻找
// 如果位置小于n/2，则在左侧继续寻找

// 首先给出partition的过程，枢纽元素则选择随机的元素
// 和快排中的差不多
int partition(int arr[], int left, int right) {
	assert(left <= right);
	if (left == right)
		return left;

	int low = left;
	int high = right;

	//选择枢纽元素
	int idx = (rand() % (right - left + 1) ) + left;
	int pivot = arr[idx];
	// 让枢纽元素和第一个元素交换一下，方便后边代码的编写和理解
	// 交换之后，相当于选择第一个元素为枢纽元进行比较
	arr[idx] = arr[left];
	// 双指针方法，从右侧找到第一个小于枢纽的元素，左侧找到第一个大于枢纽的元素
	while (low < high) {
		while (low < high && arr[high] >= pivot) high--;
		if (low < high) 
			arr[low++] = arr[high];
		while(low < high && arr[low] <= pivot) low++;
		if (low < high)
			arr[high--] = arr[low];
	}

	arr[low] = pivot;
	return low;
}

// 完成partiontion之后，得出本问题的解决方法(迭代思路)
// 类似于二分的查找过程
int findMoreThanHalf(int arr[], int len) {
	// 先假定存在这样的数，出现次数超过一半
	int mid = len / 2;
	int left = 0, right = len - 1;
	int idx = partition(arr, left, right);

	while (idx != mid) {
		if (idx > mid) {
			right = right - 1;
			idx = partition(arr, left, right);
		} else {
			left = idx + 1;
			idx = partition(arr, left, right);
		}
	}
	// 现在，如果我们要保证程序的健壮性，对于不存在这样的数的情况，设置一下某个全局变量的标志，表明不存在
	// 那么只需针对这个arr[idx]，遍历一遍数组，统计他的次数，看是否是超过一半即可，这里就不写了
	return arr[idx];
}

// 思路二
// 根据数组的特点，超过一半的次数，那么这个数出现的次数，比其他数字出现次数之和还要多
// 那么，从第一个数字开始计数，如果下一个数和这个一样，则计数+1，否则计数-1
// 每次还需要判断计数是否为0，如果为0，则当前数字记作前一个，计数为1，然后继续迭代即可
// 最后一个计为1或者更多的数字，就一定是我们需要找的数字
// 代码实现则比较简单


// 测试partition过程的快排程序
void quickSort(int arr[], int left, int right) {
	assert(left <= right);
	if (left == right)
		return;
	int mid = partition(arr, left, right);
	if (mid > left)
		quickSort(arr, left, mid - 1);
	if (mid < right)
		quickSort(arr, mid + 1, right);
}

int main(void) {
	// 经过测试，partition是没有问题的

	int arr[] = {1,3,5,6,2,4,6,6,6,1,0,6,5,9,6,6,6,6,6,6,6,6,6};
	int len = sizeof(arr) / sizeof(arr[0]);
	for_each(arr, arr + len, [] (int val) { cout << val << ' '; });
	cout << endl;
	int result = findMoreThanHalf(arr, len);
	cout << result << endl;
//	cout << endl;
//	quickSort(arr, 0, len - 1);
//	for_each(arr, arr + len, [] (int val) { cout << val << ' '; });
//	cout << endl;
	return 0;
}