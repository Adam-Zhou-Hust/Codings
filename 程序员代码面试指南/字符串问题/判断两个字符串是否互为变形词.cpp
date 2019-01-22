// 很明显使用到hash表的思想

#include <iostream>
#include <string>
using namespace std;

class Solution {
public:
    bool isDeformation(const string &str1, const string &str2);
};

bool Solution::isDeformation(const string &str1, const string &str2) {
    int arr[256] = {0};
//  int arr2[256] = {0};
    for (int i = 0; i < str1.size(); i++) {
        arr[str1[i]]++;
    }
    // 最开始的做法是，分别统计，但是起始效率还可以提高一些
    // 实际上，只要保证，第二个字符串中出现的字符，在第一个字符串中也出现
    // 同时，出现的次数必须一致
    // 也即是，针对第二个字符串中的每个字符，在第一个字符串统计的map数组中
    // 对应的统计值不为0，同时，作为一次消耗，其值减1
    // 因此具有更加高效的做法
/*
    for (int i = 0; i < str2.size(); i++) {
        arr2[str1[i]]++;
    }
    for (int i = 0; i < 256; i++) {
        if (arr1[i] != arr2[i]) {
            return false;
        }
    }
*/
    for (int i = 0; i < str2.size(); i++) {
        if (arr[str2[i]]-- == 0) {
            return false;
        }
    }
    return true;
}

int main(int argc, char *argv[]) {
    string s1, s2;
    Solution solu;
    while (cin >> s1 >> s2) {
        cout << (solu.isDeformation(s1, s2) ? "Yes": "No") << endl;
    }
    return 0;
}