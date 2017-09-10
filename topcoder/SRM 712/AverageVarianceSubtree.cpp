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
#define mset(a, b) memset(a, b, sizeof(a))
typedef long double arr[55], arr2[55][55];

class AverageVarianceSubtree {
public:

	int n;
	vector<int> G[55];

	arr w;
	arr2 cnt, s, s2, s3;

	int dfs(int u, int from, int lim) {
		cnt[u][1] = 1;
		s[u][1] = w[u];
		s2[u][1] = s3[u][1] = w[u] * w[u];

		int C = 1;

		static arr _cnt, _s, _s2, _s3;
		arr &cnt = this->cnt[u], &s = this->s[u], &s2 = this->s2[u], &s3 = this->s3[u];

		for (int v : G[u]) if (v != from && v > lim) {
				int _C = dfs(v, u, lim);
				mset(_cnt, 0), mset(_s, 0),	mset(_s2, 0), mset(_s3, 0);

				const arr &cntv = this->cnt[v], &sv = this->s[v], &s2v = this->s2[v], &s3v = this->s3[v];

				for (int c = 1; c <= C + _C; ++c)
					for (int L = 1; L <= C; ++L) {
						int R = c - L;
						if (R < 0 || R > _C) continue;
						_cnt[c] += cnt[L] * cntv[R];
						_s[c] += cnt[L] * sv[R] + cntv[R] * s[L];
						_s2[c] += s2[L] * cntv[R] + 2.0 * s[L] * sv[R] + s2v[R] * cnt[L];
						_s3[c] += s3[L] * cntv[R] + s3v[R] * cnt[L];
					}

				C += _C;
				for (int i = 0; i <= C; ++i) {
					cnt[i] = _cnt[i];
					s[i] = _s[i];
					s2[i] = _s2[i];
					s3[i] = _s3[i];
				}
			}
		cnt[0] = 1;
		return C;
	}

	double average(vector<int> p, vector<int> weight) {
		n = weight.size();
		long double average = 0.0;
		for (int i = 0; i < n; ++i) {
			G[i].clear();
			w[i] = weight[i];
			average += w[i];
		}
		for (int i = 1; i < n; ++i) {
			G[p[i - 1]].push_back(i);
			G[i].push_back(p[i - 1]);
		}

		average /= n;

		for (int i = 0; i < n; ++i)
			w[i] -= average;

		mset(cnt, 0);
		mset(s, 0);
		mset(s2, 0);
		mset(s3, 0);

		long double xcnt = 0.0, sum = 0.0;
		for (int i = 0; i < n; ++i) {
			int end = dfs(i, i, i) + 1;

			for (int j = 1; j < end; ++j) {
				xcnt += this->cnt[i][j];
				sum += s3[i][j] / j - s2[i][j] / j / j;
			}

		}
		cout << endl;
		cout << "sum = " << sum << endl;
		cout << "xcnt = " << xcnt << endl;
		return (double)(sum / xcnt);

	}
};

// CUT begin
ifstream data("AverageVarianceSubtree.sample");

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

bool double_equal(const double &a, const double &b) { return b==b && a==a && fabs(b - a) <= 1e-9 * max(1.0, fabs(a) ); }

bool do_test(vector<int> p, vector<int> weight, double __expected) {
	time_t startClock = clock();
	AverageVarianceSubtree *instance = new AverageVarianceSubtree();
	double __result = instance->average(p, weight);
	double elapsed = (double)(clock() - startClock) / CLOCKS_PER_SEC;
	delete instance;

	if (double_equal(__expected, __result)) {
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
		vector<int> p;
		from_stream(p);
		vector<int> weight;
		from_stream(weight);
		next_line();
		double __answer;
		from_stream(__answer);

		cases++;
		if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
			continue;

		cout << "  Testcase #" << cases - 1 << " ... ";
		if ( do_test(p, weight, __answer)) {
			passed++;
		}
	}
	if (mainProcess) {
		cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
		int T = time(NULL) - 1494250589;
		double PT = T / 60.0, TT = 75.0;
		cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
		cout << "Score  : " << 600 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
		cout << "AverageVarianceSubtree (600 Points)" << endl << endl;
	}
	return run_test(mainProcess, cases, argv[0]);
}
// CUT end
