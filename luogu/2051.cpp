#include <bits/stdc++.h>
using namespace std;

void ModAdd(int &a, const long long &b) {
  static const int MOD = 9999973;
  a = (a + b) % MOD;
}

const int MAXN = 101;
int dp[2][MAXN][MAXN];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int n, m;
  cin >> n >> m;
  auto f = dp[0], g = dp[1];
  f[0][0] = 1;
  for (int step = 0; step < n; step++) {
    memset(g, 0, MAXN * MAXN * sizeof(int));
    for (int i = 0; i <= m; i++) {
      for (int j = 0; i + j <= m; j++) {
        if (f[i][j] == 0) continue;
        static auto C2 = [](const int &a) {
          return a * (a - 1) / 2;
        };
        ModAdd(g[i][j], f[i][j]);
        if (i >= 1) ModAdd(g[i - 1][j + 1], (long long)f[i][j] * i);
        if (i >= 2) ModAdd(g[i - 2][j + 2], (long long)f[i][j] * C2(i));
        if (m - i - j >= 1) ModAdd(g[i + 1][j], (long long)f[i][j] * (m - i - j));
        if (m - i - j >= 2) ModAdd(g[i + 2][j], (long long)f[i][j] * C2(m - i - j));
        if (m - i - j >= 1 && i >= 1) ModAdd(g[i][j + 1], (long long)f[i][j] * (m - i - j) * i);
      }
    }
    swap(f, g);
  }
  int ans = 0;
    for (int i = 0; i <= m; i++)
      for (int j = 0; i + j <= m; j++)
        ModAdd(ans, f[i][j]);
    cout << ans << endl;
  return 0;
}
