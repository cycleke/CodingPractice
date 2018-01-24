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

class HeroVacation {
public:
	vector<int> getPermutation(vector<int> p) {
		n = p.size() + 1;
		size = new int[n];
		srt = new int[n];
		edges = new vector<int>[n];
		for (int i = 1; i < n; ++i) {
			edges[i].push_back(p[i - 1]);
			edges[p[i - 1]].push_back(i);
		}

		get_size(0, -1);
		int root = get_root(0, -1);
		for (int to : edges[root]) {
			dfs(to, root);
			c.push_back(a);
			a.clear();
		}
		int m = c.size();
		for (int i = 0; i < m; ++i)
			srt[i] = i;
		sort(srt, srt + m, [&](const int &a, const int &b){return c[a].size() > c[b].size();});
		for (int i = 0; i < m; ++i)
			for (int j : c[srt[i]])
				a.push_back(j);
		vector<int> ans;
		int half = n >> 1;
		for (int i = 0; i < half; ++i) {
			ans.push_back(a[i]);
			if (i + half < n - 1)
				ans.push_back(a[i + half]);
		}
		ans.push_back(root);
		reverse(ans.begin(), ans.end());
		return ans;
	}

private:
	int n, *size, *srt;
	vector<vector<int>> c;
	vector<int> *edges, a;

	void get_size(int x, int par) {
		size[x] = 1;
		for (int y : edges[x])
			if (y != par) {
				get_size(y, x);
				size[x] += size[y];
			}
	}
	int get_root(int x, int par) {
		for (int y : edges[x])
			if (y != par && size[y] * 2 >= n)
				return get_root(y, x);
		return x;
	}
	void dfs(int x, int par) {
		a.push_back(x);
		for (int y : edges[x])
			if (y != par)
				dfs(y, x);
	}

};

// CUT begin
ifstream data("HeroVacation.sample");

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

template <typename T> string to_string(vector<T> ts) {
	stringstream s;
	s << "[ ";
	for (int i = 0; i < ts.size(); ++i) {
		if (i > 0) s << ", ";
		s << to_string(ts[i]);
	}
	s << " ]";
	return s.str();
}

bool do_test(vector<int> p, vector<int> __expected) {
	time_t startClock = clock();
	HeroVacation *instance = new HeroVacation();
	vector<int> __result = instance->getPermutation(p);
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
		vector<int> p;
		from_stream(p);
		next_line();
		vector<int> __answer;
		from_stream(__answer);

		cases++;
		if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
			continue;

		cout << "  Testcase #" << cases - 1 << " ... ";
		if ( do_test(p, __answer)) {
			passed++;
		}
	}
	if (mainProcess) {
		cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
		int T = time(NULL) - 1516758240;
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
		cout << "HeroVacation (600 Points)" << endl << endl;
	}
	return run_test(mainProcess, cases, argv[0]);
}
// CUT end
