#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int n;
  cin >> n;
  int a[30][31];
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cin >> a[i][j];
    }
  }

  bool vis[30][31];
  queue<int> q;

  memset(vis, 0, sizeof(vis));
  for (int i = 0; i < n; i++) {
    if (a[0][i] == 0) {
      q.push(0 << 5 | i);
      vis[0][i] = true;
    }
    if (a[n - 1][i] == 0) {
      q.push((n - 1) << 5 | i);
      vis[n - 1][i] = true;
    }
  }
  for (int i = 1; i < n - 1; i++) {
    if (a[i][0] == 0) {
      q.push(i << 5 | 0);
      vis[i][0] = true;
    }
    if (a[i][n - 1] == 0) {
      q.push((i) << 5 | (n - 1));
      vis[i][n - 1] = true;
    }
  }
  while (!q.empty()) {
    int status = q.front();
    q.pop();
    int x = status >> 5;
    int y = status & 31;
    static int dx[] = {0, 0, 1, -1};
    static int dy[] = {1, -1, 0, 0};
    auto OutOfRange = [&](const int &x) {
      return x < 0 || x >= n;
    };
    for (int i = 0; i < 4; i++) {
      int _x = x + dx[i];
      int _y = y + dy[i];
      if (OutOfRange(_x) || OutOfRange(_y) || vis[_x][_y] || a[_x][_y] == 1)
        continue;
      q.push(_x << 5 | _y);
      vis[_x][_y] = true;
    }
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (vis[i][j]) {
        cout << a[i][j] << ' ';
      } else {
        cout << (a[i][j] == 1 ? 1 : 2) << ' ';
      }
    }
    cout << endl;
  }
  return 0;
}
