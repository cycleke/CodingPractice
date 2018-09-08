#include <cstdio>

int main() {
  int k, n = 1;
  scanf("%d", &k);
  long double sum = 0;
  while (true) {
    sum += 1.0 / n;
    if (sum > k) break;
    n += 1;
  }
  printf("%d\n", n);
  return 0;
}
