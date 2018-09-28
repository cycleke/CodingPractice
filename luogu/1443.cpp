#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int n, m, sx, sy;
  cin >> n >> m >> sx >> sy;
  queue<int> q;
  int d[401][401];
  memset(d, -1, sizeof(d));
  d[sx][sy] = 0;
  q.push(sx << 9 | sy);
  while (!q.empty()) {
    int x = q.front() >> 9;
    int y = q.front() & 511;
    q.pop();
    static const int dx[] = {1, 1, -1, -1, 2, -2, 2, -2};
    static const int dy[] = {2, -2, 2, -2, 1, 1, -1, -1};
    for (int i = 0; i < 8; i++) {
      int _x = x + dx[i];
      int _y = y + dy[i];
      auto OutOfRange = [&](int x, int n) {
        return x < 1 || x > n;
      };

      if (OutOfRange(_x, n) || OutOfRange(_y, m) || (~d[_x][_y]))
        continue;
      q.push(_x << 9 | _y);
      d[_x][_y] = d[x][y] + 1;
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      cout << left << setw(5) << d[i][j];
    }
    cout << endl;
  }
  return 0;
}
