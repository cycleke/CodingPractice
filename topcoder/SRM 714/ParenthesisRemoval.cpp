#include <string>
#include <vector>
#include <cstdlib>
#include <sstream>
#include <cstring>
#include <numeric>
#include <iostream>
#include <algorithm>
using namespace std;

class ParenthesisRemoval {
public:
	int countWays(string s) {
		const int n = s.length(), mod = 1e9 + 7;
		int ans = 1, cnt = 0;
		for (int i = 0; i < n; ++i)
			if (s[i] == '(') ++cnt;
			else ans = 1ll * ans * (cnt--) % mod;
		return ans;
	}

// BEGIN CUT HERE
public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "()()()()()"; int Arg1 = 1; verify_case(0, Arg1, countWays(Arg0)); }
	void test_case_1() { string Arg0 = "(((())))"; int Arg1 = 24; verify_case(1, Arg1, countWays(Arg0)); }
	void test_case_2() { string Arg0 = "((()()()))"; int Arg1 = 54; verify_case(2, Arg1, countWays(Arg0)); }
	void test_case_3() { string Arg0 = "(())(())(())"; int Arg1 = 8; verify_case(3, Arg1, countWays(Arg0)); }
	void test_case_4() { string Arg0 = "((((())((((((((((()((((((()))))())))))()))))))))))"; int Arg1 = 948334170; verify_case(4, Arg1, countWays(Arg0)); }

// END CUT HERE
};

// BEGIN CUT HERE

int main() {
	ParenthesisRemoval ___test;
	___test.run_test(-1);
	return 0;
}

// END CUT HERE
