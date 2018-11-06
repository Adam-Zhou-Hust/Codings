/**
 * 不使用 if else while for switch 等控制结构
 * 不使用乘除法
 * 求 1+2+3+...n的和 
 */

#include <iostream>
#include <cassert>
using namespace std;
// 思路分析


// 一开始，我首先想到的是求和通项公式，并且其中的 (1+n)/2 利用右移很好模拟
// 但是 *n 利用左移模拟，左移动次数并不好确定，还是要利用 if 判断才能完成，因此，一下子想不到方法

// 看了答案，才知道，自己的思维还是不够活跃，不够宽，以后加油吧

// 一个思路就是，既然不能循环，那就找可以替代循环的方法，其实我刚才利用位运算模拟的思路也类似，找替代
// 但是这个替代并不合适，一下子没有想到别的替代方案

// 1.循环的替代
// 思考到利用C++的语言特性，在默认构造函数中，对类的静态变量进行递增，这样，创建多少个对象，最终的值就是多少
// 至于求和，我们也可以把和 sum 放置于默认构造函数中，于是有如下解法

class Accumulate {
	public:
		Accumulate() {
			++count;
			sum += count;
		}
		static int GetSum() {
			return sum;
		}
		// 设置一个Reset函数，每次求值完毕后，需要清零，保证下次求值的正确性
		static void Reset() {
			count = 0;
			sum = 0;
		}
	private:
		static int sum;
		static int count;
};

int Accumulate::sum = 0;
int Accumulate::count = 0;

int SumVersionA(int n) {
	int result;
	Accumulate *p = new Accumulate[n];
	result = Accumulate::GetSum();
	Accumulate::Reset();
	delete [] p;
	return result;
}


// 2.递归的代替
// 显然，这种求和按照通常情况，是可以用递归去完成的，但是由于递归情况存在一个Base Condition
// 肯定需要利用 if 判断是否是 Base Condition 因此，常规的递归函数无法完成
// 联想 C++ 函数的语言特性中，如何才能表现出递归的特性呢？
// 显然，递归不能在一个类的单个函数中，因为如果仅仅是一个函数中产生递归，那么必然和 global 函数的递归没有区别
// 联想到虚函数，同时，Base Condition 应该是在基类中处理，其余情况则在派生类里递归，则有如下解法

class Base;
class Derived;
Base *A[2];

class Base {
	public:
		virtual int GetSum(unsigned int n) {
			return 0;
		}
};

class Derived : public Base {
	public:
		int GetSum(unsigned int n) {
			return n + A[!!n]->GetSum(n-1);
		}
};

int SumVersionB(int n) {
	Base b;
	Derived d;
	A[0] = &b;
	A[1] = &d;
	return A[1]->GetSum(n);
}

// 对于不能使用函数机制的C语言，则可以利用函数指针模拟这种行为

typedef unsigned int (*fun)(unsigned int);

fun FunArray[2];
unsigned int BaseCondition(unsigned int n) {
	return 0;
}

unsigned int RecurrsionCondition(unsigned int n) {
	return FunArray[!!n](n-1) + n;
}

unsigned int SumVersionC(unsigned int n) {
	FunArray[0] = &BaseCondition;
	FunArray[1] = &RecurrsionCondition;
	return FunArray[!!n](n);
}


// 利用模板元编程实现编译期完成递归，模板的特例化处理递归的基准情况，模板通用代码处理递归情况
// 比较高级的用法

template <unsigned int n>
struct SumSolution {
	enum Value {
		N = SumSolution<n-1>::N + n
	};
};

template <>
struct SumSolution<1> {
	enum Value {
		N = 1
	};
};
// 由于模板元编程，n 必须是编译器就能得到的常量，因此不能动态输入，此算法的缺陷
// 同时，递归栈不能太大，因此 n 不能太大

// Main Test
int main(int argc, char **argv) {
	int n;
	while (cin >> n) {
		cout << "Sum from 1 to " << n << " is " << SumVersionA(n) << endl;
		cout << "Sum from 1 to " << n << " is " << SumVersionB(n) << endl;
		cout << "Sum from 1 to " << n << " is " << SumVersionC(n) << endl;
	}
	// TMP 方法不能使用动态输入的 n ，因此，这里就这样测试一下了
	cout << "Sum from 1 to " << 100 << " is " << SumSolution<100>::N << endl;
	return 0;
}

// 学到的一点：当不能直接使用迭代或者递归时，可以采取的另外的方法模拟迭代和递归
// 利用 构造函数 模拟简单的迭代(通过创建多个对象)
// 利用虚函数机制，模拟递归，利用基类的虚函数模拟基准情况，派生类的虚函数处理递归情形，同时设置存放基类指针的数组

// 利用函数指针模拟递归情况，一个函数处理基准情况，另一个则递归情况，同时设置函数指针数组，类似使用虚函数

// TMP 这种用法比较高级，编译器完成计算，也属于利用模板元编程，暂时没有掌握特别好，了解一下

// 总之就是找带递归或者迭代的合适替代