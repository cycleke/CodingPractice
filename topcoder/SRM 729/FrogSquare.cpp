#include <bits/stdc++.h>

using namespace std;

class FrogSquare {
public:
	int minimalJumps(int n, int d, int sx, int sy, int tx, int ty) {
		if (sx == tx && sy == ty)
			return 0;
		int d2 = d * d;
		auto check = [&](const int &x, const int &y) {
			return x * x + y * y >= d2;
		};
		if (check(sx - tx, sy - ty))
			return 1;

		queue< pair<int, int> > q;
		q.emplace(sx, sy);
		memset(dis, 63, sizeof(dis));
		dis[sx][sy]= 0;

		auto getmin = [&](int &x, const int &y) {
			if (x > y) {
				x = y;
				return true;
			} else
				return false;
		};

		auto moveto = [&](const int &sx, const int &sy,
											const int &tx, const int &ty) {
			if (check(sx - tx, ty - sy) &&
					getmin(dis[tx][ty], dis[sx][sy] + 1))
				q.emplace(tx, ty);
		};

		while (!q.empty()) {
			int x, y;
			tie(x, y) = q.front();
			q.pop();
			if (check(x - tx, y - ty))
				return dis[x][y] + 1;
			for (int i = 0; i < n; ++i) {
				moveto(x, y, 0, i);
				moveto(x, y, i, 0);
				moveto(x, y, n - 1, i);
				moveto(x, y, i, n - 1);
			}
		}

		return -1;
	}

private:
	int dis[1007][1007];

};

// CUT begin
ifstream data("FrogSquare.sample");

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

template <typename T>
string to_string(T t) {
	stringstream s;
	s << t;
	return s.str();
}

string to_string(string t) {
	return "\"" + t + "\"";
}

bool do_test(int n, int d, int sx, int sy, int tx, int ty, int __expected) {
	time_t startClock = clock();
	FrogSquare *instance = new FrogSquare();
	int __result = instance->minimalJumps(n, d, sx, sy, tx, ty);
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
		int n;
		from_stream(n);
		int d;
		from_stream(d);
		int sx;
		from_stream(sx);
		int sy;
		from_stream(sy);
		int tx;
		from_stream(tx);
		int ty;
		from_stream(ty);
		next_line();
		int __answer;
		from_stream(__answer);

		cases++;
		if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
			continue;

		cout << "  Testcase #" << cases - 1 << " ... ";
		if ( do_test(n, d, sx, sy, tx, ty, __answer)) {
			passed++;
		}
	}
	if (mainProcess) {
		cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
		int T = time(NULL) - 1518320863;
		double PT = T / 60.0, TT = 75.0;
		cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
		cout << "Score  : " << 450 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
		cout << "FrogSquare (450 Points)" << endl << endl;
	}
	return run_test(mainProcess, cases, argv[0]);
}
// CUT end
