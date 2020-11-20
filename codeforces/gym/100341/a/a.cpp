#include <bits/stdc++.h>
using namespace std;

const int MAXS = 22;
const int MAXN = 20 * 20 + 5;
const int INF = 0x3fffff;
typedef pair<int, int> pii;

int mat[MAXS][MAXS], w, h, n, m, X[MAXN], Y[MAXN];
int match[MAXN], x_match[MAXN];
int dist[MAXN][MAXN], lx[MAXN], ly[MAXN], slack[MAXN];
int visx[MAXN], visx_c, visy[MAXN], visy_c;

bool dfs(int x) {
  visx[x] = visx_c;
  for (int y = 1; y <= m; ++y)
    if (visy[y] ^ visy_c) {
      int t = lx[x] + ly[y] - dist[x][y];
      if (!t) {
        visy[y] = visy_c;
        if (!match[y] || dfs(match[y])) return match[y] = x, true;
      } else {
        (slack[y] > t) && (slack[y] = t);
      }
    }
  return false;
}

void KM() {
  for (int i = 1; i <= n; ++i) {
    lx[i] = -INF;
    for (int j = 1; j <= m; ++j) (dist[i][j] > lx[i]) && (lx[i] = dist[i][j]);
  }
  for (int x = 1; x <= n; ++x) {
    fill(slack + 1, slack + m + 1, INF);
    for (;;) {
      ++visx_c, ++visy_c;
      if (dfs(x)) break;
      int d = INF;
      for (int i = 1; i <= m; ++i)
        (visy[i] ^ visy_c) && (d > slack[i]) && (d = slack[i]);
      for (int i = 1; i <= n; ++i) (visx[i] == visx_c) && (lx[i] -= d);
      for (int i = 1; i <= m; ++i)
        (visy[i] ^ visx_c) ? slack[i] -= d : ly[i] += d;
    }
  }
  for (int y = 1; y <= m; ++y) match[y] && (x_match[match[y]] = y);
}

vector<int> adj[MAXN];
int deg[MAXN];

void toposort() {
  queue<int> que;
  for (int i = 1; i <= n; ++i)
    if (!deg[i]) que.push(i);
  bool first = true;
  while (!que.empty()) {
    int u = que.front();
    que.pop();
    if (first) {
      first = false;
    } else {
      cout << ' ';
    }
    cout << u;
    for (int v : adj[u])
      if (!--deg[v]) que.push(v);
  }
  cout << '\n';
}

int main(int argc, char *argv[]) {
  freopen("agrarian.in", "r", stdin);
  freopen("agrarian.out", "w", stdout);
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int k, s;
  cin >> h >> w >> k >> s;

  n = k;
  for (int i = 1; i <= n; ++i) {
    cin >> X[i] >> Y[i];
    mat[X[i]][Y[i]] = i;
  }

  for (int i = 0, x, y; i < s; ++i) {
    cin >> x >> y;
    mat[x][y] = INT_MAX;
  }

  m = 0;
  for (int i = 1; i <= h; ++i)
    for (int j = 1; j <= w; ++j)
      if (mat[i][j]) {
        if (mat[i][j] == INT_MAX) mat[i][j] = 0;
      } else {
        mat[i][j] = --m;
        X[n - m] = i, Y[n - m] = j;
      }
  m = -m;
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j)
      dist[i][j] = -abs(X[i] - X[n + j]) - abs(Y[i] - Y[n + j]);

  KM();

  for (int x = 1, y; x <= n; ++x) {
    int d = -dist[x][x_match[x]];
    bool succeed = false;
    for (int t = 1; t <= d; ++t) {
      for (int dx = -t; dx <= t; ++dx) {
        int dy = t - (dx > 0 ? dx : -dx);

        int _x = X[x] + dx, _y = Y[x] - dy;
        if (_x > 0 && _x <= h && _y > 0 && _y <= w && (y = -mat[_x][_y]) > 0) {
          if (match[y] && match[y] != x) {
            ++deg[x];
            adj[match[y]].push_back(x);
          } else {
            succeed = true;
          }
        }

        _x = X[x] + dx, _y = Y[x] + dy;
        if (dy && !succeed && _x > 0 && _x <= h && _y > 0 && _y <= w &&
            (y = -mat[_x][_y]) > 0) {
          if (match[y] && match[y] != x) {
            ++deg[x];
            adj[match[y]].push_back(x);
          } else {
            succeed = true;
          }
        }

        if (succeed) break;
      }
    }
  }

  toposort();

  return 0;
}
