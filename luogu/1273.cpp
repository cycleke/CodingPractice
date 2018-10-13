#include <bits/stdc++.h>
using namespace std;

const int MAXN = 3001;

vector<pair<int, int> > g[MAXN];
int payment[MAXN], dp[MAXN][MAXN], n, m;

int dfs(int u) {
  if (u > n - m) {
    dp[u][1] = payment[u];
    return 1;
  } else {
    int terminals = 0;
    for (auto e : g[u]) {
      int t = dfs(e.first);
      terminals += t;
      for (int i = terminals; i > 0; i--)
        for (int j = 0; j <= t; j++) {
          if (i - j < 0) break;
          dp[u][i] = max(dp[u][i], dp[u][i - j] + dp[e.first][j] - e.second);
        }
    }
    return terminals;
  }
}


int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n >> m;
  for (int i = 1; i <= n - m; i++) {
    int k;
    cin >> k;
    g[i] = vector<pair<int, int> >(k);
    for (int j = 0; j < k; j++) {
      cin >> g[i][j].first >> g[i][j].second;
    }
  }
  for (int i = n - m + 1; i <= n; i++) {
    cin >> payment[i];
  }
  memset(dp, ~63, sizeof(dp));
  for (int i = 1; i <= n; i++) dp[i][0] = 0;
  if (dfs(1) != m) {
    cerr << "Wrong Data" << endl;
    return -1;
  }
  for (int i = m; i >= 0; i--) {
    if (dp[1][i] < 0) continue;
    cout << i << endl;
    break;
  }

  return 0;
}
