/**
 * 输入数字n，按照顺序打印出从1到最大的n位十进制数
 * 比如，输入3
 * 打印 1 2 3 ... 一直到最大的3位数 999
 */

// 很显然，这道题目的考察点在于大数问题，当long long 型都无法满足输入的位数需求时，如何处理这些大数的表示
// 比较通常的做法便是采用字符数组模拟整数的表示，模拟整数的加法，显然要考虑到进位的问题
// 同时要考虑，何时加到最大值
// 此外，还可以考虑全排列的思路，当最末尾为0,其他位有几种排列，当末尾为1,有几种排列...
// 一直到当末尾为9时，其他位几种排列，完成全部排列后，并把这些排列打印出来，也能打印出结构，这里
// 对于全排列问题，显然要用到递归的方法
// 对于上述两种思路，分别有如下代码

// 采用字符串模拟整数，模拟整数加法

#include <cstring>
#include <iostream>


bool addOfBigInt(char *number);
void printBigInt(char *number);

void printOneToMax(int n) {
	if (n <= 0) 
		return;
	// 分配空间并且初始化
	char *number = new char[n+1];
	std::memset(number, '0', n);
	number[n] = '\0';

	while (addOfBigInt(number)) {
		printBigInt(number);
	}
	delete [] number;
}

bool addOfBigInt(char *number) {
	std::size_t length = std::strlen(number);

	char *begin = number;
	char *end = begin + length - 1;
	// 这里有一点要特注意，当使用指针时候，一定一定一定要避免访问越界的指针
	// 这里如果把 end >= begin 这个条件放到后面，就会产生问题
	// 由于 ++*end 先执行，试想一下，上一个循环导致 end 指向了 begin 之前的位置
	// 但是由于指针位置判断在后面，先执行的是 ++*end，导致访问非法内存，产生严重错误
	// 使用指针千万千万千万小心小心小心！！！！！！
	while ((end >= begin) && (++*end > '9')) {
		*end = '0';
		--end;
	}
	// 根据进位所在的位置判断加法运算是否溢出，如果超过的最开始的位置，那么就溢出
	// 否则视为加法成功返回 true
	// 调用函数根据此去判断加法运算是否成功

	// 还可以根据 strcmp 函数，比较number数组和字符串 "999..9999" 是否相等
	// 如果不相等则可以相加，否则不能相加，会导致溢出
	// 不过这种思路的时间复杂度会高些，因为 strcmp 的时间复杂度为 O(n)
	// 上述利用指针位置的思路只需要 O(1)，比较一次指针即可

	if (end >= begin) 
		return true;
	else
		return false;
}

void printBigInt(char *number) {
	// 实际上这里使用static有其局限性，之后再修改
	static int count = 0;
	while (*number == '0')
		++number;
	std::cout << number << '\t';
	count++;
	if (count % 10 == 0)
		std::cout << std::endl;
}

int main(void) {
	std::size_t n;
	while (std::cin >> n) {
		printOneToMax(n);
		std::cout << std::endl;
	}
}


// 利用全排列求解问题的思路，显然用到了递归
// 递归思路解决全排列，假设最后一个数字是0 ，则剩下高位全排列
//					 假设最后一个数字是1, 则剩下高位全排列
//                   以此类推，每次完成一个数，打印之

void printToMaxByRecursion(int n) {

}

void fullPermutation(char *start, char *end) {
	if (start != end) {
		for (int i = 0; i <= 9; i++) {
			char c = *start;
			*end = '0' + i;
			fullPermutation(start++, end);
			std::cout << start <<;
			*end = c;
		}
	} else {
		for (auto i = )
	}
}

