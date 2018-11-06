/**
 * 在具有一定特征的矩阵
 * 每行元素依次增大
 * 每列元素依次增大 
 * 1    2   8   9
 * 2    4   9   12
 * 4    7   10  13
 * 6    8   11  15
 * 的矩阵中查找一个元素
 */


// 关键思路：
// 由于元素排列的特性，要利用这种特性，在比较一次元素后，能够排除一部分元素
// 因此，不能从最小数字或者最大数字开始比较，而应该从副对角线的两个端点的元素
// 开始，每比较一次，排除一行或者一列，最后找到元素或者给出提示，没有找到

#include <iostream>
#include <cassert>

using namespace std;

int matrix[][4] = {{1, 2, 8, 9},
                   {2, 4, 9, 12},
                   {4, 7, 10, 13},
                   {6, 8, 11, 15}};

bool find(int e) {
    // 从右上角元素开始查找(当然也可以从左下角开始寻找)
    // 坐标
    int x = 0;
    int y = 3;
    while (x <= 3 && y >= 0) {
        if (e == matrix[x][y])
            break;
        else if (e > matrix[x][y])
            x++;
        else
            y--;
    }
    if (x > 3 || y < 0)
        return false;
    return true;
}
// 2018.06.07 二刷
// 考虑查找的位置应该从副对角线开始

bool find(int *matrix, int rows, int columns, int number) {
    assert(matrix != nullptr);
    assert(rows > 0 && columns > 0);

    int i = 0, j = columns - 1; // 查找的起始位置
    while (i < rows && j >= 0) {
        if (matrix[i * columns + j] == number)
            return true;
        else if (matrix[i * columns + j] < number)
            i++;
        else 
            j--;
    }
    return false;
}

int main(int argc, char **argv) {
    // 利用指针遍历二维数组中的元素
    /*
    int (*pm)[4] = matrix;
    for (int i = 0; i < 4; i++) {
        auto p = pm + i;
        // cout << **p << endl;
        for (int i = 0; i < 4; i++)
            std::cout << *(*p+i) << '\t';
        std::cout << std::endl;
    }
    */
//    int e;
//    while (cin >> e) {
//        cout << (find(e) ? "found" : "not found") << endl;
//    }
    int matrix[] = {
        1,2,8,9,
        2,4,9,12,
        4,7,10,13,
        6,8,11,15
    };
    int rows = 4, columns = 4;
    int number;
    while (cin >> number) {
        cout << (find(matrix, rows, columns, number) ? "存在" : "不存在") << endl;
    }
    return 0;
}