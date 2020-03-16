#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

// 找到数组中任意一个重复的数字
// 理解为，找到第一个重复的数字即可
// 1.排序，然后遍历
// 2.哈希表存放，遇到第一个重复的就直接return
// 3.主要考虑，如果存在重复的数字，那么排序后的数组，有些元素存在，有些不存在
class Solution {
public:
	int findFirstDup(vector<int> &numbers) {
		// 利用hash
		int length = numbers.size();
		vector<int> table(length, 0);
		for (int i = 0; i < length; i++) {
			table[numbers[i]]++;
			if (table[numbers[i]] > 1)
				return numbers[i];
		}
		cout << "不存在重复的元素" << endl;
		return -1;
	}
};

int main(void) {
	Solution solu;
	int var;
	vector<int> numbers;
	while (cin >>var) 
		numbers.push_back(var);
	int result = solu.findFirstDup(numbers);
	if (result != -1)
		cout << "第一个重复的元素是" << result << endl;
	return 0;
}