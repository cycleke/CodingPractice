#include <bits/stdc++.h>
using namespace std;

using i64 = long long;
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

constexpr int kMaxN = 15;
constexpr int kMaxS = 1 << kMaxN;
// mt19937 rnd(chrono::high_resolution_clock::now().time_since_epoch().count());

i64 sum[kMaxS], f[kMaxS];
int a[kMaxN], l[kMaxN], r[kMaxN], g[kMaxS];

void solve() {
  int n, m, k;
  cin >> n >> m >> k;

  int s_num = 1 << n;
  memset(f, 0, s_num * sizeof(f[0]));
  memset(g, 0, s_num * sizeof(g[0]));
  for (int i = 0; i < n; ++i) {
    cin >> l[i] >> r[i] >> a[i];

    f[1 << i] = 1;
    sum[1 << i] = a[i];
  }

  for (int i = 0, u, v; i < m; ++i) {
    cin >> u >> v;
    g[1 << u] |= 1 << v;
    g[1 << v] |= 1 << u;
  }

  for (int s = 1; s < s_num; ++s) {
    g[s] = g[s & (s - 1)] | g[s & -s];
    sum[s] = sum[s & (s - 1)] + sum[s & -s];
  }

  for (int s = 1; s < s_num; ++s) {
    if (sum[s] >= k) {
      continue;
    }
    debug(s, g[s]);

    for (int v = 0; v < n; ++v) {
      if ((s >> v & 1) || (~g[s] >> v & 1) || sum[s] < l[v] || sum[s] > r[v]) {
        continue;
      }

      debug(v, s | (1 << v));
      f[s | (1 << v)] += f[s];
    }
  }

  i64 ans = 0;
  for (int s = 1; s < s_num; ++s) {
    debug(s, f[s]);
    if (sum[s] == k) {
      ans += f[s];
    }
  }

  cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
  cout << fixed << setprecision(10);

  int o_o, v_v = 0;
  for (cin >> o_o; o_o; --o_o) {
    cout << "Case #" << ++v_v << ": ";
    solve();
  }
  return 0;
}
