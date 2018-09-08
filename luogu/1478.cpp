#include <cstdio>

int main() {
  int n, s, a, b;
  scanf("%d%d%d%d", &n, &s, &a, &b);
  int count[101];
  for (int i = 0; i < 101; i++) {
    count[i] = 0;
  }
  for (int i = 0; i < n; i++) {
    int x, y;
    scanf("%d%d", &x, &y);
    if (x > a + b) continue;
    count[y]++;
  }
  int ans = 0;
  for (int i = 0; i < 101; i++) {
    if (count[i] == 0) continue;
    if (i * count[i] < s) {
      s -= i * count[i];
      ans += count[i];
    } else {
      ans += s / i;
      break;
    }
  }
  printf("%d\n", ans);
  return 0;
}
