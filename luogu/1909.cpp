#include <cmath>
#include <cstdio>

int main() {
  int n, min_cost = 0x3f3f3f3f;
  scanf("%d", &n);
  for (int i = 0; i < 3; i++) {
    int a, b, cost;
    scanf("%d%d", &a, &b);
    cost = ceil((double)n / a) * b;
    if (cost < min_cost) min_cost = cost;
  }
  printf("%d\n", min_cost);
  return 0;
}
