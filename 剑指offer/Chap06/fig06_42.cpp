// 翻转单词的顺序，但是单词内部的字符顺序不被破坏
// 比如输入的一句英文短语 I am a student.
// 则输出的英文短语则是   .student a am I
// 而不是               .tneduts a ma I
// 因此，单词内部的字符顺序不能改变

// 其实稍微思考下，发现，在直接翻转字符串之后
// 单词的内部的字符顺序是反过来
// 但是，以每个单词为操作单位，再把内部的字符顺序反过来一下
// 单词内部的字符串顺序就被矫正，从而最终得到如题要求的结果
// 因此转换分为两步，第一步，直接翻转， 第二步，单词内部翻转

// 实现代码如下所示

#include <iostream>
#include <string>
#include <stdexcekaipt>
using namespace std;

void reverse(char *start, char *end) {
	while (start < end) {
		char tmp = *start;
		*start = *end;
		*end = tmp;
		start++;
		end--;
	}
}

void reverseSentence(char *data) {
	// 先翻转整个句子
	char *start = data;
	char *end = start;
	while (*end != '\0')
		end++;
	end--;
	reverse(start, end);
	// 再翻转内部的每个单词
	char *wordStart = data;
	char *wordEnd;
	while (wordEnd <= end) {
		while (*wordStart == ' ')
			wordStart++;
		wordEnd = wordStart;
		while (*wordEnd != ' ' && wordEnd <= end)
			wordEnd++;
		wordEnd--;
		reverse(wordStart, wordEnd);
		wordStart = ++wordEnd;
	}
}

int main(void) {
	char data[] = "I am a student?";
	std::cout << "befor reverse " << data << std::endl;
	reverseSentence(data);
	std::cout << "after reverse " << data << std::endl;
	return 0;
}