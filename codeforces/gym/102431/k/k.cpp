#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2e5 + 3;

vector<int> adj[MAXN];
int n, pa[MAXN], ans[MAXN];
set<int> contains[MAXN], *idx[MAXN];

int find(int x) { return x == pa[x] ? x : pa[x] = find(pa[x]); }

void merge(int u, int v) {
  ans[u] += ans[v];
  if (idx[u]->size() < idx[v]->size()) swap(idx[u], idx[v]);

  auto &su = *idx[u], &sv = *idx[v];
  for (int x : sv) {
    if (su.find(x + 1) != su.end()) { --ans[u], pa[x + 1] = find(x); }
    if (x != find(x)) continue;
    if (su.find(x - 1) != su.end()) { --ans[u], pa[x] = find(x - 1); }
  }
  for (int x : sv) su.insert(x);
  sv.clear();
}

void dfs(int u, int from) {
  ans[u] = 1;
  idx[u]->insert(u);

  for (int v : adj[u]) {
    if (v == from) continue;
    dfs(v, u);
    merge(u, v);
  }
}

void solve() {
  cin >> n;
  for (int i = 1; i <= n; ++i) {
    pa[i] = i;
    adj[i].clear();
    contains[i].clear();
    idx[i] = contains + i;
  }

  for (int i = 1, a, b; i < n; ++i) {
    cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }

  dfs(1, 1);
  for (int i = 1; i <= n; ++i) cout << " " << ans[i];
  cout << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);

  int o_o;
  cin >> o_o;
  for (int step = 1; step <= o_o; ++step) {
    cout << "Case #" << step << ":";
    solve();
  }

  return 0;
}
