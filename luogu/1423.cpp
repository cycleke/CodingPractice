#include <cmath>
#include <cstdio>

int main() {
  double x;
  scanf("%lf", &x);
  printf("%d\n", (int)ceil(log(1 - x / 100) / log(0.98)));
  return 0;
}
