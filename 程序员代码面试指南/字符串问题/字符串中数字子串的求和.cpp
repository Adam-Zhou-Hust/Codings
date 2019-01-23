// 题目要求
// 忽略小数点字符(只有整数串)
// 数字串之前如果出现奇数个-符号，则视为负数
// 数字之前如果出现偶数个-符号，则视为正数

// 本来想到使用有限状态机来写状态转换，但是好像没必要这么复杂
// 每次找到第一个数字后，查看其之前的字符(如果不是-则不用管，是-则判断个数，从而说明当前数字的符号)
// 然后开始往后面遍历，直到遇到不是数字的第一个字符停止即可，那么第一个数字找完
// 一直遍历到尾部，找到所有的数字，然后相加

// 考虑最终的和可能溢出，但是如果这么考虑，问题会比较复杂，因为字符串的长度不限制
// 实际上是一个大数问题，需要要字符串模拟，这里先简化处理，假设单个数字和和都不会溢出

// 之后有空再补上自动状态机的写法以及大数问题的写法

#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

class Solution {
public:
    long long getSum(const string &str);
};

long long Solution::getSum(const string &str) {
    int sum = 0;
    if (str.empty())
        return sum;
    const char *pstr = str.c_str();
    size_t length = str.size();
    for (int i = 0; i < length; ) {
        while (i < length && !isdigit(pstr[i])) 
            i++;
        if (i >= length)
            break;
        int var = 0;
        // 分析之前的字符，统计-字符的个数 i-(j+1)
        int j = i - 1;
        while (j >= 0 && pstr[j] == '-') 
            j--;
        // 找全本次第一个数字开始的数字字符串，并求和
        while (i < length && isdigit(pstr[i])) {
            var = var * 10 + (pstr[i] - '0');
            i++;
        }
        // 判断符号
        if ((i - (j + 1)) % 2) {
            sum -= var;
        } else {
            sum += var;
        }
    }
    return sum;
}

int main(int argc, char *argv[]) {
    string str;
    Solution solu;
    while (cin >> str) {
        cout << solu.getSum(str) << endl;
    }
    return 0;
}