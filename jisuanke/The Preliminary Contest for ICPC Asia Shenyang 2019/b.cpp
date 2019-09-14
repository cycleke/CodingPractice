#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 5;

bool monster[MAXN];
vector<int> adj[MAXN];
int n, m, k, mark[MAXN], size[MAXN], blc, nerb[MAXN], nerb_c;

void dfs(int u) {
  mark[u] = blc;
  ++size[blc];
  for (int v : adj[u]) {
    if (monster[v]) {
      if (!blc) nerb[nerb_c++] = v;
      continue;
    }
    if (~mark[v]) continue;
    dfs(v);
  }
}

void solve() {
  cin >> n >> m >> k;
  for (int i = 0; i < n; ++i) adj[i].clear();
  memset(mark, -1, sizeof(int) * n);
  memset(monster, 0, sizeof(bool) * n);
  for (int u, v; m; --m) {
    cin >> u >> v;
    --u, --v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  for (int u; k; --k) {
    cin >> u;
    monster[u - 1] = true;
  }
  blc = nerb_c = 0;
  for (int i = 0; i < n; ++i) {
    if (monster[i] || (~mark[i])) continue;
    size[blc] = 0;
    dfs(i);
    ++blc;
  }

  double ans = 0, tmp = size[0];
  size[0] = 0;
  for (int i = 0; i < nerb_c; ++i) {
    int u = nerb[i];
    int sum = 0;
    for (int v : adj[u])
      if (~mark[v]) sum += size[mark[v]];
    ans = max(ans, 1.0 * sum / adj[u].size());
  }
  cout << ans + tmp << '\n';
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout << fixed << setprecision(10);

  int o_o;
  for (cin >> o_o; o_o; --o_o) solve();
  return 0;
}
