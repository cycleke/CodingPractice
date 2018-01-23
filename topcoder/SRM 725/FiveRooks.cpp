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

class FiveRooks {
public:
	int match[9];
	bool done[9];
	vector<int> edges[9];
	vector<int> find(vector<string> board) {
		for (int i = 0; i < 8; ++i)
			for (int j = 0; j < 8; ++j)
				if (board[i][j] == 'R')
					edges[i].push_back(j);

		if (matched() < 5) exit(-1);

		vector<int> res;
		for (int i = 0; i < 8; ++i) {
			if (match[i] == -1)
				continue;
			res.push_back(match[i]);
			res.push_back(i);
			if (res.size() == 10)
				return res;
		}
		return vector<int>{};
	}

	int matched() {
		memset(match, -1, sizeof(match));
		int ans = 0;
		for (int i = 0; i < 8; ++i) {
			memset(done, 0, sizeof(done));
			if (try_match(i))
				++ans;
		}
		return ans;
	}

	bool try_match(int x) {
		if (x == -1)
			return true;
		if (done[x])
			return false;
		done[x] = true;
		for (int to : edges[x]) {
			int pre = match[to];
			match[to] = x;
			if (try_match(pre))
				return true;
			match[to] = pre;
		}
		return false;
	}

};

// CUT begin
ifstream data("FiveRooks.sample");

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

bool do_test(vector<string> board, vector<int> __expected) {
	time_t startClock = clock();
	FiveRooks *instance = new FiveRooks();
	vector<int> __result = instance->find(board);
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
		vector<string> board;
		from_stream(board);
		next_line();
		vector<int> __answer;
		from_stream(__answer);

		cases++;
		if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
			continue;

		cout << "  Testcase #" << cases - 1 << " ... ";
		if ( do_test(board, __answer)) {
			passed++;
		}
	}
	if (mainProcess) {
		cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
		int T = time(NULL) - 1516681000;
		double PT = T / 60.0, TT = 75.0;
		cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
		cout << "Score  : " << 250 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
		cout << "FiveRooks (250 Points)" << endl << endl;
	}
	return run_test(mainProcess, cases, argv[0]);
}
// CUT end
