#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;

const int MAXN = 1e4 + 5;
const int MOD = 1e9 + 7;

int n, d[MAXN][3], g[MAXN][3];
int ans[3];
vector<pii> adj[MAXN];

inline void add(int &a, int b) {
  a += b;
  if (a >= MOD) a -= MOD;
}

void dfs(int u, int from) {
  d[u][0] = 1;
  d[u][1] = d[u][2] = 0;
  g[u][0] = g[u][1] = g[u][2] = 0;
  for (pii e : adj[u]) {
    int v = e.first, w = e.second;
    if (v == from) continue;
    dfs(v, u);
    for (int i = 0; i < 3; ++i)
      for (int j = 0; j < 3; ++j) {
        int k = (i + j + w) % 3;
        add(ans[k], 1LL * g[u][i] * d[v][j] % MOD);
        add(ans[k], 1LL * d[u][i] * g[v][j] % MOD);
        add(ans[k], 1LL * d[u][i] * d[v][j] * w % MOD);
      }
    for (int i = 0; i < 3; ++i) {
      add(d[u][(i + w) % 3], d[v][i]);
      add(g[u][(i + w) % 3], (g[v][i] + 1LL * w * d[v][i]) % MOD);
    }
  }
}
void solve() {
  for (int i = 0; i < n; ++i) adj[i].clear();
  memset(ans, 0, sizeof(ans));

  for (int i = 1, u, v, w; i < n; ++i) {
    cin >> u >> v >> w;
    adj[u].emplace_back(v, w);
    adj[v].emplace_back(u, w);
  }
  dfs(0, 0);
  for (int i = 0; i < 2; ++i) cout << ans[i] * 2LL % MOD << ' ';
  cout << ans[2] * 2LL % MOD << '\n';
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  while (cin >> n) solve();

  return 0;
}
