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

class IncreasingSequences {
public:
  int count(vector<int> L, vector<int> R);
};

const long long MOD = 998244353ll;

long long a[616][313], b[616][313];

long long inv(long long x) {
  long long ret = 1;
  int n = MOD - 2;
  while (n != 0) {
    if ((n & 1) != 0) {
      ret = ret * x % MOD;
    }
    x = x * x % MOD;
    n >>= 1;
  }
  return ret;
}

int IncreasingSequences::count(vector<int> L, vector<int> R) {
  L.push_back(int(1e9 + 7));
  R.push_back(int(1e9 + 7));

  const int n = L.size();
  for (int i = 0; i < n; ++i) {
    L[i] += n - i;
    R[i] += n - i;
  }

  vector<int> c{0, 0x7fffffff};
  for (int i = 0; i < n; ++i) {
    c.push_back(L[i]);
    c.push_back(R[i] + 1);
  }
  sort(c.begin(), c.end());
  c.erase(unique(c.begin(), c.end()), c.end());
  const int m = c.size();
  memset(a, 0, sizeof(a));
  for (int i = 0; i < m - 1; ++i)
    if (L[0] <= c[i] && c[i + 1] <= R[0] + 1)
      a[i][0] = 1;

  for (int i = 0; i < m - 1; ++i) {
    long long p = c[i + 1] - c[i] - 1;
    b[i][0] = 1;
    for (int j = 1; j < 301; ++j) {
      ++p;
      b[i][j] = b[i][j - 1] * p % MOD * inv(j) % MOD;
    }
  }

  long long ret = 0;
  for (int i = 1; i < n; ++i) {
    long long s = 0;
    for (int j = 0; j < m - 1; ++j) {
      if (L[i] <= c[j] && c[j + 1] <= R[i] + 1)
        a[j][i] = s;
      if (L[i - 1] <= c[j] && c[j + 1] <= R[i - 1] + 1) {
        for (int k = i - 1; k >= 0; --k) {
          if (L[k] > c[j] || c[j + 1] > R[k] + 1)
            break;
          if (a[j][k] != 0)
            s = (s + a[j][k] * b[j][i - k]) % MOD;
        }
      }
      ret = s;
    }
  }
  return int(ret);
}

// CUT begin
ifstream data("IncreasingSequences.sample");

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

bool do_test(vector<int> L, vector<int> R, int __expected) {
  time_t startClock = clock();
  IncreasingSequences *instance = new IncreasingSequences();
  int __result = instance->count(L, R);
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
    vector<int> L;
    from_stream(L);
    vector<int> R;
    from_stream(R);
    next_line();
    int __answer;
    from_stream(__answer);

    cases++;
    if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
      continue;

    cout << "  Testcase #" << cases - 1 << " ... ";
    if (do_test(L, R, __answer)) {
      passed++;
    }
  }
  if (mainProcess) {
    cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
    int T = time(NULL) - 1517717938;
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
    cout << "IncreasingSequences (500 Points)" << endl << endl;
  }
  return run_test(mainProcess, cases, argv[0]);
}
// CUT end
