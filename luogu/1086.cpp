#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

pair<int, pair<int, int>> a[400];
int main() {
  int m, n, k, count = 0;
  scanf("%d%d%d", &m, &n, &k);
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      int p;
      scanf("%d", &p);
      a[count++] = make_pair(-p, make_pair(i + 1, j + 1));
    }
  }
  sort(a, a + count);
  if (k < a[0].second.first * 2 + 1) {
    puts("0");
  } else {
    int ans = a[0].first;
    k -= a[0].second.first + 1;
    int x = a[0].second.first;
    int y = a[0].second.second;
    for (int i = 1; i < count; i++) {
      if (a[0].first == 0) break;
      int _x = a[i].second.first;
      int _y = a[i].second.second;
      //printf("%d %d %d\n", x, y, k);
      if (abs(x - _x) + abs(y - _y) + _x + 1 <= k) {
        ans += a[i].first;
        k -= abs(x - _x) + abs(y - _y) + 1;
        x = _x, y = _y;
      } else
        break;
    }
    printf("%d\n", -ans);
  }
  return 0;
}
