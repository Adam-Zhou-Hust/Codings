/**
 * 一个整型数组中，除了两个数字之外，其他的数字都出现了两次
 * 请找出这两个只出现了一次的数，并保证算法的时间复杂度为O(n)，空间复杂度为O(1)
 */

// 思路
// 这种题目如果之前没有碰到过，其实蛮难一下想到
// 除了两个数字外，其余成对出现，说明：这两个数不相同，并且这两个数和其他数也不相同，否则题干并不成立

// 因此，假设，全部的数字，成对出现，那么所有的数字通过按位异或运算之后，结果是0
// 既然存在另外两个不同的数，那么所有数进行异或的结果就等价于这两个数单独异或

#include <iostream>
#include <string>
using namespace std;

void findNumAppearOnce(int data[], int length, int *n1, int *n2) {
	if (data == nullptr || length <= 0)
		return;
	int xorOfAll = 0;
	for (int i = 0; i < length; i++)
		xorOfAll ^= data[i];
	int firstDiffBit = 1;
	int count = 0;
	while (xorOfAll % 2 != 1) {
		xorOfAll >>= 1;
		count++;
	}
	firstDiffBit <<= count;
//	cout << "count firstDiffBit" << count << " " << firstDiffBit << endl; 
// 
//	for (int i = 0; i < length; i++)
//		std::cout << left[i] << " ";
//	std::cout << std::endl;
// 
	int *left = new int[length]();
	int *right = new int[length]();
	int i = 0, j = 0, k = 0;

	for (; k < length; k++) {
		if ((data[k] & firstDiffBit) == 0)
			left[i++] = data[k];
		else
			right[j++] = data[k];
	}
	*n1 = *n2 = 0;
	for (int k = 0; k < i; k++)
		(*n1) ^= left[k];
	for (int k = 0; k < j; k++)
		(*n2) ^= right[k];
	delete left;
	delete right;
	return;
}

int main(int argc, char **argv) {
	int arr[] = {1,2,3,4,5,5,4,3,2,1,7,9};
	int n1, n2;
	findNumAppearOnce(arr, sizeof(arr)/sizeof(arr[0]), &n1, &n2);
	std::cout << "在数组中不同的两个数是" << n1 << " 和 " << n2 << std::endl;
	return 0;
}