#include <iostream>
#include <vector>
#include <string>
#include <utility>
using namespace std;
// 递归的简单应用
// 显然，每次都往四个方向走，同时为了避免由于四个方向都可以走导致往回走进而导致死循环
// 走过的格子无需再走，因此需要一个record结构记录哪些格子走过
// #define SHOW_MATRIX
class Solution {
public:
#ifndef SHOW_MATRIX
	int movingCount(int rowNumber, int colNumber, int threashol);
#else
	pair<int, pair<vector<int>, int>> movingCount(int rowNumber, int colNumber, int threashold);
#endif
private:
	int doMovingCount(vector<int> &visitRecord, int rowNumber, int colNumber, int threashold, int x, int y);
	bool checkIfBlocked(const vector<int> &visitRecord, int threashold, int rowNumber, int colNumber, int x, int y);
	int sumOfIndex(int x, int y);
	int getNumberOfIndex(int index);
};

#ifndef SHOW_MATRIX
int Solution::movingCount(int threashold, int rowNumber, int colNumber) {
#else
pair<int, pair<vector<int>, int>> Solution::movingCount(int threashold, int rowNumber, int colNumber) { 
#endif
	// 0表示没有访问过，1表示已经访问
	vector<int> visitRecord(rowNumber * colNumber, 0);
#ifndef SHOW_MATRIX 
	return doMovingCount(visitRecord, rowNumber - 1, colNumber - 1, threashold, 0, 0);
#else
	// 因为函数参数求值的不确定性，因此分两步写
	int cnt =  doMovingCount(visitRecord, rowNumber - 1, colNumber - 1, threashold, 0, 0);
	return {cnt, {visitRecord, colNumber}};
#endif 
}

int Solution::doMovingCount(vector<int> &visitRecord, int rowNumber, int colNumber, int threashold, int x , int y) {
	if (checkIfBlocked(visitRecord, threashold, rowNumber, colNumber, x, y)) {
		visitRecord[x * (colNumber + 1)+ y] = 1;
		return 1 + doMovingCount(visitRecord, rowNumber, colNumber, threashold, x - 1, y) +
			   doMovingCount(visitRecord, rowNumber, colNumber, threashold, x + 1, y) +
			   doMovingCount(visitRecord, rowNumber, colNumber, threashold, x , y - 1) +
			   doMovingCount(visitRecord, rowNumber, colNumber, threashold, x , y + 1);
	}
	return 0;
}

inline
int Solution::getNumberOfIndex(int index) {
	int ret = 0;
	while (index != 0) {
		ret += index % 10;
		index /= 10;
	}
	return ret;
}

inline
int Solution::sumOfIndex(int x, int y) {
	return getNumberOfIndex(x) + getNumberOfIndex(y);
}

inline
bool Solution::checkIfBlocked(const vector<int> &visitRecord, int threashold, int rowNumber, int colNumber, int x, int y) {
	return 0 <= x && x <= rowNumber && 0 <= y && y <= colNumber &&
		   !visitRecord[x * (colNumber + 1) + y] && sumOfIndex(x, y) <= threashold;
}


int main(int argc, char *argv[]) {
	int rowNumber, colNumber, threashold;
	Solution solution;
	while (cin >> rowNumber >> colNumber >> threashold) {
#ifndef SHOW_MATRIX
		cout << "可以走的格子为" << solution.movingCount(threashold, rowNumber, colNumber) << endl;
#else
		auto ret = solution.movingCount(threashold, rowNumber, colNumber);
		cout << "可以走的格子为" << ret.first << endl;
		auto &vec = ret.second.first;
		for (int i = 0; i < vec.size(); i++) {
			cout << (vec[i] ? 'X': 'O') << ' ';
			if (!((i + 1) % ret.second.second)) 
				cout << endl;
		}
#endif 	
	}
	return 0;
}
