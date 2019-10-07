#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 5;

int n, m, dfn[MAXN], dfs_c;
vector<int> adj[MAXN];
vector<tuple<int, int, int>> ans;

bool dfs(int u, int from) {
  int son = 0, anc = 0;
  dfn[u] = ++dfs_c;
  for (int v : adj[u]) {
    if (v == from) continue;
    if (dfn[v]) {
      if (dfn[v] > dfn[u]) continue;
      if (anc) {
        ans.emplace_back(anc, u, v);
        anc = 0;
      } else {
        anc = v;
      }
    } else {
      if (dfs(v, u)) continue;
      if (son) {
        ans.emplace_back(son, u, v);
        son = 0;
      } else {
        son = v;
      }
    }
  }

  if (son && anc) {
    ans.emplace_back(son, u, anc);
    return false;
  }
  if (!from) return false;
  if (son) {
    ans.emplace_back(son, u, from);
    return true;
  }
  if (anc) {
    ans.emplace_back(anc, u, from);
    return true;
  }
  return false;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> m;
  for (int u, v; m; --m) {
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  dfs_c = 0;
  for (int i = 1; i <= n; ++i)
    if (!dfn[i]) dfs(i, 0);

  cout << ans.size() << '\n';
  int u, v, w;
  for (auto t : ans) {
    tie(u, v, w) = t;
    cout << u << ' ' << v << ' ' << w << '\n';
  }
  return 0;
}
