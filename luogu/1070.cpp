#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1001, INF = 0x3f3f3f3f;
typedef int Array[MAXN], Array2[MAXN][MAXN];
typedef pair<int, int> pii;

Array cost, dp;
Array2 sum, rec, pre, money;
priority_queue<pii>heap[MAXN];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int n, m, p;
  cin >> n >> m >> p;
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++)
      cin >> money[i % n][j];
  for (int i = 0; i < n; i++)
    cin >> cost[i];
  for (int i = 1; i <= m; i++)
    for (int j = 0; j < n; j++)
      sum[i][j] = sum[i - 1][(j - 1 + n) % n] + money[j][i];
  for (int i = 0; i < n; i++)
    pre[0][(i - 1 + n) % n] = i;
  for (int i = 0; i < n; i++) {
    rec[0][i] = -cost[i];
    heap[pre[0][i]].push(make_pair(-cost[i], 0));
  }

  int ans = -INF;
  for (int i = 1; i <= m; i++) {
    int temp = -INF;
    dp[i] = -INF;
    for (int j = 0; j < n; j++) {
      dp[i] = max(dp[i], rec[i - 1][(j - 1 + n) % n] + sum[i][j]);
      ans = max(ans, dp[i]);
      temp = max(temp, dp[i]);
    }
    for (int j = 0; j < n; j++) {
      pre[i][j] = pre[i - 1][(j - 1 + n) % n];
      auto &q_heap = heap[pre[i][j]];
      q_heap.push(make_pair(temp - sum[i][j] - cost[j], i));
      while (i - q_heap.top().second >= p) q_heap.pop();
      rec[i][j] = q_heap.top().first;
    }
  }
  cout << ans << endl;
  return 0;
}
