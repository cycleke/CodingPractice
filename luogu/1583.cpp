#include <cstdio>
#include <algorithm>
using namespace std;

pair<int, int> a[20003];
int e[10];

int main() {
  int n, k;
  scanf("%d%d", &n, &k);
  for (int i = 0; i < 10; i++) {
    scanf("%d", e + i);
  }
  for (int i = 0; i < n; i++) {
    scanf("%d", &a[i].first);
    a[i].second = i + 1;
  }
  auto cmp = [&](const pair<int, int> &a, const pair<int, int> &b) {
               if (a.first == b.first) return a.second < b.second;
               return a.first > b.first;
             };
  sort(a, a + n, cmp);
  for (int i = 0; i < n; i++) {
    a[i].first += e[i % 10];
  }
  sort(a, a + n, cmp);
  for (int i = 0; i < k; i++) {
    printf("%d ", a[i].second);
  }
  return 0;
}
