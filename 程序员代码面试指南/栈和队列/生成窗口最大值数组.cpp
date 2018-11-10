#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <deque>
#include <cassert>
using namespace std;

// 滑动窗口的思想，非常巧妙的使用双端队列，队列内部的值都是可能成为接下来的其他窗口或者当前窗口的最大值
// 同时，对于已经排除在任何窗口之外的失效的值，也要从队列中删除，保证队列内都是可能的有效值
// 针对出队，可以考虑每次遍历到原始数组中某个的位置时，都要比较一下当前队列队头元素在原队列的下标和当前的元素的下标
// 看是否已经无效，无效则这个队头元素出队
// 考虑入队，当队列为空，显然，遍历到的当前原始数组中的值，直接放入队列中
// 若队列非空，则考虑

class Solution {
public:
	vector<int> maxSlidingWindow(const vector<int>& arr, int windowSize);
};

vector<int> Solution::maxSlidingWindow(const vector<int>& arr, int windowSize) {
	assert(windowSize <= arr.size());
	deque<int> idxRecord;
	vector<int> ret;
	for (int i = 0; i < arr.size(); i++) {
		while (!idxRecord.empty() && arr[i] >= arr[idxRecord.back()]) {
			idxRecord.pop_back();
		}
		idxRecord.push_back(i);
		if (idxRecord.front() == i - windowSize) {
			idxRecord.pop_front();
		}
		// 判断是否需要加入最大值到ret中
		if (i >= windowSize - 1) {
			ret.push_back(arr[idxRecord.front()]);
		}
	}
	return ret;
}

int main(void) {
	Solution solution;
	vector<int> arr;
	int n, val, k;
	while (cin >> n >> k) {
		while (n--) {
			cin >> val;
			arr.push_back(val);
		}
		auto ret = solution.maxSlidingWindow(arr, k);
		for_each(ret.begin(), ret.end(), [](int val) { cout << val << ' ';});
		arr.clear();
	}
}