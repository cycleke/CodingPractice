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

class SumProduct {
public:
  int findSum(vector<int> amount, int blank1, int blank2);
};

const int MOD = (int) (1e9 + 7);

inline int add(int a, int b) {
  a += b;
  if (a >= MOD) a-= MOD;
  return a;
}

inline int mul(int a, int b) {
  return (long long) a * b % MOD;
}

const int N = (int) (1e6 + 7);

int f[2345][2345];
int fac[N], inv_fac[N], inv[N], p[202];

int SumProduct::findSum(vector < int > amount, int blank1, int blank2) {
  //preprogress
  fac[0] = inv_fac[0] = inv[0] = 1;
  fac[1] = inv_fac[1] = inv[1] = 1;
  for (int i = 2; i < N; ++i) {
    fac[i] = mul(fac[i - 1], i);
    inv[i] = MOD - (1ll * MOD / i * inv[MOD % i]) % MOD;
    inv_fac[i] = mul(inv_fac[i - 1], inv[i]);
  }
  p[0] = 1;
  for (int i = 1; i < blank1 + blank2; ++i)
    p[i] = mul(p[i - 1], 10);
  //debug
  //for (int i = 0; i < N; ++i) printf("%d ", inv_fac[i]);
  //puts("");
  //for (int i = 1; i < blank1 + blank2; ++i) printf("%d ", p[i]);
  //puts("");
  //
  int c = 0;
  for (int i = 0; i < blank1; ++i)
    for (int j = 0; j < blank2; ++j)
      c = add(c, p[i + j]);
  int ans = 0;
  for (int x = 0; x < 10; ++x) {
    if (amount[x] == 0) continue;
    --amount[x];
    for (int y = 0; y < 10; ++y) {
      if (amount[y] == 0) continue;
      --amount[y];
      int need = blank1 + blank2 - 2;
      for (int i = 0; i <= 10; ++i)
        for (int j = 0; j <= need; ++j)
          f[i][j] = 0;
      f[0][0] = 1;
      for (int i = 0; i < 10; ++i)
        for (int j = 0; j <= need; ++j) {
          int temp = f[i][j];
          if (temp == 0) continue;
          for (int k = 0; k <= amount[i] && j + k <= need; ++k)
            f[i + 1][j + k] = add(f[i + 1][j + k], mul(temp, inv_fac[k]));
        }
      int temp = mul(f[10][need], fac[need]);
      ans = add(ans, mul(temp, mul(x * y, c)));
      ++amount[y];
    }
    ++amount[x];
  }
  return ans;
}


// CUT begin
ifstream data("SumProduct.sample");

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

bool do_test(vector<int> amount, int blank1, int blank2, int __expected) {
  time_t startClock = clock();
  SumProduct *instance = new SumProduct();
  int __result = instance->findSum(amount, blank1, blank2);
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
    vector<int> amount;
    from_stream(amount);
    int blank1;
    from_stream(blank1);
    int blank2;
    from_stream(blank2);
    next_line();
    int __answer;
    from_stream(__answer);

    cases++;
    if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
      continue;

    cout << "  Testcase #" << cases - 1 << " ... ";
    if ( do_test(amount, blank1, blank2, __answer)) {
      passed++;
    }
  }
  if (mainProcess) {
    cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
    int T = time(NULL) - 1505619301;
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
    cout << "SumProduct (250 Points)" << endl << endl;
  }
  return run_test(mainProcess, cases, argv[0]);
}
// CUT end
