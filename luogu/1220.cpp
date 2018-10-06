#include <bits/stdc++.h>
using namespace std;

int f[51][51][2];
int p[51], sum[52];
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int n, c;
  cin >> n >> c;
  for (int i = 1; i <= n; i++) {
    int w;
    cin >> p[i] >> w;
    sum[i] = sum[i - 1] + w;
  }
  memset(f, 63, sizeof(f));
  f[c][c][0] = f[c][c][1] = 0;
  for (int len = 2; len <= n; len++) {
    for (int i = 1, j = i + len - 1; j <= n; i++, j++) {
      f[i][j][0] = min(f[i + 1][j][0] + (p[i + 1] - p[i]) * (sum[i] + sum[n] - sum[j]),
                       f[i + 1][j][1] + (p[j] - p[i]) * (sum[i] + sum[n] - sum[j]));
      f[i][j][1] = min(f[i][j - 1][1] + (p[j] - p[j - 1]) * (sum[i - 1] + sum[n] - sum[j - 1]),
                       f[i][j - 1][0] + (p[j] - p[i]) * (sum[i - 1] + sum[n] - sum[j - 1]));
    }
  }
  cout << min(f[1][n][0], f[1][n][1]) << endl;
  return 0;
}
