#include <cstdio>
#include <algorithm>

std::pair<int, int> p[100000];

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    scanf("%d%d", &p[i].second, &p[i].first);
  }
  std::sort(p, p + n);
  int ans = 0, pre = -1;
  for (int i = 0; i < n; i++) {
    if (p[i].second >= pre) {
      ans++;
      pre = p[i].first;
    }
  }
  printf("%d\n", ans);
  return 0;
}
