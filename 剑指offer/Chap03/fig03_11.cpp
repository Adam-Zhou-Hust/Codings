/**
 * 数值的整数次方--实现 double Power(double base, int exponent) 
 * 不使用库函数，不需要考虑大数问题
 */

// 很显然，这种类似数学题目的算法实现，由于 base 和 exponent 的输入的多样性，导致需要讨论各种情况
// exponent > 0 这种情况下，对于 base 不管正负，直接求解，累乘即可，如果 base 为0,还可以直接返回
// exponent = 0 这种情况下，按照指数的定义，全部为1, 0 的 0 次幂 是无法定义的，因此也必须告知用户
// exponent < 0 这种情况下，实际上对第一种情况的倒数，同时，由于分母不能为0, 因此 base 为0
//              指数为负的情况要进行处理，通知用户
// 根据上面的情况，把对于exponent为正的处理抽离出来，我们很容易写出下列的代码

#include <iostream>
#include <cassert>
#include <stdexcept>
using namespace std;

double absPower(double base, int exponent) {
	assert(exponent >= 0);
	double result = 1;
	if (exponent == 0) {
		if (base != 0)
			return 1;
		else
			throw std::runtime_error("mathmatics undefined");
	}
	if (base == 0)
		return 0;
	while (exponent--) 
		result *= base;
	return result;
}

double Power(double base, int exponent) {
	double result = 1;
	if (exponent >= 0) {
		return absPower(base, exponent);
	} else if (base != 0) {
		return result/absPower(base, -exponent);
	} else {
		throw std::runtime_error("wrong input");
	}
}

int main(int argc, char *argv[]) {
	int exponent;
	double base;
	cout << "Please input base and exponent" << endl;
	while (cin >> base >> exponent) {
		cout << base << "^" << exponent << "=" << Power(base, exponent);
		cout << endl;
	}
	return 0;
}

// 测试用例

// 0 0
// 0 2
// 0 -2

// 2 2
// 2 0
// 2 -2

// -2 0
// -2 2
// -2 -2 