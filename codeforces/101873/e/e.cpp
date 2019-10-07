#include <bits/stdc++.h>
using namespace std;

const int MAXN = 805;
const double LOG_1dot1 = log(1.1);
const double EPS = 1e-10;

double dis[MAXN];
vector<pair<int, double> >adj[MAXN];
bool vis[MAXN];

bool spfa(int u) {
  vis[u] = true;
  for (auto e : adj[u]) {
    if (dis[u] + e.second >= dis[e.first] - EPS) continue;
    dis[e.first] = dis[u] + e.second;
    if (vis[e.first] || spfa(e.first))
      return true;
  }
  vis[u] = false;
  return false;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;

  int u, v;
  double w;
  for (int i = 0; i < m; ++i) {
    cin >> u >> v >> w;
    adj[u].emplace_back(v, -log(w));
  }

  for (int i = 1; i <= n; ++i)
    if (spfa(i)) {
      cout << "inadmissible\n";
      return 0;
    }
  cout << "admissible\n";
  return 0;
}
