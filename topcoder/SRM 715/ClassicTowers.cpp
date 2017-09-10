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

#define rep(i, n) for (i = 0; i <= n; ++i)

class ClassicTowers {

public:
	char res[51];
	int a[3], d[3][51][51][51];

	string findTowers(long long k, vector<int> count) {
		const int n0 = count[0];
		const int n1 = count[1];
		const int n2 = count[2];
		const int n = n0 + n1 + n2;
		if (k >= 1ll << (n - 1))
			return "";

		memset(d, 0, sizeof (d));
		d[0][1][0][0] = (n0 > 0) ? -1 : 0;
		d[1][0][1][0] = (n1 > 0) ? -1 : 0;
		d[2][0][0][1] = (n2 > 0) ? -1 : 0;

		rep (a[0], n0) rep (a[1], n1) rep (a[2], n2)
			for (int i = 0; i < 3; ++i) {
				if (d[i][a[0]][a[1]][a[2]] == 0)
					continue;
				int bit = n - a[0] - a[1] - a[2] - 1;
				if (bit < 0)
					continue;
				if (k >> bit & 1) {
					int x = (i + 1) % 3, y = (i + 2) % 3;
					++a[x];
					if (a[x] <= count[x])
						d[y][a[0]][a[1]][a[2]] = i + 1;
					--a[x];
					++a[y];
					if (a[y] <= count[y])
						d[x][a[0]][a[1]][a[2]] = i + 1;
					--a[y];
				} else {
					++a[i];
					if (a[i] <= count[i])
						d[i][a[0]][a[1]][a[2]] = i + 1;
					--a[i];
				}
			}
		for (int i = 0; i < 3; ++i)
			if (d[i][n0][n1][n2] != 0) {
				for (int j = 0; j < 3; ++j)
					a[j] = count[j];
				for (int _i = 0; _i < n - 1; ++_i) {
					const int _d = d[i][a[0]][a[1]][a[2]] - 1;
					if (_d == i) {
						res[_i] = 'A' + i;
						--a[i];
					} else {
						res[_i] = 'A' + 3 - i - _d;
						--a[3 - i - _d];
						i = _d;
					}
				}
				res[n] = 0;
				res[n - 1] = 'A' + i;
				return string(res);
			}
		return "";
	}
};

// CUT begin
ifstream data("ClassicTowers.sample");

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

bool do_test(long long k, vector<int> count, string __expected) {
	time_t startClock = clock();
	ClassicTowers *instance = new ClassicTowers();
	string __result = instance->findTowers(k, count);
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
		long long k;
		from_stream(k);
		vector<int> count;
		from_stream(count);
		next_line();
		string __answer;
		from_stream(__answer);

		cases++;
		if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
			continue;

		cout << "  Testcase #" << cases - 1 << " ... ";
		if ( do_test(k, count, __answer)) {
			passed++;
		}
	}
	if (mainProcess) {
		cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
		int T = time(NULL) - 1501233031;
		double PT = T / 60.0, TT = 75.0;
		cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
		cout << "Score  : " << 500 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
		cout << "ClassicTowers (500 Points)" << endl << endl;
	}
	return run_test(mainProcess, cases, argv[0]);
}
// CUT end
