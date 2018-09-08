#include <cstdio>

#define MARK(x) {                               \
    int d[] = {x % 10, x / 10 % 10, x / 100};   \
    for (int i = 0; i < 3; i++) {               \
      mark ^= 1 << d[i];                        \
    }                                           \
  }

int main() {
  for (int i = 123; i <= 327; i++) {
    int mark = 0;
    int a = i;
    int b = i * 2;
    int c = i * 3;
    MARK(a);
    MARK(b);
    MARK(c);
    if (mark == 1022) printf("%d %d %d\n", a, b, c);
  }
  return 0;
}
