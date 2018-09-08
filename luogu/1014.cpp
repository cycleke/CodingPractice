#include <cstdio>

int main() {
  long long l, r, m, n, a;
  scanf("%lld", &n);
  l = 1, r = n;
  while (l < r) {
    m = (l + r) / 2;
    if (m * (m + 1) / 2 < n) l = m + 1;
    else r = m;
  }
  a = n - l * (l - 1) / 2;
  if (l & 1) printf("%lld/%lld\n", l + 1 - a, a);
  else printf("%lld/%lld\n", a, l + 1 - a);
  return 0;
}
