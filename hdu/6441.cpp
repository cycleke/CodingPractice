#include <cstdio>

int main() {
  int _, a, n;
  scanf("%d", &_);
  while (_--) {
    scanf("%d%d", &n, &a);
    if (n > 2 || n == 0) {
      puts("-1 -1");
    } else if (n == 1) {
      printf("1 %d\n", a + 1);
    } else {
      static int s_b[40001], s_c[40001];
      int &_b = s_b[a], &_c = s_c[a];
      if (_b && _c) {
        printf("%d %d\n", _b, _c);
        continue;
      }
      int x = a >> 1;
      if (a & 1) {
        int c = x * x + (x + 1) * (x + 1);
        printf("%d %d\n", _b = c - 1, _c = c);
      } else {
        printf("%d %d\n", _b = x * x - 1, _c = x * x + 1);
      }
    }
  }
  return 0;
}
