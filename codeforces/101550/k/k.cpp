#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 5;
const double EPS = 1e-20;

struct Point {
  double x, y;

  Point(double x = 0, double y = 0) : x(x), y(y) {}
  double dist() const { return sqrt(x * x + y * y); }
  double dist2() const { return x * x + y * y; }
  Point unit() const {
    double d = dist();
    return d > EPS ? Point(x / d, y / d) : *this;
  }
  Point operator+(const Point &b) const { return Point(x + b.x, y + b.y); }
  Point operator-(const Point &b) const { return Point(x - b.x, y - b.y); }
  Point operator/(const double &b) const { return Point(x / b, y / b); }
  Point operator*(const double &b) const { return Point(x * b, y * b); }

  double dot(const Point &b) const { return x * b.x + y * b.y; }
} a[MAXN], b[MAXN];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout << fixed << setprecision(11);

  int n, m;
  cin >> n;
  for (int i = 0; i < n; ++i) cin >> a[i].x >> a[i].y;
  a[n] = a[n - 1];
  cin >> m;
  for (int i = 0; i < m; ++i) cin >> b[i].x >> b[i].y;
  b[m] = b[m - 1];

  Point ca = a[0], cb = b[0];
  double ans = (ca - cb).dist();
  for (int nxta = 1, nxtb = 1; nxta < n && nxtb < m;) {
    Point ra = a[nxta] - ca;
    Point rb = b[nxtb] - cb;
    double da = ra.dist(), db = rb.dist();
    double d = min(da, db);

    ra = ra.unit(), rb = rb.unit();
    double a = (ra - rb).dist2();
    double b = 2 * (ca - cb).dot(ra - rb);
    double c = (ca - cb).dist2();
    double t0 = -b / (2 * a);

    static auto cal = [&](const double &t) { return sqrt(a * t * t + b * t + c); };
    if (t0 >= 0 && t0 <= d) {
      ans = min(ans, cal(t0));
    } else {
      ans = min(ans, min(cal(0), cal(d)));
    }

    ca = (fabs(d - da) < EPS) ? ::a[nxta++] : (ca + ra * d);
    cb = (fabs(d - db) < EPS) ? ::b[nxtb++] : (cb + rb * d);
  }
  cout << ans << '\n';
  return 0;
}
