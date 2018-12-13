#include <iostream>
#include <string>
#include <vector>
using namespace std;

// 前置声明
struct Node;
// 函数声明
static void test();
static void fillList(Node *&head1, Node *&head2);
static vector<int> findCommonPart(Node *head1, Node *head2);

// 打印有序链表的公共部分，注意有序，因此肯定不必暴力破解，从而避免O(N2)的时间复杂度
// 使用双指针方法，分别指向两个链表的首个节点
// 比较两个指针指向的元素的大小
// 1.相等，则找到一个公共元素，同时，两个指针均往下走一步
// 2.不相等，则其中小的指针往下走一步，然后继续循环
// 显然，当其中一个指针走到尾部，那么整个比较过程结束

struct Node {
    int var;
    Node *next;
    Node(int v, Node *n = nullptr) : var(v), next(n) {  }
};

static vector<int> findCommonPart(Node *head1, Node *head2) {
    vector<int> commonPart;
    while (head1 && head2) {
        int var1 = head1->var;
        int var2 = head2->var;
        
        if (var1 == var2) {
            head1 = head1->next;
            head2 = head2->next;
            commonPart.push_back(var1);
        } else if (var1 < var2) {
            head1 = head1->next;
        } else {
            head2 = head2->next;
        }
    }
    return commonPart;
}

static void test() {
    Node *head1, *head2;
    fillList(head1, head2);
    vector<int> commonPart = findCommonPart(head1, head2);
    cout << "公共元素为：" << endl;
    for (auto var : commonPart) {
        cout << var << ' ';
    }
    cout << endl;
}

static void fillList(Node *&head1, Node *&head2) {
    int var;
    Node *ptr1, *ptr2;
    cout << "请输入第一个链表的元素：" << endl;
    cin >> var;
    head1 = new Node(var); ptr1 = head1;
    while (cin >> var) {
        ptr1->next = new Node(var);
        ptr1 = ptr1->next;
    }
    cin.clear();
    cout << "第一个链表的元素输入完毕！" << endl;
    cout << "请输入第二个链表的元素：" << endl;
    cin >> var;
    head2 = new Node(var); ptr2 = head2;
    while (cin >> var) {
        ptr2->next = new Node(var);
        ptr2 = ptr2->next;
    }
    cin.clear();
    cout << "第二个链表的元素输入完毕！" << endl;
}

// 恢复刷题，写代码
// 两个月不写，真的要废了！！！

int main(int argc, char *argv[]) {
    test();
}
