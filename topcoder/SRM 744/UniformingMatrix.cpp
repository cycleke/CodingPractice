#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <typeinfo>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<pii> vpii;
// Head File

class UniformingMatrix {
public:
  string isPossible(vector<string> M) {
    const string YES = "possible";
    const string NO = "impossible";

    int n = M.size();
    int m = M.back().size();
    if (m == n && n == 1)
      return M[0][0] == '1' ? YES : NO;
    vector<vi> a(n, vi(m));
    for (int v = 0; v < 2; v++) {

      for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
          a[i][j] = (M[i][j] == '0');
        }
      }

      for (int &x : a[0])
        x ^= v;

      int r = v, c = 0;
      for (int j = 0; j < m; j++) {
        if (!a[0][j])
          continue;
        c ^= 1;
        for (int i = 0; i < n; i++)
          a[i][j] ^= 1;
      }
      for (int i = 1; i < n; i++) {
        if (!a[i][0])
          continue;
        r ^= 1;
        for (int j = 0; j < m; j++)
          a[i][j] ^= 1;
      }

      if (r != c)
        continue;
      int flag = 0;
      for (vi &v : a)
        for (int &x : v)
          flag |= x;
      if (flag)
        continue;
      return YES;
    }

    return NO;
  }
};

// CUT begin
ifstream data("UniformingMatrix.sample");

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

bool do_test(vector<string> M, string __expected) {
  time_t startClock = clock();
  UniformingMatrix *instance = new UniformingMatrix();
  string __result = instance->isPossible(M);
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
    vector<string> M;
    from_stream(M);
    next_line();
    string __answer;
    from_stream(__answer);

    cases++;
    if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
      continue;

    cout << "  Testcase #" << cases - 1 << " ... ";
    if (do_test(M, __answer)) {
      passed++;
    }
  }
  if (mainProcess) {
    cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
    int T = time(NULL) - 1545445466;
    double PT = T / 60.0, TT = 75.0;
    cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
    cout << "Score  : "
         << 500 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT))
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
    cout << "UniformingMatrix (500 Points)" << endl << endl;
  }
  return run_test(mainProcess, cases, argv[0]);
}
// CUT end
