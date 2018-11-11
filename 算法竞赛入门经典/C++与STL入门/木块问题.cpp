// 没怎么看懂题意
// 先看代码再说

#include <cstdio>
#include <string>
#include <vector>
#include <iostream>
using namespace std;

const int maxn = 30;
int n;
vector<int> pile[maxn];

// 找到木块对应的堆和高度
void find_block(int a, int& p, int& h) {
	for (p = 0; p < n; p++) {
		for (h = 0; h < pile[p].size(); h++) {
			if (pile[p][h] == a)
				return ;
		}
	}
}  