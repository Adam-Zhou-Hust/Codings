#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <cassert>
using namespace std;

typedef long long LL;
const int coeff[3] = {2, 3, 5};

class Solution {
public:
	int kthUglyNumber(int k);
};

// 类似于利用优先队列，进行堆排序
int Solution::kthUglyNumber(int k) {
	assert(k >= 1);
	if (k == 1)
		return 1;
	priority_queue<LL, vector<LL>, greater<LL>> que;
	set<LL> number;
	number.insert(1); que.push(1);
	LL var;
	for (int i = 1; ; i++) {
		var = que.top();
		que.pop();
		if (i == k) {
			break;
		} else {
			for (int j = 0; j < 3; j++) {
				LL tmp = coeff[j] * var;
				if (number.find(tmp) == number.end()) {
					number.insert(tmp);
					que.push(tmp);
				}
			}
		}
	}
	return var;
}

int main(void) {
	Solution solu;
	int k;
	while (cin >> k) {
		cout << solu.kthUglyNumber(k) << endl;
	}
	return 0;
}