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
#include <unordered_map>
#include <vector>

using namespace std;

class Halving {
public:
  int minSteps(vector<int> a) {
    const int n = a.size();
    int o = -1;
    unordered_map<int, int> divided[n];
    for (int i = 0; i < n; ++i) {
      dfs(divided[i], a[i], 0);
      if (o < 0 || divided[i].size() < divided[o].size())
        o = i;
    }
    int ans = 0x0f7f7f7f;
    for (auto it : divided[o]) {
      int cnt = 0;
      for (int i = 0; i < n; ++i) {
        int c = divided[i].count(it.first);
        if (c == 0) {
          cnt = 0x0f7f7f7f;
        } else {
          cnt += divided[i][it.first];
        }
      }
      if (cnt < ans) {
        ans = cnt;
      }
    }
    return ans;
  }

private:
  void dfs(unordered_map<int, int> &a, int length, int step) {
    if (a.find(length) != a.end())
      return;
    a[length] = step;
    if ((length & 1) == 0) {
      dfs(a, length >> 1, step + 1);
    } else {
      dfs(a, length >> 1, step + 1);
      dfs(a, (length + 1) >> 1, step + 1);
    }
  }
};

// CUT begin
ifstream data("Halving.sample");

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

template <typename T> string to_string(T t) {
  stringstream s;
  s << t;
  return s.str();
}

string to_string(string t) { return "\"" + t + "\""; }

bool do_test(vector<int> a, int __expected) {
  time_t startClock = clock();
  Halving *instance = new Halving();
  int __result = instance->minSteps(a);
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
    vector<int> a;
    from_stream(a);
    next_line();
    int __answer;
    from_stream(__answer);

    cases++;
    if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
      continue;

    cout << "  Testcase #" << cases - 1 << " ... ";
    if (do_test(a, __answer)) {
      passed++;
    }
  }
  if (mainProcess) {
    cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
    int T = time(NULL) - 1517713461;
    double PT = T / 60.0, TT = 75.0;
    cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
    cout << "Score  : "
         << 250 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT))
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
    cout << "Halving (250 Points)" << endl << endl;
  }
  return run_test(mainProcess, cases, argv[0]);
}
// CUT end
