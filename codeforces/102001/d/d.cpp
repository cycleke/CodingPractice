#include <bits/stdc++.h>
using namespace std;

const int MAXN = 505;

char maze[MAXN][MAXN];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;
  for (int i = 0; i < n; ++i) cin >> maze[i];

  int ans = 0;
  if (n == 1) {
    for (int i = 1; i < m - 1; ++i) ans += maze[0][i] == '.';
  } else if (n == 2) {
    for (int i = 1; i < m - 1; ++i)
      ans += maze[0][i] == '.' && maze[1][i] == '.';
  } else if (m == 1) {
    for (int i = 1; i < n - 1; ++i) ans += maze[i][0] == '.';
  } else if (m == 2) {
    for (int i = 1; i < n - 1; ++i)
      ans += maze[i][0] == '.' && maze[i][1] == '.';
  } else {
    bool have = false;
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < m; ++j) {
        bool b1 = i == 0 || i == n - 1;
        bool b2 = j == 0 || j == m - 1;
        if (b1 && b2) continue;
        if (b1 || b2)
          have |= maze[i][j] == '#';
        else
          ans += maze[i][j] == '.';
      }
    if (!have) ++ans;
  }
  cout << ans << '\n';
  return 0;
}
