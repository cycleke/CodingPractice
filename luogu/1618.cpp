#include <cstdio>

#define MARK(x) {                               \
    int d[] = {x % 10, x / 10 % 10, x / 100};   \
    for (int i = 0; i < 3; i++) {               \
      mark ^= 1 << d[i];                        \
    }                                           \
  }

int main() {
  int A, B, C;
  scanf("%d%d%d", &A, &B, &C);
  bool hava_answer = false;
  for (int a = 123; a <= 987; a++) {
    if (a % A) continue;
    int mark = 0;
    int one = a / A;
    int b = B * one;
    int c = C * one;
    MARK(a);
    MARK(b);
    MARK(c);
    if (mark == 1022) {
      hava_answer = true;
      printf("%d %d %d\n", a, b, c);
    }
  }
  if (!hava_answer) puts("No!!!");
  return 0;
}
