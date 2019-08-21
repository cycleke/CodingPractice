#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e4 + 5;

double p[MAXN];

int main(int argc, char *argv[]) {

  int o_o, n;
  for (scanf("%d", &o_o); o_o; --o_o) {
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) scanf("%lf", p + i);
    sort(p, p + n);
    double p0 = 1.0, p1 = 0.0;
    for (int i = n - 1; ~i; --i) {
      p1 = p0 * p[i] + p1 * (1 - p[i]);
      p0 *= 1 - p[i];
      if (p1 >= p0) break;
    }
    printf("%.12lf\n", p1);
  }

  return 0;
}
