#include <string>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <numeric>
#include <iostream>
#include <algorithm>
using namespace std;
class RemovingParenthesis {
protected:

	string s;
	bool vis[22];
	int n, ans;
	vector<int> p1, p2;

	bool check() {
		int sum = 0;
		for (int i = 0; i < n; ++i)
			if (!vis[i]) {
				if (s[i] == '(')
					++sum;
				else if (--sum < 0)
					return false;
			}
		return sum == 0;
	}

	void dfs(int step, int pre = 0) {
		if (step == n) {
			ans += 1;
			return;
		}
		if (pre) {
			for (int i : p2)
				if (!vis[i] && s[i] == ')') {
					vis[i] = true;
					if (check()) dfs(step + 1, 0);
					vis[i] = false;
				}
		} else {
			for (int i : p1)
				if (!vis[i] && s[i] == '(') {
					vis[i] = true;
					dfs(step + 1, 1);
					vis[i] = false;
					break;
				}
		}
	}

public:
	int countWays(string s) {
		this->s = s;
		this->n = s.length();
		this->ans = 0;
		memset(vis, 0, sizeof vis);
		p1.clear(), p2.clear();
		for (int i = 0; i < n; ++i)
			if (s[i] == '(') p1.push_back(i);
			else p2.push_back(i);
		dfs(0);
		return ans;
	}
};

// BEGIN CUT HERE

int main() {
	int ANS = RemovingParenthesis().countWays("(((((((((())))))))))");
	cout << ANS << endl;
	return 0;
}

// END CUT HERE
