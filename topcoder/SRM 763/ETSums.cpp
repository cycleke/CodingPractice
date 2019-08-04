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

const int MOD = 1e9 + 7;
const int MAXN = 2e5 + 3;

int A[MAXN * 2], P[MAXN], C[MAXN], dep[MAXN], T[MAXN], dfs_clock, ans;
vi adj[MAXN];

int mod_pow(int a, int b = MOD - 2) {
  int r = 1;
  while (b) {
    if (b & 1) {
      r = 1LL * r * a % MOD;
    }
    a = 1LL * a * a % MOD;
    b >>= 1;
  }
  return r;
}

void dfs(int u) {
  T[u] = dfs_clock++;
  for (int v : adj[u]) {
    dfs(v);
  }
  if (dep[u] == 1) {
    ans = (ans + 1LL * (dfs_clock - T[u]) * C[u]) % MOD;
  } else if (dep[u] > 1) {
    int t = 1LL * (mod_pow(dep[u], dfs_clock) - mod_pow(dep[u], T[u]) + MOD) %
            MOD * mod_pow(dep[u] - 1) % MOD;
    ans = (ans + 1LL * C[u] * t) % MOD;
  }
}

class ETSums {
public:
  int findSumOfETSums(int N, vector<int> parent, vector<int> cost, int D,
                      int seed, int MX) {
    A[0] = seed;
    for (int i = 1; i < 2 * N; ++i) {
      A[i] = (A[i - 1] * 1103515245LL + 12345) % 2147483648;
    }

    for (size_t i = 0; i < parent.size(); ++i) {
      P[i] = parent[i];
    }
    for (int i = parent.size(); i < N; ++i) {
      P[i] = (A[i] % min(i, D)) + i - min(i, D);
    }

    for (size_t i = 0; i < cost.size(); ++i) {
      C[i] = cost[i];
    }
    for (int i = cost.size(); i < N; ++i) {
      C[i] = A[N + i] % MX;
    }

    dep[0] = 0;
    adj[0].clear();
    for (int i = 1; i < N; ++i) {
      adj[i].clear();
      adj[P[i]].push_back(i);
      dep[i] = dep[P[i]] + 1;
    }

    ans = 0;
    dfs_clock = 1;
    dfs(0);
    return ans;
  }
};

// CUT begin
ifstream data("ETSums.sample");

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

bool do_test(int N, vector<int> parent, vector<int> cost, int D, int seed,
             int MX, int __expected) {
  time_t startClock = clock();
  ETSums *instance = new ETSums();
  int __result = instance->findSumOfETSums(N, parent, cost, D, seed, MX);
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
    int N;
    from_stream(N);
    vector<int> parent;
    from_stream(parent);
    vector<int> cost;
    from_stream(cost);
    int D;
    from_stream(D);
    int seed;
    from_stream(seed);
    int MX;
    from_stream(MX);
    next_line();
    int __answer;
    from_stream(__answer);

    cases++;
    if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
      continue;

    cout << "  Testcase #" << cases - 1 << " ... ";
    if (do_test(N, parent, cost, D, seed, MX, __answer)) {
      passed++;
    }
  }
  if (mainProcess) {
    cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
    int T = time(NULL) - 1564839750;
    double PT = T / 60.0, TT = 75.0;
    cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
    cout << "Score  : "
         << 1000 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT))
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
    cout << "ETSums (1000 Points)" << endl << endl;
  }
  return run_test(mainProcess, cases, argv[0]);
}
// CUT end
