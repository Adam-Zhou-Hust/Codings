// fig04_20.cpp

// 顺时针打印矩阵
// 输入一个矩阵，按照从外向里 以顺时针的顺序依次打印出每一个数字
// 例子

/**
 *  1	2	3	4	-1
 *  5	6	7	8	-2
 *  9	10	11	12	-3
 *  13  14  15  16	-4
 */

// 打印结果: 1 2 3 4 8 12 16 15 14 13 9 5 6 7 11 10

// 由于矩阵是 MxN 矩阵，因此不能单独考虑 N 阶矩阵这种情形，而应该考虑到各种可能的矩阵形式
// 首先是边界条件，每次循环的边界条件
// 再次是每个循环内部如何打印出四个走向上的数据

#include <cassert>
#include <iostream>
#include <stdexcept>

void PrintOneCircle(int **, int, int, int, int);

void PrintMatrix(int **matrix, int rows, int columns) {
	int leftUpx = 0, leftUpy = 0;
	int rightDownx = columns-1, rightDowny = rows-1;

	while (leftUpx <= rightDownx && leftUpy <= rightDowny) {
		PrintOneCircle(matrix, leftUpx, leftUpy, rightDownx, rightDowny);
		leftUpx++, leftUpy++;
		rightDownx--, rightDowny--;
	}
	std::cout << std::endl;
}

void PrintOneCircle(int **matrix, int leftUpx,
								  int leftUpy,
								  int rightDownx,
								  int rightDowny) {
	// 打印左右 右下 下左 左上 四个方向上的数据
	//  左右方向
	for (int i = leftUpx; i <= rightDownx; i++)
		std::cout << matrix[leftUpy][i] << ' ';
	// 右下方向
	for (int i = leftUpy+1; i <= rightDowny; i++)
		std::cout << matrix[i][rightDownx] << ' ';
	// 下左方向
	for (int i = rightDownx-1; i >= leftUpx; i--)
		std::cout << matrix[rightDowny][i] << ' ';
	// 左上方向
	for (int i = rightDowny-1; i >= leftUpy+1; i--)
		std::cout << matrix[i][leftUpx] << ' ';
}

void Test() {
	int a[] = {1,2,3,4,-1};
	int b[] = {5,6,7,8,-2};
	int c[] = {9,10,11,12,-3};
	int d[] = {13,14,15,16,-4};

	int *(matrix[]) = {a,b,c,d};
	int *tmp = &b[0];
	int **matrix2 = &(tmp);

	PrintMatrix(matrix, 4, 5);
	PrintMatrix(matrix2, 1, 1);
}

int main(void) {
	Test();
	return 0;
}