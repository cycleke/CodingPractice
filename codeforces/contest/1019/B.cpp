#include <cstdio>

int n;

int React(int x) {
  printf("? %d\n? %d\n", x, x + n / 2);
  fflush(stdout);
  static int a, b;
  scanf("%d%d", &a, &b);
  if (a == b) return -1;
  return a < b ? 1 : 0;
}

int main() {
  scanf("%d", &n);
  int start = React(1);
  int left = 0, right = n / 2;
  while (right - left > 1) {
    int middle = (left + right) / 2;
    int temp = React(middle + 1);
    if (temp == -1) {
      printf("! %d\n", middle + 1);
      return 0;
    }
    if (temp == start) left = middle;
    else right = middle;
  }
  puts("! -1");
  return 0;
}
