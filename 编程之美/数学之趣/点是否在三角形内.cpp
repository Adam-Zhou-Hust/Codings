// 判断点是否在三角形内

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

// 方法一：
// 点在三角形内，则该点和另外三角形的三个点组成的三个小三角形面积之和与大三角形面积相等
// 三角形面积计算公式（海伦公式）
struct Point {
    double x, y;
};

void ComputeEdge(Point A, Point B, Point C, double &a, double &b, double &c);
bool isInTriangle(Point A, Point B, Point C, Point D);

double Area(Point A, Point B, Point C) {
    double a, b, c;
    ComputeEdge(A, B, C, a, b, c);
    double p = (a + b + c) / 2;
    return sqrt((p - a) * (p - b) * (p - c) * p);
}

void ComputeEdge(Point A, Point B, Point C, double &a, double &b, double &c) {
    double ab, ac, bc;
    a = sqrt((A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y));
    b = sqrt((A.x - C.x) * (A.x - C.x) + (A.y - C.y) * (A.y - C.y));
    c = sqrt((B.x - C.x) * (B.x - C.x) + (B.y - C.y) * (B.y - C.y));
}

double err = 1e-10;

bool isInTriangle(Point A, Point B, Point C, Point D) {
    // 浮点数的比较和判断和整数不同，一定要上误差
    if (abs((Area(A, B, D) + Area(A, C, D) + Area(B, C, D) - Area(A, B, C)))> err)
        return false;
    return true;
}

int main(int argc, char *argv[]) {
    Point A = {0, 0};
    Point B = {3, 0};
    Point C = {0, 3};
    Point D = {1, 1};
    cout << (isInTriangle(A, B, C, D) ? "True" : "False") << endl;
    return 0;
}
