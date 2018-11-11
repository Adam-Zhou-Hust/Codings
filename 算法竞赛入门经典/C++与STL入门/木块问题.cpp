// 没怎么看懂题意
// 先看代码再说

// 原来是一个移动木块的问题，主要考察vector的相关操作
// 逻辑上主要是抽取出函数，同时注意push_back pop_back resize的使用即可

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

// 把第p堆上高度为h的木块上方的所有木块移会原位
void clear_above(int p, int h) {
	for (int i = h + 1; i < pile[p].size(); i++) {
		int b = pile[p][i];
		pile[b].push_back(b);
	}
	pile[p].resize(h + 1);    // 只保留下标为0～h的木块，其余放置到正确的位置上
}

// 把第p堆上高度为h的及其上方的木块整体移动到p2堆的顶端
void pile_onto(int p, int h, int p2) {
	for (int i = h; i < pile[p].size(); i++) {
		pile[p2].push_back(pile[p][i]);
	}
	pile[p].resize(h);
}

void print() {
	for (int i = 0; i < n; i++) {
		cout << i << ":";
		for (int j = 0; j < pile[i].size(); j++) {
			cout << pile[i][j];
		}
		cout << endl;
	}
}

int main(int argc, char *argv[]) {
	int a, b;
	cin >> n;
	string s1, s2;
	for (int i = 0; i < n; i++) {
		pile[i].push_back(i);
	}
	while (cin >> s1 >> a >> s2 >> b) {
		int pa, pb, ha, hb;
		find_block(a, pa, ha);
		find_block(b, pb, hb);
		if (pa == pb) {
			continue;
		}
		if (s2 == "onto") {
			clear_above(pb, hb);
		}
		if (s1 == "move") {
			clear_above(pa, ha);
		}
		pile_onto(pa, ha, pb);
	}
	print();
	return 0;
}