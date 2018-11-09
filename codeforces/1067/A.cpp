#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int n, f[201][2], g[201][2];
  cin >> n;
  for (int i = 0; i < 201; i++) {
    f[i][0] = 1;
    f[i][1] = 0;
  }
  auto Add =
    [](int a, int b) {
      a += b;
      if (a >= MOD) {
        a -= MOD;
      }
      return a;
    };
  auto Sub =
    [](int a, int b) {
      a -= b;
      if (a < 0) {
        a += MOD;
      }
      return a;
    };

  for (int step = 0; step < n; step++) {
    int x;
    cin >> x;
    memset(g, 0, sizeof(g));
    for (int i = 1; i <= 200; i++) {
      g[i][0] = g[i - 1][0];
      g[i][1] = g[i - 1][1];
      if (x == -1 || i == x) {
        g[i][0] = Add(g[i][0], Add(f[i - 1][0], f[i - 1][1]));
        g[i][1] = Add(g[i][1], Sub(f[i][0], f[i - 1][0]));
        g[i][1] = Add(g[i][1], Sub(f[200][1], f[i - 1][1]));
      }
    }
    memcpy(f, g, sizeof(g));
  }
  cout << f[200][1] << endl;
  return 0;
}
