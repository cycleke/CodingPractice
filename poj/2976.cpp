#include <cstdio>
#include <algorithm>

const int MAXN = 1e3 + 5;

int n, k, a[MAXN], b[MAXN];

bool gao(double x) {
  static double c[MAXN];
  for (int i = 0; i < n; ++i) c[i] = a[i] - x * b[i];
  std::sort(c, c + n);

  double s = 0;
  for (int i = k; i < n; ++i) s += c[i];
  return s > 0;
}

int main() {
  while (scanf("%d %d", &n, &k) == 2) {
    if (n == 0 && k == 0) break;
    for (int i = 0; i < n; ++i) scanf("%d", a + i);
    for (int i = 0; i < n; ++i) scanf("%d", b + i);

    double l = 0, r = 1;
    for (int step = 0; step < 100; ++step) {
      double mid = (l + r) * 0.5;
      (gao(mid) ? l : r) = mid;
    }
    printf("%.0f\n", l * 100);
  }
  return 0;
}
