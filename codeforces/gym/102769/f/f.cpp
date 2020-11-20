#include <bits/stdc++.h>
using namespace std;

const int MAXN = 3e5 + 3;

vector<int> adj[MAXN];
bitset<MAXN> mark;

void solve() {
  int n, m;
  cin >> n >> m;
  for (int i = 1; i <= n; ++i) adj[i].clear(), mark[i] = 0;
  for (int u, v; m; --m) {
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  int ans = 0;
  for (int i = 1; i <= n; ++i) {
    if (mark[i]) continue;
    int vs = 0, es = 0;
    static queue<int> q;
    q.push(i);
    mark[i] = 1;
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      ++vs, es += adj[u].size();
      for (int v : adj[u]) {
        if (mark[v]) continue;
        mark[v] = 1;
        q.push(v);
      }
    }
    ans += max(0, es / 2 - vs);
  }
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
