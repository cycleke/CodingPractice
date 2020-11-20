#include <bits/stdc++.h>
using namespace std;

typedef pair<double, double> pdd;

double dist(const pdd &a, const pdd &b) {
  return sqrt(pow(a.first - b.first, 2) + pow(a.second - b.second, 2));
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  double a, b, c;
  pdd p1, p2;
  cin >> a >> b >> c;
  // a * x + b * y + c = 0
  cin >> p1.first >> p1.second;
  cin >> p2.first >> p2.second;
  double ans = fabs(p1.first - p2.first) + fabs(p1.second - p2.second);

  auto gen = [a, b, c](pdd p) {
    double x = p.first, y = p.second;
    return vector<pdd>{pdd(x, -(x * a + c) / b), pdd(-(y * b + c) / a, y)};
  };
  if (fabs(a * b) > 1e-6) {
    auto l1 = gen(p1), l2 = gen(p2);
    for (pdd &x : l1)
      for (pdd &y : l2) {
        ans = min(ans, dist(p1, x) + dist(x, y) + dist(y, p2));
      }
  }
  cout << fixed << ans << endl;
  return 0;
}
