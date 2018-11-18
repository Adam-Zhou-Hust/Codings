// 三种操作
// 编号x的人，进入长队
// 长队的队首出队伍，并给出出队伍的人的编号
// 停止模拟

// 一共有t个团队的人
// 实际上是一个队列模拟题，有两种队列，总队列和每个团队的队列
// t个团队分别1个队列保存
// 针对于进队列，很好操作，直接进入相应团队的队列即可
// 针对出队，必须先判断当前是哪个团队的人在队伍首部，然后从这个队列中出队一个即可
// 因此，问题的关键则是，如何保存判断总的队伍的队首是哪个队伍
// 同时，如果总队列首部的团队的队伍全部出队后，就是下一个团队的队列在首部的，注意更新

// 个人思路
// deque + set + vector 的数据结构
// set<int> 存在当前在整个队列中有成员的团队编号，用于快速查找
// deque<int> 存放目前在整个队列中的团队的编号（按照出入的次序），主要是保存团队在队列中的排序
// vector<deque<int>> 存放具体的队列的元素，vector的下标则是团队的编号，deque用于保存具体的成员的编号


#include <iostream>
#include <string>
#include <map>
#include <queue>
#include <deque>
#include <algorithm>
#include <vector>
using namespace std;

class TeamStructure {
public:
	TeamStructure(int n);
	void enqueue(int idx, int num);
	int dequeue();
private:
	vector<deque<int>> teamMembers;
	set<int> teamMap;
	deque<int> teamOrder;
};

TeamStructure::TeamStructure(int n) : teamMembers(n, deque<int> ()) { }

void TeamStructure::enqueue(int idx, int num) {
	// idx为所在团队编号，num为自身的编号
	teamMembers[idx - 1].push_back(num);
	// 查看之前总队列中是否存在此队列，如果不存在，则添加到总队列的尾部
	if (teamMap.find(idx - 1) == teamMap.end()) {
		teamOrder.push_back(idx - 1);
		teamMap.insert(idx - 1);
	}
}

int TeamStructure::dequeue() {
	assert(!teamOrder.empty());
	int idx = teamOrder.front();
	assert(!teamMembers[idx].empty());
	int num = teamMembers[idx].front();
	teamMembers[idx].pop_front();
	if (teamMembers[idx].empty()) {
		teamMap.erase(idx);
		teamOrder.pop_front();
	}
	return num;
}
