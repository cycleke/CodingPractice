#include <bits/stdc++.h>
using namespace std;

const int MAXN = 505;
const int MAXC = 1e4 + 5;

struct App {
  int d, s, id;
} apps[MAXN];

bool operator<(const App &a, const App &b) { return a.s > b.s; }

int n, c, dp[MAXN][MAXN];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> c;
  for (int i = 0, d, s; i < n; ++i) {
    cin >> d >> s;
    apps[i] = {max(d, s), max(d, s) - s, i + 1};
  }
  sort(apps, apps + n);

  memset(dp, 0x3f, sizeof(dp));
  dp[0][0] = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j <= i; ++j) {
      dp[i + 1][j] = min(dp[i + 1][j], dp[i][j]);
      if (dp[i][j] + apps[i].d <= c &&
          dp[i][j] + apps[i].d - apps[i].s < dp[i + 1][j + 1])
        dp[i + 1][j + 1] = dp[i][j] + apps[i].d - apps[i].s;
    }
  }

  for (int i = n; ~i; --i) {
    if (dp[n][i] < 0x3f3f3f3f) {
      vector<int> ans;
      int x = n, y = i;
      while (y) {
        for (int j = x; ~j; --j)
          if (dp[j][y] == dp[j - 1][y - 1] + apps[j - 1].d - apps[j - 1].s) {
            ans.push_back(apps[j - 1].id);
            x = j - 1, --y;
            break;
          }
      }
      reverse(ans.begin(), ans.end());
      cout << ans.size() << '\n';
      for (int x : ans) cout << x << ' ';
      break;
    }
  }
  return 0;
}
