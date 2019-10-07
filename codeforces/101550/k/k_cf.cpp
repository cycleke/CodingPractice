// passed on codeforces c++17
#include <bits/stdc++.h>
#define double long double
using namespace std;

const int MAXN = 1e5 + 5;

int n, m;
double ts[MAXN], tl[MAXN], tt[MAXN * 2];
int xs[MAXN], ys[MAXN], xl[MAXN], yl[MAXN];

inline double dist(double x, double y) { return sqrtl(x * x + y * y); }
inline double sqr(double x) { return x * x; }
inline double gao(double x1, double y1, double x2, double y2, double x3,
                  double y3, double x4, double y4) {
  double d1 = dist(x1 - x2, y1 - y2);
  double d2 = dist(x3 - x4, y3 - y4);
  double rx1 = (x2 - x1) / d1, ry1 = (y2 - y1) / d1;
  double rx2 = (x4 - x3) / d2, ry2 = (y4 - y3) / d2;

  double a = sqr(rx1 - rx2) + sqr(ry1 - ry2);
  double b = 2 * ((x1 - x3) * (rx1 - rx2) + (y1 - y3) * (ry1 - ry2));
  double c = sqr(x1 - x3) + sqr(y1 - y3);

  double t0 = -b / (2 * a);

  static auto cal = [&](const double &t) {
    return sqrtl(a * t * t + b * t + c);
  };

  if (t0 >= 0 && t0 <= d1 && t0 <= d2) return cal(t0);
  return min(cal(0), cal(min(d1, d2)));
}

inline void walk(int *x, int *y, int i, double t, double &ex, double &ey) {
  if (fabs(t) < 1e-9) {
    ex = x[i], ey = y[i];
    return;
  }
  double d = dist(x[i] - x[i + 1], y[i] - y[i + 1]);
  double rx = (x[i + 1] - x[i]) / d;
  double ry = (y[i + 1] - y[i]) / d;
  ex = x[i] + rx * t, ey = y[i] + ry * t;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout << fixed << setprecision(10);

  cin >> n;
  for (int i = 0; i < n; ++i) { cin >> xs[i] >> ys[i]; }

  cin >> m;
  for (int i = 0; i < m; ++i) cin >> xl[i] >> yl[i];

  int tc = 1;
  ts[0] = tl[0] = tt[0] = 0;
  for (int i = 1; i < n; ++i) {
    ts[i] = ts[i - 1] + dist(xs[i] - xs[i - 1], ys[i] - ys[i - 1]);
    tt[tc++] = ts[i];
  }
  for (int i = 1; i < m; ++i) {
    tl[i] = tl[i - 1] + dist(xl[i] - xl[i - 1], yl[i] - yl[i - 1]);
    tt[tc++] = tl[i];
  }

  sort(tt, tt + tc);
  tc = unique(tt, tt + tc) - tt;

  double cxs, cys, cxl, cyl;
  double pxs = *xs, pys = *ys, pxl = *xl, pyl = *yl;
  double ans = dist(pxs - pxl, pys - pyl);
  for (int i = 1, i1 = 0, i2 = 0; i < tc; ++i) {
    while (i1 + 1 < n && ts[i1 + 1] <= tt[i]) ++i1;
    while (i2 + 1 < m && tl[i2 + 1] <= tt[i]) ++i2;
    walk(xs, ys, i1, tt[i] - ts[i1], cxs, cys);
    walk(xl, yl, i2, tt[i] - tl[i2], cxl, cyl);
    ans = min(ans, gao(pxs, pys, cxs, cys, pxl, pyl, cxl, cyl));
    pxs = cxs, pys = cys, pxl = cxl, pyl = cyl;
    if (i1 == n - 1 || i2 == m - 1) break;
  }
  cout << ans << '\n';
  return 0;
}
