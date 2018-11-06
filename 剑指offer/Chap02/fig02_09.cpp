// fig02_09.cpp
// 斐波那契数列，求斐波那契数列的任意一项
// 这道题在于对递归和迭代的理解，两者的优缺点的比较
// 递归--结构简洁，思路清晰，但是函数调用开销不可避免，同时深度递归可能导致栈溢出
// 迭代--思维量更大，但是不存在递归开销，时间空间的效率都要更高
// 斐波那契数列的递归解法--递归的子问题重复求解现象太严重，效率过低
// 因此利用迭代去实现更为高效

#include <iostream>

using namespace std;

// 迭代 实践复杂度 O(logn)
long long Fibonacci(unsigned int n) {
	if (n == 0)
		return 0;
	if (n == 1)
		return 1;
	int first = 0, second = 1;
	int result = first + second;
	int i = 2;
	while (i++ < n) {
		first = second;
		second = result;
		result = first + second;
	}
	return result;
}


int main(void) {
	int n;
	cout << "请输入要求值的斐波那契数列的项数：" << endl;
	while (cin >> n) {
		cout << "第 " << n << "项" << "的值为：" << Fibonacci(n) << endl;
		cout << "请输入要求值的斐波那契数列的项数：" << endl;
	}
	return 0;
}