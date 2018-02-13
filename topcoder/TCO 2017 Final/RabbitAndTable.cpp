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

class RabbitAndTable {
public:
  int count(vector<int> x);
};

const int N = 2007;
const int MOD = 1000000007;

int f[N], g[N], cnt[N];
long long fac[N], inv[N], fac_inv[N];

int RabbitAndTable::count(vector<int> x) {
  const int n = x.size();
  auto FastPow = [&](int a, int b) {
    int r = 1;
    for (; b != 0; b >>= 1, a = 1ll * a * a % MOD)
      if ((b & 1) != 0)
        r = 1ll * a * r % MOD;
    return r;
  };

  fac[0] = inv[0] = fac_inv[0] = 1;
  fac[1] = inv[1] = fac_inv[1] = 1;
  for (int i = 2; i <= n; ++i) {
    fac[i] = fac[i - 1] * i % MOD;
    inv[i] = (MOD - MOD / i) * inv[MOD % i] % MOD;
    fac_inv[i] = fac_inv[i - 1] * inv[i] % MOD;
  }

  memset(f, 0, sizeof(f));
  memset(cnt, 0, sizeof(cnt));
  f[0] = 1;
  for (auto i : x)
    ++cnt[i];
  for (int i = n; i > 0; --i) {
    for (int j = 0; j <= n; ++j)
      if (j < cnt[i])
        g[j] = 0;
      else
        g[j] = f[j - cnt[i]];
    memset(f, 0, sizeof(f));
    for (int j = 0; j * i <= n; ++j) {
      long long comb = fac_inv[j] * FastPow(fac_inv[i], j) % MOD * fac[j * i] % MOD;
      for (int k = 0; k + j * i <= n; ++k) {
        f[k] = (f[k] + g[k + j * i] * comb) % MOD;
        comb = comb * (k + j * i + 1) % MOD * inv[k + 1] % MOD;
      }
    }
  }
  return f[0];
}

// CUT begin
ifstream data("RabbitAndTable.sample");

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

bool do_test(vector<int> x, int __expected) {
  time_t startClock = clock();
  RabbitAndTable *instance = new RabbitAndTable();
  int __result = instance->count(x);
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
    vector<int> x;
    from_stream(x);
    next_line();
    int __answer;
    from_stream(__answer);

    cases++;
    if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
      continue;

    cout << "  Testcase #" << cases - 1 << " ... ";
    if (do_test(x, __answer)) {
      passed++;
    }
  }
  if (mainProcess) {
    cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
    int T = time(NULL) - 1518402394;
    double PT = T / 60.0, TT = 75.0;
    cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
    cout << "Score  : "
         << 300 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT))
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
    cout << "RabbitAndTable (300 Points)" << endl << endl;
  }
  return run_test(mainProcess, cases, argv[0]);
}
// CUT end
