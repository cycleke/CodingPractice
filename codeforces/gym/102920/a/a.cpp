#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;

void debug_out() { cerr << endl; }
template <typename T> string to_string(const vector<T> &vec) {
  string res = "[";
  bool first = true;
  for (const T &x : vec) {
    if (first) {
      first = false;
    } else {
      res += ",";
    }
    res += to_string(x);
  }
  return res + "]";
}
template <typename Head, typename... Tail> void debug_out(Head H, Tail... T) {
  cerr << " " << to_string(H);
  debug_out(T...);
}
#ifdef ONLINE_JUDGE
#define debug(...)
#else
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#endif

constexpr int MAXN = 503;

int bx[MAXN], by[MAXN], ex[MAXN], ey[MAXN];
pii intersect[MAXN][MAXN], fwd[MAXN][MAXN][4];
// dir: u: 0, l: 1, d: 2, r: 3

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);

  int n;
  ll t;
  cin >> n >> t;
  int sx = 1, sy = -1, dir = -1;
  for (int i = 1; i <= n; ++i) {
    cin >> bx[i] >> by[i] >> ex[i] >> ey[i];
    if (bx[i] == ex[i]) {
      if (by[i] > ey[i]) {
        swap(by[i], ey[i]);
        if (i == 1) { sy = n + 2, dir = 2; }
      } else if (i == 1) {
        sy = n + 1, dir = 0;
      }
    } else {
      if (bx[i] > ex[i]) {
        swap(bx[i], ex[i]);
        if (i == 1) { sy = n + 2, dir = 1; }
      } else if (i == 1) {
        sy = n + 1, dir = 3;
      }
    }
  }

  memset(fwd, 128, sizeof(fwd));
  memset(intersect, 128, sizeof(intersect));
  for (int i = 1; i <= n; ++i) {
    intersect[i][n + 1] = intersect[n + 1][i] = {bx[i], by[i]};
    intersect[i][n + 2] = intersect[n + 2][i] = {ex[i], ey[i]};
  }

  static auto fwdlr = [&](int a, int b, int c, int d) {
    fwd[min(a, b)][max(a, b)][3] = {min(c, d), max(c, d)};
    fwd[min(c, d)][max(c, d)][1] = {min(a, b), max(a, b)};
  };
  static auto fwdud = [&](int a, int b, int c, int d) {
    fwd[min(a, b)][max(a, b)][0] = {min(c, d), max(c, d)};
    fwd[min(c, d)][max(c, d)][2] = {min(a, b), max(a, b)};
  };

  for (int i = 1; i <= n; ++i) {
    static vector<pii> v;
    v.clear();
    if (bx[i] == ex[i]) {
      for (int j = 1; j <= n; ++j) {
        if (bx[j] == ex[j]) continue;
        if (by[i] <= by[j] && by[j] <= ey[i] && bx[j] <= bx[i] &&
            bx[i] <= ex[j]) {
          intersect[i][j] = intersect[j][i] = {bx[i], by[j]};
          v.emplace_back(by[j], j);
        }
      }
      sort(v.begin(), v.end());
      if (!v.empty()) {
        for (int j = 0; j < static_cast<int>(v.size()) - 1; ++j)
          fwdud(i, v[j].second, i, v[j + 1].second);
        fwdud(i, n + 1, i, v[0].second);
        fwdud(i, v.back().second, i, n + 2);
      } else {
        fwdud(i, n + 1, i, n + 2);
      }
    } else {
      for (int j = 1; j <= n; ++j) {
        if (by[j] == ey[j]) continue;
        if (bx[i] <= bx[j] && bx[j] <= ex[i] && by[j] <= by[i] &&
            by[i] <= ey[j]) {
          intersect[i][j] = intersect[j][i] = {bx[j], by[i]};
          v.emplace_back(bx[j], j);
        }
      }
      sort(v.begin(), v.end());
      if (!v.empty()) {
        for (int j = 0; j < static_cast<int>(v.size()) - 1; ++j)
          fwdlr(i, v[j].second, i, v[j + 1].second);
        fwdlr(i, n + 1, i, v[0].second);
        fwdlr(i, v.back().second, i, n + 2);
      } else {
        fwdlr(i, n + 1, i, n + 2);
      }
    }
  }

  vector<tuple<int, int, int>> path;
  ll total_dist = 0;
  for (;;) {
    path.emplace_back(sx, sy, dir);
    if (path.size() > 1 && path[0] == path.back()) break;
    auto [u1, v1] = intersect[sx][sy];
    auto [nxtx, nxty] = fwd[sx][sy][dir];
    auto [u2, v2] = intersect[nxtx][nxty];
    total_dist += abs(u1 - u2) + abs(v1 - v2);
    if (nxty == n + 1 || nxty == n + 2) {
      dir = (dir + 2) % 4;
    } else {
      dir = (dir + 1) % 4;
    }
    sx = nxtx, sy = nxty;
  }
  t %= total_dist;

  for (int i = 0; i < static_cast<int>(path.size()) - 1; ++i) {
    auto [u1, v1] = intersect[get<0>(path[i])][get<1>(path[i])];
    auto [u2, v2] = intersect[get<0>(path[i + 1])][get<1>(path[i + 1])];
    int d = abs(u1 - u2) + abs(v1 - v2);
    if (t > d) {
      t -= d;
    } else {
      if (u1 == u2) {
        cout << u1 << " " << (v1 < v2 ? v1 + t : v1 - t) << "\n";
      } else {
        cout << (u1 < u2 ? u1 + t : u1 - t) << " " << v1 << "\n";
      }
      break;
    }
  }

  return 0;
}
