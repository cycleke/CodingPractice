#include <cstdio>

int main() {
  int a, b, c, d;
  scanf("%d%d%d%d", &a, &b, &c, &d);
  if (b <= d) {
    printf("%d %d\n", c - a, d - b);
  } else {
    printf("%d %d\n", c - a - 1, b - d + 60);
  }
  return 0;
}
