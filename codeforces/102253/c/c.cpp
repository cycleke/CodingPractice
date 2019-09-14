#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2e5 + 5;

int n, c[MAXN], size[MAXN], pos[MAXN], cnt[MAXN], cc[MAXN];
vector<int> adj[MAXN];
long long ans;

inline long long ract(long long n) { return n * (n - 1) >> 1; }

void dfs(int u, int from) {
  int anc = pos[c[u]];
  pos[c[u]] = u;
  size[u] = 1;
  for (int v : adj[u]) {
    if (v == from) continue;
    cnt[u] = 0;
    dfs(v, u);
    ans -= ract(size[v] - cnt[u]);
    size[u] += size[v];
  }
  if (~anc) {
    cnt[anc] += size[u];
  } else {
    cc[c[u]] += size[u];
  }
  pos[c[u]] = anc;
}

int main() {
  // freopen("in1.txt", "r", stdin);
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int case_count = 0;
  while (cin >> n) {
    cout << "Case #" << ++case_count << ": ";
    for (int i = 0; i < n; ++i) cin >> c[i], adj[i].clear();
    memset(cc, 0, sizeof(int) * (n + 1));
    memset(pos, -1, sizeof(int) * (n + 1));
    for (int i = 1, u, v; i < n; ++i) {
      cin >> u >> v;
      --u, --v;
      adj[u].push_back(v);
      adj[v].push_back(u);
    }
    ans = n * ract(n);
    dfs(0, 0);
    for (int i = 1; i <= n; ++i) { ans -= ract(n - cc[i]); }
    cout << ans << '\n';
  }
  return 0;
}
