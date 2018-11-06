// 旋转数组的最小数字
// 输入一个递增排序数组的一次旋转 {3,4,5,1,2}
// 输出数组中的最小元素   
// 关键是 这道题目要先分析好各种测试用例的情况，如何处理
// 把各种可能的输入情况分析好

// 基本思路    数组旋转之后，分为左侧部分和右侧部分，最小元素显然是右侧的第一个元素
// 数组旋转后的特点，第一个元素必然不会小于右侧所有的元素
// 1.没有旋转的一种情况----第一个元素小于最后一个元素，那么直接返回
// 2.采取逐步逼近，一个指针指向左侧元素，一个指向右侧，每次利用二分查找，让两个指针逐步逼近
//   直到之间的距离为1
// 3.每次二分的目的，判断当前指针指向的元素在左侧还是右侧---这是核心思路
// 4.做上述判断的标准有哪些？会出现哪些特殊情况，具体分析，如果无法判断其在哪侧，又该如何处理？
// 5.当无法判断其在哪一侧时，采取顺序查找办法，找出最小元素，其余情况则直接二分，直到指针距离为1
// 6.最后返回最小值



#include <iostream>
#include <string>
#include <stdexcept>

int MinInOrder(int *array, int start, int end) {
	int min = array[start];
	for (auto i = start + 1; i <= end; i++)
		if (array[i] < min)
			min = array[i];
	return min;
}

int Min(int *array, int length) {
	if (array == nullptr || length <= 0)
		throw std::runtime_error("empty array");

	int start = 0;
	int end = length - 1;
	int mid;

	// 仔细考虑各种情况
	// 1.没有经过旋转的数组，直接返回最小元素
	if (array[start] < array[end])
		return array[start];
	while ((end - start) != 1) {
		mid = (start + end) / 2;
		// 无法判断在左侧还是右侧的情况，三个指针指向的数都相等
		if (array[start] == array[end] && array[mid] == array[start])
			return MinInOrder(array, start, end);
		// 三者必然不全相等，判断在左侧还是右侧
		if (array[start] <= array[mid])
			start = mid;
		else
			end = mid;
	}
	return array[end];
}

// 测试
void TestMinInOrder() {
	int array[] = {2, 0, -3, 9, 13, -2, 0, 0, 1, 5, -22, 99, 11, 36};
	int start = 0;
	int end = sizeof(array)/sizeof(array[0]);
	std::cout << MinInOrder(array, start, end) << std::endl;
}

void TestMin() {
	int arr1[] = {1,2,3,4,5,6,7};
	int arr2[] = {5,6,7,8,9,0,1,2};
	int arr3[] = {3,3,3,4,3,3,3,3,3};
	int arr4[] = {4,4,4,4,4,4,4,4,4,4,4};
	int arr5[] = {5,5,5,5,6,6,6,6,6,6,6,3};
	int arr6[] = {1};
	int *arr7 = nullptr;

	std::cout << Min(arr1, sizeof(arr1)/sizeof(arr1[0])) << std::endl;
	std::cout << Min(arr2, sizeof(arr2)/sizeof(arr2[0])) << std::endl;
	std::cout << Min(arr3, sizeof(arr3)/sizeof(arr3[0])) << std::endl;
	std::cout << Min(arr4, sizeof(arr4)/sizeof(arr4[0])) << std::endl;
	std::cout << Min(arr5, sizeof(arr5)/sizeof(arr5[0])) << std::endl;
	std::cout << Min(arr6, sizeof(arr6)/sizeof(arr6[0])) << std::endl;
	std::cout << Min(arr7, sizeof(arr7)/sizeof(arr7[0])) << std::endl;
}

// Main
int main(void) {
	// TestMinInOrder();
	TestMin();
	return 0;
}