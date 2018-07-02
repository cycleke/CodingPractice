#include <cstdio>

int main() {
  int n;
  long long x, y;
  scanf("%d %lld %lld\n", &n, &x, &y);
  int pre = 1, cnt = 0;
  for (int i = 0; i < n; ++i) {
    int x = getchar() - '0';
    if (x == 0 && pre == 1) cnt++;
    pre = x;
  }
  if (cnt == 0) puts("0");
  else {
    long long ans = 1ll << 60;
    for (int i = 0; i < cnt; ++i) {
      long long temp = x * i + y * (cnt - i);
      if (temp < ans) ans = temp;
    }
    printf("%lld\n", ans);
  }
  return 0;
}
