#include <bits/stdc++.h>
using namespace std;

const int MAXN = 5e3 + 5;

vector<int> adj[MAXN];
int n, f[MAXN][MAXN], g[MAXN][MAXN];

void cmin(int &a, const int &b) {
  if (a > b) a = b;
}

void dfs(int u, int from) {
  for (int v : adj[u]) {
    if (v == from) continue;
    dfs(v, u);
    for (int i = 1; i <= n; ++i) g[u][i] += g[v][i - 1];
  }

  f[u][n] = g[u][0] = n;
  for (int i = n - 1; ~i; --i) {
    if (i) {
      f[u][i] = min(f[u][i + 1], i + g[u][i + 1]);
    } else {
      f[u][i] = min(f[u][i + 1], 1 + g[u][2]);
    }

    for (int v : adj[u]) {
      if (v == from) continue;
      cmin(f[u][i], f[v][i + 1] - g[v][i] + g[u][i + 1]);
    }
  }

  g[u][0] = f[u][0];
  for (int i = 1; i <= n; ++i) cmin(g[u][i], g[u][i - 1]);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n;
  for (int i = 1, u, v; i < n; ++i) {
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  dfs(1, 1);
  int ans = n;
  for (int i = 0; i <= n; ++i) cmin(ans, f[1][i]);
  cout << ans << '\n';
  return 0;
}
