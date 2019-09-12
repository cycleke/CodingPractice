#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-12;
const double PI = acos(-1.0);

inline double cal_v(double x) {
  double t = acos(1 - x);
  double v = sin(t) - sin(t) * sin(t) * sin(t) / 3 - t * cos(t);
  return v * 2 / x;
}

inline double ract(double a, double x) { return (x + sin(2 * x) / 2) * a / 2; }

inline double area(double a, double x) {
  return 2 * (ract(a, PI / 2) - ract(a, asin(x / a)));
}

void solve() {
  double d;
  cin >> d;
  if (d == 0) {
    cout << .0 << '\n';
    return;
  }
  if (d > 1) {
    double h = 2 * d - 2;
    double a = sqrt(4 + (2 - h) * (2 - h)) / 2;
    cout << PI * a << '\n';
    return;
  }
  double l = 0, r = 2, v = PI * d;
  for (int step = 0; step < 100; ++step) {
    double mid = (l + r) / 2;
    if (cal_v(mid) > v + EPS) {
      r = mid;
    } else {
      l = mid;
    }
  }
  int sign = l < 1 ? -1 : 1;
  double len = sqrt(l * l + 4);
  double h = sqrt(2 * l - l * l);
  double a = len / (1 + sign * sqrt(1 - h * h));
  double x = a - len;
  cout << area(a, x) << '\n';
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout << fixed << setprecision(5);

  int o_o;
  for (cin >> o_o; o_o; --o_o) solve();
  return 0;
}
