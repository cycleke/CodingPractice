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

constexpr int MAXK = 103;
constexpr int MAXN = 1e5 + 3;
constexpr i64 INF = 0x3f3f3f3f3f3f3f3fLL;

int n, k, sz[MAXN];
vector<pii> adj[MAXN];
i64 dp[MAXN][MAXK];

void dfs(int u, int from) {
  if (adj[u].size() == 1) {
    sz[u] = 1;
    dp[u][0] = dp[u][1] = 0;
    return;
  }
  dp[u][0] = sz[u] = 0;
  memset(dp[u] + 1, 0x3f, k * sizeof(i64));
  for (auto &[v, w] : adj[u]) {
    if (v == from) continue;
    dfs(v, u);
    int l1 = min(k, sz[u]), l2 = min(k, sz[v]);
    debug(u, v, l1, l2, dp[u][l1], dp[v][l2]);
    for (int i = l1; i >= 0; --i) {
      if (dp[u][i] == INF) continue;
      for (int j = 0, s = i; j <= l2 && s <= k; ++j, ++s) {
        if (dp[v][j] == INF) continue;
        dp[u][s] = min(dp[u][s], dp[u][i] + dp[v][j] + 1ll * (k - j) * j * w);
      }
    }
    sz[u] += sz[v];
  }
}

void solve() {
  cin >> n >> k;
  for (int i = 1, u, v, w; i < n; ++i) {
    cin >> u >> v >> w;
    adj[u].emplace_back(v, w);
    adj[v].emplace_back(u, w);
  }

  if (n == 2) {
    cout << (k == 1 ? 0 : adj[1][0].second) << "\n";
    for (int i = 1; i <= n; ++i) adj[i].clear();
    return;
  }

  int rt = 1;
  while (adj[rt].size() == 1) ++rt;

  dfs(rt, rt);
  cout << dp[rt][k] << "\n";

  for (int i = 1; i <= n; ++i) adj[i].clear();
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
  cout << fixed << setprecision(3);

  int v_v = 0, o_o;
  for (cin >> o_o; v_v < o_o; solve()) cout << "Case #" << ++v_v << ": ";

  return 0;
}
