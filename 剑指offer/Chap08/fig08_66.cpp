#include <iostream>
#include <string>
using namespace std;

// 这道题目属于回溯思路的典型应用，而回溯通常以递归的形式编写
// 题目要求判断路径是否存在，基本的思路就是从一个点出发，然后递归的在四个方向上搜索
// 而回溯中，重要的一点是，当返回上一层递归时，要恢复之前的状态，在本题中表现为
// 每次回溯完毕后，返回上一层之前，恢复本节点的未访问状态

// 同时，既然是递归写法，就要注意，判断路径存在的条件是什么，不存在的条件是什么，递归的基准的情况
// 递归的情况，先把代码思路想好

class Solution {
public:
	bool hasPath(char *matrix, int rows, int colunms, const char *str);
	bool hasPath(char *matrix, int rows, int colunms, const char *str, int i, int j, int *visited);
};

bool Solution::hasPath(char *matrix, int rows, int colunms, const char *str) {
	if (matrix == nullptr || rows <= 0 || colunms <= 0 || str == nullptr)
		return false;
	int *visited = new int[rows * colunms] {0};
	// 从每个点判断，作为下面递归算法的起始点
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < colunms; j++) 
			if (hasPath(matrix, rows, colunms, str, i, j, visited))
				return true;

	delete [] visited;

	return false;
}

bool Solution::hasPath(char *matrix, int rows, int colunms, const char *str, int i, int j, int *visited) {
	if (*str == '\0')
		return true;         // 说明路径走完，正确匹配
	// 本字符匹配的情况
	bool result = false;    // 判断矩阵的位置是否可以越界
	if (i >= 0 && i < rows && j >= 0 && j < colunms && *str == matrix[i * colunms + j] &&
		visited[i * colunms + j] == 0) {  
			// 先标记本处字符已经被访问过
			visited[i * colunms + j] = 1;
			// 然后在四个方向 左右上下 上回溯，回溯完成后，需要恢复本处节点处于未访问的状态
			result = hasPath(matrix, rows, colunms, str + 1, i, j - 1, visited) ||
					 hasPath(matrix, rows, colunms, str + 1, i, j + 1, visited) ||
					 hasPath(matrix, rows, colunms, str + 1, i - 1, j, visited) ||
					 hasPath(matrix, rows, colunms, str + 1, i + 1, j, visited);
			visited[i * colunms + j] = 0;     // 恢复先前的状态
	}
	return result;
}

int main(int argc, char *argv[]) {
	Solution solution;
	char matrix[] = {
		'a', 'b', 'c', 'e',
		's', 'f', 'c', 's',
		'a', 'd', 'e', 'e'
	};
	int rows = 3, colunms = 4;
	string s;
	while (cin >> s) {
		cout << (solution.hasPath(matrix, rows, colunms, s.c_str()) ? "存在这个路径" : "不存在这个路径") << endl;
	}
}