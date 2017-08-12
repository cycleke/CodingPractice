#include <cstdio>

#define MAXN 1005

int d[MAXN], s[MAXN];

inline double max(const double &a, const double &b) {
  return a < b ? b : a;
}

int main() {
  int n, t;
  while (scanf("%d %d", &n, &t) != EOF) {
    double l = -1e10, r = 1e10;
    for (int i = 0; i < n; ++i) {
      scanf("%d %d", d + i, s + i);
      l = max(l , s[i] * -1.0);
    }
    for (int _ = 0; _ < 200; ++_) {
      double totle = 0;
      double mid = (l + r) * 0.5;
      for (int i = 0; i < n; ++i) {
        totle += d[i] / (s[i] + mid);
      }
      if (totle > t) {
        l = mid;
      } else {
        r = mid;
      }
    }
    printf("%.7lf\n", (l + r) * 0.5);
  }
  return 0;
}