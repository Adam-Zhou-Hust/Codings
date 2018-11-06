// 练习题  根据给出的字符序列，计算列数，实际上是进制问题

#include <iostream>
#include <string>
#include <cstring>
#include <cassert>
using namespace std;

int ComputeColumnsNum(const char *start, const char *end) {
	assert(end >= start);
	if (end == start)
		return *end-'A' + 1;
	return ComputeColumnsNum(start, end-1) * 26 + *end - 'A' + 1;
}

int ColumnsNum(const char *arr) {
	size_t length = strlen(arr);
	const char *start = arr;
	const char *end = arr + length - 1;
	return ComputeColumnsNum(start, end);
}


int main(int argc, char **argv) {
	string s;
	cout << "Please input the string :" << endl;
	while (cin >> s) {
		const char *pc = s.c_str();
		cout << pc << endl;
		cout << "Columns number is : " << ColumnsNum(pc) << endl;
		cout << "Please input the string :" << endl;
	}
	return 0;
}