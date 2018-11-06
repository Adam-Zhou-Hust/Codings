/**
 * 输入一个整数数组，实现一个函数，调整数组中数字的顺序
 * 使得所有的奇数位于数组的前半部，偶数位于数组的后半部 
 */

// 这道题目，首先让我想到的是快速排序中，根据枢纽元素，把整个数组分为两部分
// 左边为小于枢纽元素的集合，右边为大于枢纽元素的集合
// 用到的是首尾指针，思想是元素交换，从而在O(n)时间内完成元素的一次排列
// 很显然，此题也是一样，两个指针，首指针指向左边第一个偶数，尾指针指向右边第一个奇数，交换之
// 迭代，直到两个指针位置颠倒，很显然，存在下列做法

#include <iostream>

inline
void Exchange(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void DoDivideTwoPart(int *_start, int *_end) {
    int *start = _start, *end = _end;
    while (start < end) {
        while (start <= _end && (*start) % 2 != 0)
            start++;
        while (end >= _start && (*end) % 2 == 0)
            end--;
        if (start < end) 
            Exchange(start, end);
    }
}

void DivideTwoPart(int *arr, int length) {
    int *start = arr;
    int *end = arr + length - 1;
    DoDivideTwoPart(start, end);
}

inline
void PrintArray(int *arr, int length) {
    int *start = arr;
    int *end = arr + length;
    for (; start != end; start++)
        std::cout << *start << '\t';
    std::cout << std::endl;
}

inline
void DoTest(int *arr, int length) {
    PrintArray(arr, length);
    DivideTwoPart(arr, length);
    PrintArray(arr, length);
    std::cout << std::endl;
}

void Test() {
    // 测试用例考虑
    // 全奇数、全偶数一定要考虑到 
    // 单个元素的数组

    int a[] = {1};
    int b[] = {1,2,3,4,5,6,7,8,9,10};
    int c[] = {1,3,5,7,9,2,4,6,8,10};
    int d[] = {2,4,6,8,10,1,3,5,7,9};
    int e[] = {2,4,76,2,4,3,7,25,39,1,2,0,87,65,34,3};
    int f[] = {4,4,4,4,4,4,4};
    int g[] = {9,9,9,9,9,9,9};

    DoTest(a, sizeof(a)/sizeof(a[0]));
    DoTest(b, sizeof(b)/sizeof(b[0]));
    DoTest(c, sizeof(c)/sizeof(c[0]));
    DoTest(d, sizeof(d)/sizeof(d[0]));
    DoTest(e, sizeof(e)/sizeof(e[0]));
    DoTest(f, sizeof(f)/sizeof(f[0]));
    DoTest(g, sizeof(g)/sizeof(g[0]));
    
}

/*
int main() {
    Test();
    return 0;
}
*/

// 现在考虑一个扩展性
// 本质上，我们是利用交换完成Partition操作，而Partition的条件是左边偶数，右边奇数
// 考虑，另外的partition条件，比如按照正负，把数组Partiton为两个部分
// 比如，按照被3整除分类，能够被整除，在左侧，其余右侧
// 诸如此类，让我们明白实际上，关键在于这个条件
// 不同的条件，不同的分类方法 
// 不可能为了不同的条件就重新写全部函数
// 应该把不变的框架部分，也就是交换部分，提取出来
// 变化的是条件，把条件抽取出来，很容易想到函数指针
// 把判断函数作为一个参数，传递给Partition函数
// 联想到C++中的可调用对象，很容易有下列代码

typedef bool (*Judge)(int);
void Partition(int *arr, int length, Judge f) {
    int *start = arr;
    int *end = arr + length - 1;
    while (start < end) {
        while ((start <= arr + length -1)  && f(*start))
            start++;
        while ((end >= arr) && !f(*end))
            end--;
        Exchange(start, end);
    }
}

// 按照是否大于10，分左右两半部分，小于在左边，大于右边
bool IfSmaller(int a) {
    if (a <= 10)
        return true;
    return false;
}

int main() {
    int a[] = {100,200,300,13,3,4,6,7,120,45,36,0,7,1,2,3,4,5,67};
    PrintArray(a, sizeof(a)/sizeof(a[0]));
    Partition(a, sizeof(a)/sizeof(a[0]), IfSmaller);
    PrintArray(a, sizeof(a)/sizeof(a[0]));
    return 0;
}
