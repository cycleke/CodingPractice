#include <bits/stdc++.h>
using namespace std;

int belong[1001][1001];
int cnt[1000 * 1000 + 3];
char a[1001][1003];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int n, m;
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> (a[i] + 1);
    //cerr << a[i] + 1 << endl;
  }

  while (m--) {
    int x, y;
    cin >> x >> y;
    if (belong[x][y]) {
      cout << cnt[belong[x][y]] << endl;
      continue;
    }
    static int belong_id = 0;
    static queue<int> q;
    belong_id++;
    q.push(x << 10 | y);
    belong[x][y] = belong_id;
    while (!q.empty()) {
      int x = q.front() >> 10;
      int y = q.front() & 1023;
      q.pop();

      cnt[belong_id]++;

      static const int dx[] = {0, 0, 1, -1};
      static const int dy[] = {1, -1, 0, 0};
      auto OutOfRange = [&](const int &x) {
        return x < 1 || x > n;
      };

      for (int i = 0; i < 4; i++) {
        int _x = x + dx[i];
        int _y = y + dy[i];
        if (OutOfRange(_x) || OutOfRange(_y)
            || a[_x][_y] == a[x][y] || belong[_x][_y])
          continue;
        q.push(_x << 10 | _y);
        belong[_x][_y] = belong_id;
      }
    }
    cout << cnt[belong_id] << endl;
  }

  return 0;
}
