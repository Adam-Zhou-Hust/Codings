//	第一个只出现一次的字符
//	很明显，要使用映射结构，比如哈系表
//  考虑STL中并没直接可使用的哈系表，而且这里只需要很间的字符-数字的映射
//  字符使用ASCII编码，那么最多256个，建立一个数字即可

#include <iostream>

const int size = 256;

char firstOfNotrepeated(const char *pString) {
	if (pString == nullptr)
		return '\0';
	int hashTable[size];
	for (int i = 0; i < size; ++i)
		hashTable[i] = 0;
	for (const char *p = pString; *p != '\0'; ++p)
		++hashTable[*p];
// Debug
//	for (int i = 0; i < size; ++i)
//		std::cout << hashTable[i] << " ";
//	std::cout << std::endl;
// Debug
    int i = 0;
    while (pString[i] != '\0') {
    	if (hashTable[pString[i]] == 1)
    		return pString[i];
    	i++;
    }
    return '\0';
}

int main(void) {
	const char *pString = "abaccdeff";
	char result = firstOfNotrepeated(pString);
	std::cout << "在字符串 " << pString << " 第一个出现的字符是 " << result << std::endl;
	return 0;
}
