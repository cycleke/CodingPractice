#include <bits/stdc++.h>
using namespace std;

int a[801][801];
int f[801][801][16][2];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int n, m, k;
  cin >> n >> m >> k;
  k++;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      cin >> a[i][j];
      f[i][j][a[i][j]][1] = 1;
    }
  }
  auto ModAdd =
    [](int &a, const int &b) {
      static int MOD = 1e9 + 7;
      a += b;
      if (a >= MOD)
        a -= MOD;
    };
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      for (int d = 0; d < k; d++) {
        ModAdd(f[i][j][d][1], f[i][j - 1][(d - a[i][j] + k) % k][0]);
        ModAdd(f[i][j][d][1], f[i - 1][j][(d - a[i][j] + k) % k][0]);
        ModAdd(f[i][j][d][0], f[i][j - 1][(d + a[i][j]) % k][1]);
        ModAdd(f[i][j][d][0], f[i - 1][j][(d + a[i][j]) % k][1]);
      }
    }
  }
  int sum = 0;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      ModAdd(sum, f[i][j][0][0]);
    }
  }
  cout << sum << endl;
  return 0;
}
