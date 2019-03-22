#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<pii> vpii;
// Head File

const int MAXN = 1000;

class MaxCutFree {
public:
  vi adj[MAXN];
  int idx[MAXN], dfs_clock;
  int f[MAXN], g[MAXN];
  set<pii> bridges;

  int solve(int n, vector<int> a, vector<int> b) {
    int m = int(a.size());
    for (int i = 0; i < m; ++i) {
      adj[a[i]].push_back(b[i]);
      adj[b[i]].push_back(a[i]);
    }

    dfs_clock = 0;
    fill(idx, idx + n, -1);
    bridges.clear();
    for (int i = 0; i < n; ++i) {
      if (~idx[i]) {
        continue;
      }
      tarjan(i, -1);
    }

    for (int i = 0; i < n; ++i) {
      adj[i].clear();
      f[i] = g[i] = 0;
    }

    for (auto &edge : bridges) {
      adj[edge.first].push_back(edge.second);
      adj[edge.second].push_back(edge.first);
    }

    int res = 0;
    for (int i = 0; i < n; ++i) {
      if (f[i]) {
        continue;
      }
      dfs(i);
      res += max(f[i], g[i]);
    }
    return res;
  }

  int tarjan(int u, int from) {
    int low;
    idx[u] = dfs_clock;
    low = dfs_clock;
    ++dfs_clock;
    for (auto &v : adj[u]) {
      if (v == from) {
        continue;
      }
      if (idx[v] == -1) {
        int i_low = tarjan(v, u);
        low = min(low, i_low);
        if (i_low > idx[u]) {
          bridges.insert(make_pair(min(u, v), max(u, v)));
        }
      } else {
        low = min(low, idx[v]);
      }
    }

    return low;
  }

  void dfs(int u) {
    f[u] = 1; // choose u
    g[u] = 0; // don't choose u
    for (int &v : adj[u]) {
      if (f[v]) {
        continue;
      }
      dfs(v);
      f[u] += g[v];
      g[u] += max(f[v], g[v]);
    }
  }
};

// CUT begin
ifstream data("MaxCutFree.sample");

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

bool do_test(int n, vector<int> a, vector<int> b, int __expected) {
  time_t startClock = clock();
  MaxCutFree *instance = new MaxCutFree();
  int __result = instance->solve(n, a, b);
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
    int n;
    from_stream(n);
    vector<int> a;
    from_stream(a);
    vector<int> b;
    from_stream(b);
    next_line();
    int __answer;
    from_stream(__answer);

    cases++;
    if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
      continue;

    cout << "  Testcase #" << cases - 1 << " ... ";
    if (do_test(n, a, b, __answer)) {
      passed++;
    }
  }
  if (mainProcess) {
    cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
    int T = time(NULL) - 1553179526;
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
    cout << "MaxCutFree (300 Points)" << endl << endl;
  }
  return run_test(mainProcess, cases, argv[0]);
}
// CUT end
