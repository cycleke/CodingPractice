#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-9;

int sign(double x) { return fabs(x) < EPS ? 0 : (x < 0 ? -1 : 1); }

struct Vector {
  double x, y;

  Vector(double x = 0, double y = 0) : x(x), y(y) {}
  Vector operator-(const Vector &other) const {
    return Vector(x - other.x, y - other.y);
  }
  Vector operator+(const Vector &other) const {
    return Vector(x + other.x, y + other.y);
  }
  Vector operator*(const double &rate) const {
    return Vector(x * rate, y * rate);
  }
  double dot(const Vector &other) const { return x * other.x + y * other.y; }
  double det(const Vector &other) const { return x * other.y - y * other.x; }
  double len() const { return hypot(x, y); }
};

struct Segment {
  Vector s, t;

  Segment() {}
  Segment(Vector s, Vector t) : s(s), t(t) {}
  bool onSegment(const Vector &p) const {
    Vector ps = s - p, pt = t - p;
    return sign(ps.det(pt)) == 0 && sign(ps.dot(pt)) <= 0;
  }

  Vector inter(const Segment &other) const {
    Vector p1 = t - s, p2 = other.t - s;
    if (sign(p1.det(p2)) == 0) return Vector(-1e9, 0);
    double area1 = fabs(p1.det(other.s - s));
    double area2 = fabs(p1.det(other.t - s));
    double x = (area1 * other.t.x + area2 * other.s.x) / (area1 + area2);
    double y = (area1 * other.t.y + area2 * other.s.y) / (area1 + area2);
    return Vector(x, y);
  }
};

double area(Vector a, Vector b, Vector c) { return fabs((a - c).det(a - b)); }

void gao(Vector a, Vector b, Vector c, Vector p) {
  if (sign((p - a).len() - (p - b).len()) > 0) swap(a, b);
  // cout << a.x << " " << a.y << "\n";
  // cout << b.x << " " << b.y << "\n";
  // cout << c.x << " " << c.y << "\n";
  double l = 0, r = 1;
  Vector cb = c - b, q;
  for (int step = 0; step < 200 && sign(r - l); ++step) {
    double mid = (l + r) / 2;
    q = b + cb * mid;
    // cerr << "# " << r << " " << area(a, p, q) << " " << area(a, q, c) << " "
    // << area(p, q, b) << "\n";
    if (sign(area(a, p, q) + area(a, q, c) - area(p, q, b)) <= 0) {
      r = mid;
    } else {
      l = mid;
    }
  }
  cout << q.x << " " << q.y << "\n";
}

void solve() {
  Vector a, b, c, p;
  cin >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y >> p.x >> p.y;
  Segment ab(a, b), ac(a, c), bc(b, c);
  if (ab.onSegment(p)) {
    gao(a, b, c, p);
  } else if (ac.onSegment(p)) {
    gao(a, c, b, p);
  } else if (bc.onSegment(p)) {
    gao(b, c, a, p);
  } else {
    cout << "-1\n";
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
  cout << fixed << setprecision(10);

  int o_o;
  for (cin >> o_o; o_o; --o_o) solve();

  return 0;
}
