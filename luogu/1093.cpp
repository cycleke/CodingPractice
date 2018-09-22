#include <cstdio>
#include <algorithm>
using namespace std;

pair<int, pair<int, int> > p[300];

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    int a, b, c;
    scanf("%d%d%d", &a, &b, &c);
    p[i] = make_pair(-(a + b + c), make_pair(-a, i + 1));
  }
  sort(p, p + n);
  for (int i = 0; i < 5; i++) {
    printf("%d %d\n", p[i].second.second, -p[i].first);
  }
