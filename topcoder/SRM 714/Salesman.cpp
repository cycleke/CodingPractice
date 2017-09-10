#include <cstdio>
#include <cmath>
#include <cstring>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <set>
#include <map>
#include <vector>
#include <sstream>
#include <typeinfo>
#include <fstream>

using namespace std;

typedef vector<int> vii;

int min_r[2525], pos[2525], delta[2525], n;
class Salesman {
protected:
	int prepar(const vii &pos, const vii &delta) const {
		map<int, int> M;
		n = pos.size();
		M[0] = 0;
		for (int i = 0; i < n; ++i) M[pos[i]] += delta[i];
		n = 0;
		for (pair<int, int> p : M) {
			::pos[n] = p.first;
			::delta[n] = p.second;
			++n;
		}
		return n;
	}
	int solve() const {
		int ans(0x3f3f3f3f), s(-1), first(-1), last(-1);
		for (int i = 0; i < n; ++i) {
			if (pos[i] == 0) s = i;
			if (delta[i] < 0) {
				if (first < 0) first = i;
				last = i;
			}
		}
		if (first < 0) return 0;
		for (int i = 0; i <= first; ++i) {
			min_r[i] = 0x3f3f3f3f;
			int sum = 0;
			for (int j = i; j < n; ++j) {
				sum += delta[j];
				if (j >= last && sum >= 0) {
					min_r[i] = j;
					break;
				}
			}
		}
		int aux = 0;
		for (int l = s; l >= 0; l--) {
			aux += delta[l];
			if (first >= l) {
				int cur_ans = 2 * (pos[s] - pos[l]);
				int cur_sum = aux;
				for (int f = s; f < n; f++) {
					if (min_r[l] < 0x3f3f3f3f) {
						int cand = cur_ans;
						cand += 2 * max(0, pos[min_r[l]] - pos[f]);
						ans = min(ans, cand);
					}
					if (f == n - 1) break;
					if (cur_sum < 0)
						cur_ans += 3 * (pos[f + 1] - pos[f]);
					else
						cur_ans += 1 * (pos[f + 1] - pos[f]);
					cur_sum += delta[f + 1];
				}
			}
		}
		return ans;
	}
public:
	int minMoves(vector<int> pos, vector<int> delta) {
		const int n = this->prepar(pos, delta);
		int temp1 = this->solve();
		for (int i = 0; i < n; ++i) ::pos[i] = -::pos[i];
		//reverse(pos.begin(), pos.end());
		//reverse(delta.begin(), pos.end());
		reverse(::pos, ::pos + n);
		reverse(::delta, ::delta + n);
		int temp2 = this->solve();
		return min(temp1, temp2);
	}
};

// CUT begin
ifstream data("Salesman.sample");

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

bool do_test(vector<int> pos, vector<int> delta, int __expected) {
	time_t startClock = clock();
	Salesman *instance = new Salesman();
	int __result = instance->minMoves(pos, delta);
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
		vector<int> pos;
		from_stream(pos);
		vector<int> delta;
		from_stream(delta);
		next_line();
		int __answer;
		from_stream(__answer);

		cases++;
		if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
			continue;

		cout << "  Testcase #" << cases - 1 << " ... ";
		if ( do_test(pos, delta, __answer)) {
			passed++;
		}
	}
	if (mainProcess) {
		cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
		int T = time(NULL) - 1494209928;
		double PT = T / 60.0, TT = 75.0;
		cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
		cout << "Score  : " << 1000 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
		cout << "Salesman (1000 Points)" << endl << endl;
	}
	return run_test(mainProcess, cases, argv[0]);
}
// CUT end
