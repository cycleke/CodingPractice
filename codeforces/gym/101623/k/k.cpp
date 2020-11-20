#include <bits/stdc++.h>
using namespace std;

typedef pair<int, long double> data;

const int MAXN = 4100;
const double EPS = 1e-10;

int a[MAXN * 2];
vector<data> dp[MAXN * 2];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout << fixed << setprecision(10);
  int n;
  cin >> n;
  for (int i = 1; i <= n; ++i) cin >> a[i];
  swap(a[1], a[n]);
  sort(a + 1, a + n, greater<int>());

  int dep = 0;
  while ((1 << dep) < n) ++dep;

  int empty = (1 << dep) - n;
  for (int i = 1; i <= n - empty; ++i)
    dp[i + (1 << dep) - 1].emplace_back(i, 1);
  for (int i = n - empty + 1, j = (i + (1 << dep) - 1); i <= n; ++i, j += 2) {
    dp[j].emplace_back(i, 1);
    // dp[j + 1].emplace_back(0, 1);
  }

  for (int u = (1 << dep) - 1; u; --u) {
    int left = u << 1, right = u << 1 | 1;
    for (data &x : dp[left]) {
      int r = a[x.first];
      double p = 0;
      for (data &y : dp[right]) p += y.second * r / (r + a[y.first]);
      if (dp[right].empty()) p = 1;
      p *= x.second;
      // if (p < EPS) continue;
      dp[u].emplace_back(x.first, p);
    }
    for (data &x : dp[right]) {
      int r = a[x.first];
      double p = 0;
      for (data &y : dp[left]) p += y.second * r / (r + a[y.first]);
      if (dp[left].empty()) p = 1;
      p *= x.second;
      // if (p < EPS) continue;
      dp[u].emplace_back(x.first, p);
    }
  }

  for (data &x : dp[1])
    if (x.first == n) cout << x.second << '\n';
  return 0;
}
