#include <bits/stdc++.h>
using namespace std;

const int MAXN = 85;

int n, r, h, m, d[MAXN];
vector<int> adj[MAXN];

bool dfs(int u, int from) {
  d[u] = 1;
  bool res = u == r;
  for (int v : adj[u]) {
    if (v == from) continue;
    res |= dfs(v, u);
    d[u] = max(d[u], d[v] + 1);
  }
  return res;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> r >> h >> m;
  for (int i = 1, u, v; i < n; ++i) {
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  int ans = INT_MAX;
  for (int i = 1; i <= n; ++i) {
    if (i == h || i == m) {
      for (int v : adj[i]) {
        if (dfs(v, i)) {
          ans = min(ans, d[v]);
          break;
        }
      }
    } else {
      dfs(i, i);
      ans = min(ans, d[i]);
    }
  }
  cout << ans << '\n';
  return 0;
}
