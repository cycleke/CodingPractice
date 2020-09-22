#pragma GCC optimize(2)
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2e5 + 5;

vector<int> adj[MAXN];
int sz[MAXN], fa[MAXN], ans[MAXN], ans2[MAXN];

void dfs(int u, int from) {
  sz[u] = 1;
  queue<int> q;
  for (int v : adj[u]) {
    if (v == from) continue;
    fa[v] = u;
    dfs(v, u);
    q.push(ans[v]);
    sz[u] += sz[v];
  }

  int &point = ans[u] = u, val = sz[u];
  while (!q.empty()) {
    int v = q.front();
    q.pop();
    while (sz[u] > sz[v] << 1) v = fa[v];
    if (v == u) continue;
    int val_ = max(sz[v], sz[u] - sz[v]);
    if (val_ < val) point = v, val = val_;
  }
  if (sz[u] == sz[point] << 1) ans2[u] = fa[point];
}

int main(int argc, char *argv[]) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);

  int n;
  cin >> n;
  for (int u, v, i = 1; i < n; ++i) {
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  dfs(1, 1);
  for (int i = 1; i <= n; ++i) {
    if (ans2[i]) {
      cout << min(ans[i], ans2[i]) << " " << max(ans[i], ans2[i]) << "\n";
    } else {
      cout << ans[i] << "\n";
    }
  }

  return 0;
}
