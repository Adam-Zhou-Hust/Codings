#include <iostream>
#include <string>
using namespace std;

// 完成一个不能被继承的类
// 思路一
// 考虑把构造函数设置为私有，那么肯定不能继承
// 但是，也无法直接生成对象，那么只能使用工厂方法来获取对象

// 思路二
// C++11实际上已经支持了final关键字，类似于Java语言
// final可以修饰虚函数，被修饰的虚函数，则不能被子类覆盖

// 思路一代码

class NonDerived {
public:
	static NonDerived *getInstance() {
		static NonDerived instance;
		return &instance;
	}
	/*************Test************************/
	int setVar(int var) {
		value = var;
	}
	int getVar() const {
		return value;
	}
	/*************Test***********************/
private:
	NonDerived(int var = 0) : value(var) {}
	~NonDerived() { }
	int value;
};

int main(void) {
	NonDerived *obj = NonDerived::getInstance();
	obj->setVar(99);
	cout << obj->getVar() << endl;

//	NonDerived d;
//	NonDerived *d = new NonDerived(88);
// 直接报错，由于构造函数私有
	return 0;
}