#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e3 + 3;
const int MOD = 1e9 + 7;

int f[4][MAXN][MAXN], a[MAXN][MAXN];
pair<int, int> p[MAXN * MAXN];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
  cout << fixed << setprecision(10);

  int n, m, cnt = 0;
  cin >> n >> m;
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      cin >> a[i][j];
      p[cnt++] = make_pair(a[i][j], i << 10 | j);
    }
  }
  sort(p, p + cnt);

  int ans = 0;
  for (int i = 0; i < cnt; ++i) {
    int v = p[i].first;
    int x = p[i].second >> 10, y = p[i].second & 1023;

    static int dx[] = {0, 1, 0, -1};
    static int dy[] = {1, 0, -1, 0};
    static auto valid = [&](const int &x, const int &y) {
      return 1 <= x && x <= n && 1 <= y && y <= m;
    };
    static auto add = [&](int &a, int b) {
      a += b;
      if (a >= MOD) a -= MOD;
    };
    bool fg1 = true, fg2 = true;
    for (int i = 0; i < 4; ++i) {
      int x_ = x + dx[i];
      int y_ = y + dy[i];
      if (!valid(x_, y_)) continue;
      if (a[x_][y_] != v - 1) {
        fg1 &= a[x_][y_] != v + 1;
        continue;
      }
      fg2 = false;
      for (int j = 0; j < 3; ++j) add(f[j + 1][x][y], f[j][x_][y_]);
      add(f[3][x][y], f[3][x_][y_]);
    }
    if (fg1) {
      // cerr << "# " << x << " " << y << " " << f[3][x][y] << endl;
      add(ans, f[3][x][y]);
    }
    if (fg2) { f[0][x][y] = 1; }
  }

  cout << ans << "\n";

  return 0;
}
