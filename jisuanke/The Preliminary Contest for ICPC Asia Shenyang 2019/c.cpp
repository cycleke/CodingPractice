#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e3 + 5;
const int MAXM = 1e4 + 5;

int n, m, p[MAXN], c[MAXN];
long long dp[MAXM];

void solve() {
  int limit = 0;
  for (int i = 0; i < n; ++i) {
    cin >> p[i] >> c[i];
    limit = max(limit, c[i]);
  }
  limit = min(MAXM, limit + m + 5);
  memset(dp, 0x3f, sizeof(long long) * limit);
  dp[0] = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = c[i]; j < limit; ++j) dp[j] = min(dp[j], dp[j - c[i]] + p[i]);
    // for (int j = 0; j < limit; ++j) cout << dp[j] << ' ';
    // cout << '\n';
  }

  long long a = 0x3f3f3f3f3f3f3f3fLL;
  int b = 0;
  for (int i = m; i < limit; ++i)
    if (dp[i] <= a) {
      a = dp[i];
      b = i;
    }
  cout << a << ' ' << b << '\n';
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  while (cin >> n >> m) solve();

  return 0;
}
