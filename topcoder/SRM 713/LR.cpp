#include <string>
#include <vector>
#include <cstdlib>
#include <numeric>
#include <iostream>
#include <algorithm>

using namespace std;

class LR {

protected:

	inline void LL_oper(vector<long long> &s, int times) {
		const int n = s.size();
		while (times--) {
			long long left_one = s[n - 1], temp;
			for (int i = 0; i < n; ++i)
				temp = s[i], s[i] += left_one, left_one = temp;
		}
	}

	inline void RR_oper(vector<long long> &s, int times) {
		const int n = s.size();
		while (times--) {
			long long right_one = s[0], temp;
			for (int i = n - 1; ~i; --i)
				temp = s[i], s[i] += right_one, right_one = temp;
		}
	}

public:
	string construct(vector<long long> s, vector<long long> t) {
		const int n = s.size();

		for (int i = 0; i < n; ++i) if (s[i] > t[i]) return "No solution";

		if (s == t) return "";

		long long sum_s = accumulate(s.begin(), s.end(), 0ll);
		long long sum_t = accumulate(t.begin(), t.end(), 0ll);

		if (sum_s == 0 || sum_t % sum_s) return "No solution";

		long long diff = sum_t / sum_s, p2(1), times(-1);

// BEGIN CUT HERE
		cout << diff << endl;
// END CUT HERE
		for (int i = 0; ; ++i, p2 <<= 1) {
			if (p2 == diff) {
				times = i;
				break;
			}
			if (p2 > diff) break;
		}

		if (times < 1) return "No solution";

		for (int i = 0; i <= times; ++i) {
			vector<long long> copy_one(s);
			LL_oper(copy_one, i);
			RR_oper(copy_one, times - i);
			if (copy_one == t)
				return string(i, 'L') + string(times - i, 'R');

// BEGIN CUT HERE

			cout << i << endl;
			for (long long x : copy_one) cout << x << " ";
			cout << endl;

// END CUT HERE
		}

		return "No solution";

	}
};


// BEGIN CUT HERE

int main() {

	vector<long long> s({0,1,0,0,0}), t({0,1,2,1,0});

	cout << LR().construct(s, t) << endl;

}

// END CUT HERE


// Powered by FileEdit
// Powered by TZTester 1.01 [25-Feb-2003]
// Powered by CodeProcessor
