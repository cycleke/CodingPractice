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

constexpr int MAXN = 503;

tuple<int, int, int> edges[MAXN * MAXN];
int a[MAXN][MAXN], b[MAXN][MAXN], r[MAXN], c[MAXN], fa[MAXN];

int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
bool merge(int x, int y) {
  x = find(x), y = find(y);
  return x == y ? false : (fa[x] = y, true);
}

void solve() {
  int n, m = 0, total = 0;

  cin >> n;
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j) cin >> a[i][j];
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j) cin >> b[i][j];
  for (int i = 0; i < n; ++i) cin >> r[i];
  for (int i = 0; i < n; ++i) cin >> c[i];

  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j) {
      if (~a[i][j]) continue;
      total += b[i][j];
      edges[m++] = make_tuple(b[i][j], i, j + n);
    }

  iota(fa, fa + n * 2, 0);

  sort(edges, edges + m, greater<>());
  for (int i = 0, u, v, w; i < m; ++i) {
    tie(w, u, v) = edges[i];
    if (merge(u, v)) total -= w;
  }

  cout << total << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
  cout << fixed << setprecision(10);

  int o_o, v_v = 1;
  for (cin >> o_o; v_v <= o_o; ++v_v) {
    cout << "Case #" << v_v << ": ";
    solve();
  }
  return 0;
}
