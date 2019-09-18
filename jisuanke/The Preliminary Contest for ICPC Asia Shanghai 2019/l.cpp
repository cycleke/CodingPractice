#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;

const int MAXD = 22;

pii dp[MAXD][10];
int n, b, dig[MAXD], len;

pii dfs(int step, int cur, bool limit) {
  if (!step) return pii(cur, 1);
  if (!limit && (~dp[step][cur].first)) return dp[step][cur];
  int f = 0, s = 0;

  int end = limit ? dig[step - 1] : b - 1;
  for (int i = 0; i <= end; ++i) {
    pii p = dfs(step - 1, i, limit && i == end);
    f += p.first;
    s += p.second;
  }
  f += s * cur;

  if (!limit) dp[step][cur] = pii(f, s);
  return pii(f, s);
}

void solve() {
  cin >> n >> b;

  for (len = 0; n; n /= b, ++len) dig[len] = n % b;
  dig[len] = 0;
  memset(dp, -1, sizeof(dp));
  cout << dfs(len, 0, true).first << '\n';
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int o_o;
  cin >> o_o;
  for (int i = 1; i <= o_o; ++i) {
    cout << "Case #" << i << ": ";
    solve();
  }
}
