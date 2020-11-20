#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2e3 + 5;

bool mark[MAXN];
int x[MAXN], y[MAXN], k[MAXN], c[MAXN], con[MAXN];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;
  for (int i = 0; i < n; ++i)
    cin >> x[i] >> y[i];
  for (int i = 0; i < n; ++i) cin >> c[i];
  for (int i = 0; i < n; ++i) cin >> k[i];

  memset(con, -1, sizeof(int) * n);
  long long ans = 0;
  vector<int> stations;
  vector<pair<int, int>> edges;
  for (int i = 0; i < n; ++i) {
    int u = -1;
    for (int j = 0; j < n; ++j) {
      if (mark[j]) continue;
      if (u < 0 || c[u] > c[j]) u = j;
    }
    if (u < 0) return -1;
    ans += c[u];
    mark[u] = true;
    if (~con[u]) {
      edges.emplace_back(u + 1, con[u] + 1);
    } else {
      stations.push_back(u + 1);
    }
    for (int j = 0; j < n; ++j) {
      if (mark[j]) continue;
      long long t = k[u] + k[j];
      t *= abs(x[u] - x[j]) + abs(y[u] - y[j]);
      if (t < c[j]) {
        c[j] = t;
        con[j] = u;
      }
    }
  }

  cout << ans << '\n';
  cout << stations.size() << '\n';
  for (int p : stations) cout << p << ' ';
  cout << '\n' << edges.size() << '\n';
  for (auto e : edges) cout << e.first << ' ' << e.second << '\n';

  return 0;
}
