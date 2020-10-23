#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 1e6 + 3;

vector<int> adj[MAXN];
int dep[MAXN], max_dep[MAXN];
long long ans;

void dfs1(int u) {
  max_dep[u] = dep[u];
  for (int v : adj[u]) {
    dep[v] = dep[u] + 1;
    dfs1(v);
    max_dep[u] = max(max_dep[u], max_dep[v]);
  }
}

int dfs2(int u, int loc) {
  sort(adj[u].begin(), adj[u].end(),
       [&](const int &a, const int &b) { return max_dep[a] < max_dep[b]; });
  for (int v : adj[u]) {
    ans += min(dep[v], dep[v] + dep[loc] - 2 * dep[u]);
    loc = dfs2(v, v);
  }
  return loc;
}

void solve() {
  int n;
  cin >> n;
  for (int i = 1; i <= n; ++i) adj[i].clear();
  for (int i = 2, f; i <= n; ++i) {
    cin >> f;
    adj[f].push_back(i);
  }
  dep[1] = 0;
  dfs1(1);
  ans = 0;
  dfs2(1, 1);
  cout << ans << "\n";
}

int main(int argc, char *argv[]) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);

  int T;
  cin >> T;
  for (int step = 1; step <= T; ++step) {
    cout << "Case #" << step << ": ";
    solve();
  }

  return 0;
}
