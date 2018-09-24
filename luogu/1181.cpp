#include <cstdio>

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  int sum = 0, ans = 1;
  for (int i = 0; i < n; i++) {
    int x;
    scanf("%d", &x);
    if (sum + x <= m) {
      sum += x;
    } else {
      sum = x;
      ans++;
    }
  }
  printf("%d", ans);
  return 0;
}
