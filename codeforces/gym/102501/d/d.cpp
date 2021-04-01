#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;

void debug_out() { cerr << endl; }
template <typename T> string to_string(const vector<T> &vec) {
  string res = "[";
  bool first = true;
  for (const T &x : vec) {
    if (first) {
      first = false;
    } else {
      res += ",";
    }
    res += to_string(x);
  }
  return res + "]";
}
template <typename Head, typename... Tail> void debug_out(Head H, Tail... T) {
  cerr << " " << to_string(H);
  debug_out(T...);
}
#ifdef ONLINE_JUDGE
#define debug(...)
#else
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#endif

constexpr int SIMPLE = 26;
constexpr int MAXN = 2e5 + 3;
mt19937 rnd(chrono::high_resolution_clock::now().time_since_epoch().count());

map<pii, int> idx;
int lhs[MAXN], rhs[MAXN], cnt;

bool eval(int *stk, int &top, const string &ops) {
  for (char op : ops) {
    switch (op) {
    case 'C': {
      stk[top] = stk[top - 1];
      ++top;
      break;
    }
    case 'D': {
      --top;
      break;
    }
    case 'L': {
      if (stk[top - 1] < SIMPLE) return false;
      stk[top - 1] = lhs[stk[top - 1]];
      break;
    }
    case 'R': {
      if (stk[top - 1] < SIMPLE) return false;
      stk[top - 1] = rhs[stk[top - 1]];
      break;
    }
    case 'P': {
      pii p = make_pair(stk[top - 1], stk[top - 2]);
      --top;
      auto it = idx.find(p);
      if (it != idx.end()) {
        stk[top - 1] = it->second;
      } else {
        lhs[cnt] = stk[top];
        rhs[cnt] = stk[top - 1];
        stk[top - 1] = idx[p] = cnt++;
      }
      break;
    }
    case 'U': {
      if (stk[top - 1] < SIMPLE) return false;
      int id = stk[top - 1];
      stk[top] = lhs[id];
      stk[top - 1] = rhs[id];
      ++top;
      break;
    }
    case 'S': {
      swap(stk[top - 1], stk[top - 2]);
      break;
    }
    default: assert(0);
    }
  }
  return true;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
  cout << fixed << setprecision(10);

  uniform_int_distribution<> gen(0, SIMPLE - 1);

  string s1, s2;
  cin >> s1 >> s2;
  for (int step = 100; step; --step) {
    int n = max(s1.length(), s2.length()) * 2 + 3, m = n;
    static int a[MAXN], b[MAXN];
    cnt = SIMPLE, idx.clear();
    for (int i = 0; i < n; ++i) a[i] = b[i] = gen(rnd);
    bool r1 = eval(a, n, s1), r2 = eval(b, m, s2);
    debug(r1, r2, n, m);
    if (r1 ^ r2) {
      cout << "False\n";
      return 0;
    }
    if (r1) {
      if (n != m) {
        cout << "False\n";
        return 0;
      }
      for (int i = 0; i < n; ++i)
        if (a[i] != b[i]) {
          cout << "False\n";
          return 0;
        }
    }
  }
  cout << "True\n";
  return 0;
}
