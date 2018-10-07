#include <bits/stdc++.h>
using namespace std;

int a[80];
__int128 p2[81], f[80][80];

void Print(__int128 x) {
  if (x == 0)
    return;
  Print(x / 10);
  cout << char(x % 10 + '0');
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int n, m;
  cin >> n >> m;
  p2[0] = 1;
  for (int i = 1; i <= m; i++)
    p2[i] = p2[i - 1] << 1;

  __int128 ans = 0;
  for (int step = 0; step < n; step++) {
    for (int i = 0; i < m; i++) {
      cin >> a[i];
      f[i][i] = a[i] * p2[m];
    }
    for (int len = 2; len <= m; len++) {
      __int128 p = p2[m - len + 1];
      for (int i = 0, j = len - 1; j < m; i++, j++) {
        f[i][j] = max(f[i + 1][j] + a[i] * p, f[i][j - 1] + a[j] * p);
      }
    }
    ans += f[0][m - 1];
  }
  if (ans == 0) {
    cout << 0 << endl;
  } else {
    Print(ans);
    cout << endl;
  }
  return 0;
}
