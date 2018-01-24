#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <typeinfo>
#include <vector>

using namespace std;

const int MOD = 1e9 + 7;
int dp[2][4009][5][5], inv[4009];
void add_mod(int &a, const long long &b) { a = (a + b) % MOD; }

class DoubleLive {
public:
	int findEV(int B, int H, int T) {
		int tot = B + H;
		memset(dp, 0, sizeof(dp));
		dp[0][B + H][1][1] = 1ll * B * H * 2 % MOD;
		dp[0][B + H][2][1] = 1ll * B * (B - 1) * H % MOD;
		dp[0][B + H][1][2] = 1ll * B * H * (H - 1) % MOD;
		inv[0] = inv[1] = 1;
		for (int i = 2; i <= tot; ++i)
			inv[i] = MOD - 1ll * inv[MOD % i] * (MOD / i) % MOD;
		int last, cur = 0;
		for (int i = 0; i < T; ++i) {
			last = cur;
			cur ^= 1;
			memset(dp[cur], 0, sizeof(dp[cur]));
			for (int j = 0; j <= tot; ++j) {
				int x = B * 2 + H - i - j;
				int y = j - x;
				if (x < 0 || y < 0)
					continue;
				for (int a = 0; a < 4; ++a)
					for (int b = 0; b < 4; ++b) {
						if (dp[last][j][a][b] == 0)
							continue;
						long long temp = 1ll * dp[last][j][a][b] * inv[j] % MOD;
						add_mod(dp[cur][j][a][b], temp * (x - a));
						if (a != 0)
							add_mod(dp[cur][j][a - 1][b + 1], temp * a);
						if (y != 0)
							add_mod(dp[cur][j - 1][a][b], temp * (y - b));
					}
			}
		}
		int ans = 0;
		for (int i = 0; i <= tot; ++i)
			for (int j = 0; j < 4;++j)
				for (int k = 0; k < 4; ++k)
					add_mod(ans, dp[cur][i][j][k]);
		return ans;
	}
};

// CUT begin
ifstream data("DoubleLive.sample");

string next_line() {
	string s;
	getline(data, s);
	return s;
}

template <typename T> void from_stream(T &t) {
	stringstream ss(next_line());
	ss >> t;
}

void from_stream(string &s) { s = next_line(); }

template <typename T> string to_string(T t) {
	stringstream s;
	s << t;
	return s.str();
}

string to_string(string t) { return "\"" + t + "\""; }

bool do_test(int B, int H, int T, int __expected) {
	time_t startClock = clock();
	DoubleLive *instance = new DoubleLive();
	int __result = instance->findEV(B, H, T);
	double elapsed = (double)(clock() - startClock) / CLOCKS_PER_SEC;
	delete instance;

	if (__result == __expected) {
		cout << "PASSED!"
				 << " (" << elapsed << " seconds)" << endl;
		return true;
	} else {
		cout << "FAILED!"
				 << " (" << elapsed << " seconds)" << endl;
		cout << "           Expected: " << to_string(__expected) << endl;
		cout << "           Received: " << to_string(__result) << endl;
		return false;
	}
}

int run_test(bool mainProcess, const set<int> &case_set, const string command) {
	int cases = 0, passed = 0;
	while (true) {
		if (next_line().find("--") != 0)
			break;
		int B;
		from_stream(B);
		int H;
		from_stream(H);
		int T;
		from_stream(T);
		next_line();
		int __answer;
		from_stream(__answer);

		cases++;
		if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
			continue;

		cout << "  Testcase #" << cases - 1 << " ... ";
		if (do_test(B, H, T, __answer)) {
			passed++;
		}
	}
	if (mainProcess) {
		cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
		int T = time(NULL) - 1516775369;
		double PT = T / 60.0, TT = 75.0;
		cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
		cout << "Score  : "
				 << 900 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT))
				 << " points" << endl;
	}
	return 0;
}

int main(int argc, char *argv[]) {
	cout.setf(ios::fixed, ios::floatfield);
	cout.precision(2);
	set<int> cases;
	bool mainProcess = true;
	for (int i = 1; i < argc; ++i) {
		if (string(argv[i]) == "-") {
			mainProcess = false;
		} else {
			cases.insert(atoi(argv[i]));
		}
	}
	if (mainProcess) {
		cout << "DoubleLive (900 Points)" << endl << endl;
	}
	return run_test(mainProcess, cases, argv[0]);
}
// CUT end
