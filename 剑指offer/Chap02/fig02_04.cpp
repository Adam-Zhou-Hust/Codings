/**
 * 替换字符串中的空格字符为 %20
 * 高效 时间复杂度 O(n) 
 * 很显然，应该确定好最终的位置后，从后往前移动字符
 * 如果从前往后移动，那么会导致很多次重复移动，因为，除了最后一次，其余移动
 * 都不是把字符移到最终的位置
 */

// 关键点：
// 1.两个指针，分别指向最终的末尾 当前字符的末尾
// 2.从后往前开始处理空字符，避免重复的移动
// 3.注意循环的边界条件

#include <iostream>
#include <cstring>

const int SIZE = 1000;

// 前提：保证 str 的空间能够容纳替换后的字符
void replaceBlank(char *str, int length) {
	// 计算空格的位置和最终字符串的末尾位置
	int blankNum = 0;
	for (auto p = str; *p != '\0'; p++)
		if (*p == ' ')
			blankNum++;
	auto endOfFinal = str + length + blankNum*2 + 1;
	auto endOfCurr = str + length + 1;

	// 空格处理完毕的标志是 endOfFinal 追上 endOfCurr
	// 或者第一个指针已经走到第一个字符

	while (endOfCurr!= str) {
		if (*endOfCurr != ' ') 
			*endOfFinal-- = *endOfCurr--;
		else {
			endOfCurr--;
			*endOfFinal-- = '0';
			*endOfFinal-- = '2';
			*endOfFinal-- = '%';
		}
	}
}

int main(int argc, char *argv[]) {
	using namespace std;

	char str[SIZE] = "we are happy.";
	int len = strlen(str);
	cout << "Before replace:" << endl << str << endl;
	replaceBlank(str, len);
	cout << "After replace:" << endl << str << endl;
	return 0;
}