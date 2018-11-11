#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

// STL的sort lower_bound upper_bound equal_range的使用

int main(int argc, char **argv) {
	int n, q;
	int tmp;
	vector<int> data;
	while (cin >> n >> q) {
		while (n--) {
			cin >> tmp;
			data.push_back(tmp);
		}
		sort(data.begin(), data.end());
		while (q--) {
			cin >> tmp;
			auto res = lower_bound(data.begin(), data.end(), tmp);
			if (res != data.end() && *res == tmp) {
				cout << "found " << *res << " at " << (res - data.begin()) << " position" << endl;
			} else {
				cout << "not found" << endl;
			}
		}
		data.clear();
	}
	return 0;
}