#include <iostream>
using namespace std;

class A { };

class B {
public:
	virtual ~B() { }  // for the virtual function
};                    // a vptr pointer will be added to the memory model of this object

int main(void) {
	A a;
	B b;
	cout << "size of A : " << sizeof(a) << endl;
	cout << "size of B : " << sizeof(b) << endl;
	return 0;
}

/**
 size of A : 1
 size of B : 8
 */