#include <bits/stdc++.h>
using namespace std;

int n, sum[201], dp[201][40001];
pair<int, int> p[201];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n;
  for (int i = 1; i <= n; i++)
    cin >> p[i].first >> p[i].second;

  sort(p + 1, p + n + 1,
       [](const pair<int, int> &a, const pair<int, int> &b) {
         return a.second > b.second;
       });
  for (int i = 1; i <= n; i++)
    sum[i] = sum[i - 1] + p[i].first;
  memset(dp, 63, sizeof(dp));
  dp[0][0] = 0;
  for (int i = 1; i <= n; i++)
    for (int j = 0; j <= sum[i]; j++) {
      if (j >= p[i].first) dp[i][j] = min(dp[i][j], max(dp[i - 1][j - p[i].first], j + p[i].second));
      dp[i][j] = min(dp[i][j], max(dp[i - 1][j], sum[i] - j + p[i].second));
    }
  int ans = 0x3f3f3f3f;
  for (int i = 1; i <= sum[n]; i++)
    ans = min(ans, dp[n][i]);
  cout << ans << endl;

  return 0;
}
