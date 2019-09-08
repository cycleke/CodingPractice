#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;
const int MAXN = 1e6 + 5;

vector<int> adj[MAXN];
int max_dep, inv[MAXN], dep[MAXN], son[MAXN];

void dfs(int u, int from) {
  max_dep = max(max_dep, dep[u]);
  for (int v : adj[u]) {
    if (v == from) continue;
    ++son[u];
    dep[v] = dep[u] + 1;
    dfs(v, u);
  }
}

int gao(int u) {
  if (son[u] == 0) return dep[u] == max_dep;
  int p = 0;
  for (int v : adj[u])
    if (dep[v] == dep[u] + 1) p = (p + gao(v)) % MOD;
  p = 1LL * p * inv[son[u]] % MOD;
  p = (1 + MOD - p) % MOD;
  int res = 1;
  for (int i = 0; i < son[u]; ++i) res = 1LL * res * p % MOD;
  // cerr << u << ' ' << (1 + MOD - res) % MOD << '\n';
  return (1 + MOD - res) % MOD;
}

int main(int argc, char *argv[]) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;
  for (int i = 1, u, v; i < n; ++i) {
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  inv[1] = 1;
  for (int i = 2; i <= n; ++i)
    inv[i] = 1LL * (MOD - MOD / i) * inv[MOD % i] % MOD;

  max_dep = 0;
  dfs(1, 1);
  cout << gao(1) << '\n';

  return 0;
}
