#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

// 字符串转换为整数 strToInt
// 主要考虑几个边界情况和特殊字符情况
// 空指针  空字符串  正负号   溢出 
// 非数字的字符处理  错误处理（如何通知客户端代码，如果输入有误，不能转换，可以使用全局变量）

// 小trick：如果有判断溢出的需求，那么代码中一般选择，比目标值大一个级别的类型
// 比如判断int溢出，我们使用long long 类型（保证代码中的类型存储时占据的位数比整型多）

// 指示状态的enum

long long transform(const char *str, int sign);

enum State {
	valide = 1,
	invalid = 0
};
// 全局变量用于反应是否转换成功
State flag = valide;

int strToInt(const char *str) {
	// 考虑指针为空，字符串为空的情况
	// 防止溢出的情况，因此选择一个long long 类型保存 num
	flag = invalid;

	long long num = 0;
	if (str && *str != '\0') {
		// 考虑可能出现正负号，区别数据的符号
		int sign = 1;

		if (*str == '-') {
			str++;
			sign = -1;
		} else if (*str == '+') {
			str++;
		}
		// 判断除了符号，是否还剩余字符，有则进行转换，没有则直接返回
		if (*str != '\0')
			num = transform(str, sign);
	}
	return (int)num;
}

long long transform(const char *str, int sign) {
	long long num = 0;
	while (*str != '\0') {
		// 判断是否是数字，不是数字则不能转换
		if (*str >= '0' && *str <= '9') {
			num = num * 10 + sign * (*str - '0');
			// 判断是否溢出
			// 正数 > 0x7fffffff 负数 < 0x80000000
			if ((sign > 0 && num > 0x7fffffff) || (sign < 0 && num < (signed int)(0x80000000))) {
				num = 0;
				break;
			}
			str++;
		} else {
			// 不是数字，则不能转换
			num = 0;
			break;
		}
	}
	// 判断是否是正确转换之后才跳出循环
	if (*str == '\0')
		flag = valide;
	return num;
}

int main(void) {
	int num;
	string s;
	while (cin >> s) {
		num = strToInt(s.c_str());
		if (flag) {
			cout << "Transfromed Success: " << num << endl;
		} else {
			cout << "Transfromed Failed." << endl;
		}
	}
	return 0;
}