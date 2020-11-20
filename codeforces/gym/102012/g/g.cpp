#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;
const int MAXN = 3e5 + 5;

int n, m, k;
vector<int> adj[MAXN];

int size[MAXN], dep[MAXN], son[MAXN], fa[MAXN], top[MAXN];

void dfs1(int u) {
  son[u] = 0;
  size[u] = 1;
  for (int v : adj[u]) {
    if (v == fa[u]) continue;
    fa[v] = u;
    dep[v] = dep[u] + 1;
    dfs1(v);
    if (size[son[u]] < size[v]) son[u] = v;
    size[u] += size[v];
  }
}

void dfs2(int u, int anc) {
  top[u] = anc;
  if (son[u]) {
    dfs2(son[u], anc);
    for (int v : adj[u])
      if (v != fa[u] && v != son[u]) dfs2(v, v);
  }
}

int lca(int u, int v) {
  while (top[u] ^ top[v]) {
    if (dep[top[u]] < dep[top[v]]) swap(u, v);
    u = fa[top[u]];
  }
  return dep[u] < dep[v] ? u : v;
}

int c0[MAXN], c1[MAXN];

void dfs(int u) {
  for (int v : adj[u])
    if (v != fa[u]) dfs(v), c0[u] += c0[v];
}

int f[MAXN], inv[MAXN], inv_f[MAXN];

inline int C(int n, int m) {
  if (n < m) return 0;
  return 1LL * f[n] * inv_f[m] % MOD * inv_f[n - m] % MOD;
}

void solve() {
  cin >> n >> m >> k;
  for (int i = 1; i <= n; ++i) adj[i].clear(), c0[i] = c1[i] = 0, fa[i] = 0;
  for (int i = 1, u, v; i < n; ++i) {
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  dfs1(1);
  dfs2(1, 1);
  for (int u, v, g; m; --m) {
    cin >> u >> v;
    g = lca(u, v);
    ++c0[u], ++c0[v];
    ++c1[g], --c0[g], --c0[fa[g]];
  }
  dfs(1);

  int ans = 0;
  for (int i = 1; i <= n; ++i)
    ans = (ans + 1LL * (C(c0[i], k) - C(c0[i] - c1[i], k) + MOD)) % MOD;
  cout << ans << '\n';
}

int main() {
  // freopen("in0.txt", "r", stdin);
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  f[0] = inv_f[0] = 1;
  f[1] = inv[1] = inv_f[1] = 1;
  for (int i = 2; i < MAXN; ++i) {
    f[i] = 1LL * f[i - 1] * i % MOD;
    inv[i] = 1LL * (MOD - MOD / i) * inv[MOD % i] % MOD;
    inv_f[i] = 1LL * inv_f[i - 1] * inv[i] % MOD;
  }
  int o_o;
  for (cin >> o_o; o_o; --o_o) solve();

  return 0;
}
