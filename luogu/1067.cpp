#include <cstdio>

int main() {
  int n, c;
  scanf("%d", &n);
  for (int i = n; ~i; i--) {
    scanf("%d", &c);
    if (c == 0) continue;
    if (i < n && c > 0) putchar('+');
    if (c > 1 || c < -1 || !i) printf("%d", c);
    if (c == -1 && i) putchar('-');
    if (i > 1) printf("x^%d", i);
    if (i == 1) putchar('x');
  }
  return 0;
}
