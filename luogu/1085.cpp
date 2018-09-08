#include <cstdio>

int main() {
  int day = 0, max_time = 0;
  for (int i = 1; i < 8; i++) {
    int a, b;
    scanf("%d%d", &a, &b);
    if (a + b > max_time) {
      day = i;
      max_time = a + b;
    }
  }
  printf("%d\n", day);
  return 0;
}
