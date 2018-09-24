#include <cstdio>
#include <algorithm>

int c[201];

int main() {
  int w, n, upper = 0, lower = 201;
  scanf("%d%d", &w, &n);
  for (int i = 0; i < n; i++) {
    int x;
    scanf("%d", &x);
    c[x]++;
    if (x > upper) upper = x;
    if (x < lower) lower = x;
  }
  int ans = 0;
  for (int i = upper; i >= lower; i--) {
    while (c[i]) {
      bool sign = true;
      for (int j = w - i; j >= lower; j--) {
        while (c[j] && c[i] && (i != j || c[i] > 1)) {
          ans++;
          c[i]--;
          c[j]--;
          sign = false;
        }
      }
      if (sign) {
        ans += c[i];
        c[i] = 0;
      }
    }
  }
  printf("%d", ans);
  return 0;
}
