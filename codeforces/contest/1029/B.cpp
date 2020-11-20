#include <cstdio>


int main(int argc, char const *argv[]) {
  int n, a, ans = 0, cur = 0, pre = 0;
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &a);
    if (a > 2 * pre) cur = 1;
    else cur++;
    pre = a;
    if (cur > ans) ans = cur;
  }
  printf("%d", ans);
  return 0;
}
