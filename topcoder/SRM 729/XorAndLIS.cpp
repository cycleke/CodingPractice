#include <cstdio>
#include <cmath>
#include <cstring>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <sstream>
#include <typeinfo>
#include <fstream>

using namespace std;

class XorAndLIS {
public:
	int maximalLength(vector<long long> x);
};

const long long INF = 0x3f3f3f3f3f3f3f3fll;
const int N = 105;
const int K = 60;
int n;
long long dp[N][N], a[K];

long long GetBiggest(long long x, int k) {
	for (; k >= 0; --k) {
		if (a[k] == -1)
			continue;
		if (((x >> k) & 1) == 0)
			x ^= a[k];
	}
	return x;
}

long long Rect(long long x, long long bound) {
	bool gr(false);
	for (int k = K - 1; k >= 0; --k) {
		if (gr) {
			if (a[k] == -1)
				continue;
			if (((x >> k) & 1) != 0)
				x ^=a[k];
			continue;
		}
		if (a[k] == -1) {
			if (((x >> k) & 1) == ((bound >> k) & 1))
				continue;
			if (((x >> k) & 1) != 0) {
				gr = true;
				continue;
			}
			return INF;
		}
		if (((bound >> k) & 1) != 0) {
			if (((x >> k) & 1) == 0)
				x ^= a[k];
			continue;
		}
		if (((x >> k) & 1) != 0)
			x ^= a[k];
		if (GetBiggest(x, k - 1) < bound) {
			x ^= a[k];
			gr = true;
		}
	}
	if (x < bound)
		exit(1);
	return x;
}

void AddToLiner(long long x) {
	for (int k = K - 1; k >= 0; --k) {
		if (((x >> k) & 1) == 0)
			continue;
		if (a[k] != -1)
			x ^= a[k];
		else {
			a[k] = x;
			break;
		}
	}
}

int XorAndLIS::maximalLength(vector<long long> x) {
	n = x.size();
	memset(a, -1, sizeof(a));
	memset(dp, 63, sizeof(dp));
	dp[0][0] = 0;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j <= i; ++j) {
			if (dp[i][j] == INF)
				continue;
			dp[i + 1][j] = min(dp[i + 1][j], dp[i][j]);
			long long temp = Rect(x[i], dp[i][j]);
			dp[i + 1][j + 1] = min(dp[i + 1][j + 1], temp + 1);
		}
		AddToLiner(x[i]);
	}
	int ans = n;
	while (dp[n][ans] == INF)
		--ans;
	return ans;
}

// CUT begin
ifstream data("XorAndLIS.sample");

string next_line() {
	string s;
	getline(data, s);
	return s;
}

template <typename T> void from_stream(T &t) {
	stringstream ss(next_line());
	ss >> t;
}

void from_stream(string &s) {
	s = next_line();
}

template <typename T> void from_stream(vector<T> &ts) {
	int len;
	from_stream(len);
	ts.clear();
	for (int i = 0; i < len; ++i) {
		T t;
		from_stream(t);
		ts.push_back(t);
	}
}

template <typename T>
string to_string(T t) {
	stringstream s;
	s << t;
	return s.str();
}

string to_string(string t) {
	return "\"" + t + "\"";
}

bool do_test(vector<long long> x, int __expected) {
	time_t startClock = clock();
	XorAndLIS *instance = new XorAndLIS();
	int __result = instance->maximalLength(x);
	double elapsed = (double)(clock() - startClock) / CLOCKS_PER_SEC;
	delete instance;

	if (__result == __expected) {
		cout << "PASSED!" << " (" << elapsed << " seconds)" << endl;
		return true;
	}
	else {
		cout << "FAILED!" << " (" << elapsed << " seconds)" << endl;
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
		vector<long long> x;
		from_stream(x);
		next_line();
		int __answer;
		from_stream(__answer);

		cases++;
		if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
			continue;

		cout << "  Testcase #" << cases - 1 << " ... ";
		if ( do_test(x, __answer)) {
			passed++;
		}
	}
	if (mainProcess) {
		cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
		int T = time(NULL) - 1518325390;
		double PT = T / 60.0, TT = 75.0;
		cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
		cout << "Score  : " << 800 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
	}
	return 0;
}

int main(int argc, char *argv[]) {
	cout.setf(ios::fixed, ios::floatfield);
	cout.precision(2);
	set<int> cases;
	bool mainProcess = true;
	for (int i = 1; i < argc; ++i) {
		if ( string(argv[i]) == "-") {
			mainProcess = false;
		} else {
			cases.insert(atoi(argv[i]));
		}
	}
	if (mainProcess) {
		cout << "XorAndLIS (800 Points)" << endl << endl;
	}
	return run_test(mainProcess, cases, argv[0]);
}
// CUT end
