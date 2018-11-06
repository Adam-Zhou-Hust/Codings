/**
 * 输入一个整数，输出这个数的二进制表示中，1的个数
 */

// 首先，肯定涉及位运算，通过移位操作，把相应的位和1做按位与，从而判断这个位是否是1
// 关键在于，迭代的条件，移多少位能够把这个数判断完
// 迭代终止的条件
// 同时，右移整数，左边补充的是符号位，因此，如果整数是负数，则补1, 这种情况下如何设计迭代的终止条件

// 1.如果按照移位后的整数是否为0,则对于一个负数，因为右移补符号位，因此补1, 导致死循环
// 2.考虑不右移n，而是左移用来比较的flag，达到相同的效果，左移动，flag后面补充0，循环终止条件就是直到flag移动一个循环, 最后为0

#include <iostream>
#include <string>
using namespace std;

int NumOfOne(int n) {
	int count = 0;
	unsigned int flag = 1;
	while (flag != 0) {
		if ((n & flag) != 0)
			count++;
		flag <<= 1;
	}
	return count;
}

int main(void) {
	int a = 0x01ff;    
	int b = 0x7fffffff;   // 边界值，最大正数
	int c = 0x80000000;   // 边界值，最小负数
	int d = 0xffffffff;   // 边界值，最大负数

	cout << NumOfOne(a) << " 1 " << "in " << a << endl;
	cout << NumOfOne(b) << " 1 " << "in " << b << endl;
	cout << NumOfOne(c) << " 1 " << "in " << c << endl;
	cout << NumOfOne(d) << " 1 " << "in " << d << endl;

	return 0;
}
