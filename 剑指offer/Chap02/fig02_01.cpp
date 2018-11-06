/**
 * 赋值运算符的完成
 * 给 CMyString 添加拷贝赋值操作
 * 1.考虑自赋值的情况，要正确处理
 * 2.考虑申请构造对象时候，抛出异常，因此对于释放内存的顺序有要求----重点要保证异常安全
 * 3.利用 swap 函数完成拷贝赋值函数
 */

#include <cstring>
#include <iostream>
#include <string.h>

class CMyString {
	friend opearator <<(std::ostring&,const CMyString&);
public:
	// CMyString(char *pData = NULL);
	CMyString(const char *pData = NULL);
	CMyString(const CMyString &str);
	CMyString& opearator =(const CMyString &rhs);
	~CMyString();
private:
	char *allocMem(const char *p);
	char *m_pData
};

// 基本做法
// 先分配内存，在释放原来的内存，保证了只有在新内存被正确分配之后才会执行 delete [] 操作

CMyString& 
CMyString::operator =(const CMyString &rhs) {
	if (this != &rhs) {
		char *tmp = new char[strlen(rhs.m_pData) + 1];
		strcpy(tmp, rhs.m_pData);
		delete [] m_pData;
		m_pData = tmp;
	} 
	return *this;
}

// 另一种思路
// 创建另一个临时对象，让临时对象和原对象交换 (让内存分配操作不直接体现在代码中)
// 仍然是先配分配好内存再通过交换完成赋值
// 这种情况下，甚至可以省略自赋值的情况，但是为了减少不必要的内存分配，还是加上一个判断，优化性能
// 前提是必须定义一个公有swap成员

CMyString&
CMyString::operator =(const CMyString &rhs) {
	if (this != &rhs) {
		CMyString tmpString(rhs);
		char *temp = tmpString.m_pData;
		tmpString.m_pData = m_pData;
		m_pData = temp;
		//this->swap(tmp);   
	} 
	return *this;
}

