#include <bits/stdc++.h>
using namespace std;

const int MAXN = 505;

bool g[MAXN][MAXN];
int n, m, deg[MAXN];

bool gao(int lim) {
  static int d[MAXN];
  static bool _g[MAXN][MAXN];
  static queue<pair<int, int>> q;

  while (!q.empty()) q.pop();
  memcpy(d, deg, sizeof(int) * (n + 1));
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= n; ++j) _g[i][j] = g[i][j];

  for (int i = 1; i <= n; ++i)
    for (int j = 1; j < i; ++j) {
      if (!_g[i][j] && d[i] + d[j] >= lim) {
        _g[i][j] = _g[j][i] = true;
        q.emplace(i, j);
      }
    }

  while (!q.empty()) {
    int u = q.front().first;
    int v = q.front().second;
    q.pop();
    ++d[u], ++d[v];
    for (int i = 1; i <= n; ++i) {
      if (i == u || _g[u][i]) continue;
      if (d[u] + d[i] >= lim) {
        _g[u][i] = _g[i][u] = true;
        q.emplace(u, i);
      }
    }
    for (int i = 1; i <= n; ++i) {
      if (i == v || _g[v][i]) continue;
      if (d[v] + d[i] >= lim) {
        _g[v][i] = _g[i][v] = true;
        q.emplace(v, i);
      }
    }
  }

  for (int i = 1; i <= n; ++i)
    if (d[i] < n - 1) return false;
  return true;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> m;
  for (int u, v; m; --m) {
    cin >> u >> v;
    ++deg[u], ++deg[v];
    g[u][v] = g[v][u] = true;
  }

  int l = 0, r = 2 * n, ans = 0;
  while (l <= r) {
    int mid = (l + r) >> 1;
    if (gao(mid)) {
      ans = mid;
      l = mid + 1;
    } else {
      r = mid - 1;
    }
  }
  cout << ans << '\n';
  return 0;
}
