#include <bits/stdc++.h>
using namespace std;
class BalancedStrings {
	public:
	vector <string> findAny(int N) {
		vector<string> ret;
		if (N <= 26) {
			for (int i = 0; i < N; ++i)
				ret.push_back(string(1, 'a' + i));
			return ret;
		}
		int res = 0;
		for (int i = 0; i < N - 4; ++i) {
			ret.push_back(string(1, 'a' + (i >> 3)));
			res += i & 7;
		}
		char c1, c2;
		for (int i = 0; i < 4; ++i) {
			c1 = 'a' + 18 + (i << 1);
			c2 = c1 + 1;
			ret.push_back(string(1, c1));
			swap(c1, c2);
			while (res && ret.back().size() < 100) {
				ret.back().push_back(c1);
				swap(c1, c2);
				--res;
			}
		}
		return ret;
	}
};

















