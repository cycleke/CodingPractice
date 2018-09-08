#include <cstdio>

int main() {
  int n, x;
  scanf("%d%d", &n, &x);
  int base = 1, count = 0;
  while (base <= n) {
    int a = n / (base * 10);
    int b = n / base % 10;
    int c = n % base;
    if (x) {
      if (b > x) count += (a + 1) * base;
      else if (b < x) count += a * base;
      else count += a * base + c + 1;
    } else {
      if (b) count += a * base;
      else count += (a - 1) * base + c + 1;
    }
    base *= 10;
  }
  printf("%d\n", count);
  return 0;
}
