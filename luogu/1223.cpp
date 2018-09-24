#include <cstdio>
#include <algorithm>

std::pair<int, int> p[1000];

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &p[i].first);
    p[i].second = i + 1;
  }
  std::sort(p, p + n);
  long long sum = 0;
  for (int i = 0; i < n; i++) {
    printf("%d ", p[i].second);
    sum += p[i].first * (n - i - 1);
  }
  printf("\n%.2lf", double(sum) / n);
  return 0;
}
