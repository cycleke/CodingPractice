#include <cstdio>
#include <algorithm>

using namespace std;

#define MAXN 2000

pair<int, int> p[MAXN];
struct Data {
  int x, y;
  double slope;

  bool operator < (const Data &x) const {
    return slope < x.slope;
  }
} d[MAXN * MAXN];
int pos[MAXN], id[MAXN];

long long Calc(int a, int b, int c) {
  long long dx1 = p[a].first - p[b].first, dx2 = p[a].first - p[c].first;
  long long dy1 = p[a].second - p[b].second, dy2 = p[a].second - p[c].second;
  long long s = dx1 * dy2 - dx2 * dy1;
  return s < 0 ? -s : s;
}

int main() {
  int n;
  long long S;
  scanf("%d%lld", &n, &S);
  S *= 2;
  for (int i = 0; i < n; i++) {
    id[i] = pos[i] = i;
    scanf("%d%d", &p[i].first, &p[i].second);
  }
  sort(p, p + n);
  int total = 0;
  for (int i = 0; i < n; i++)
    for (int j = i + 1; j < n; j++) {
      Data &data = d[total++];
      data.x = i;
      data.y = j;
      data.slope = (double)(p[j].second-p[i].second) / (p[j].first-p[i].first);
    }
  sort(d, d + total);
  for (int i = 0; i < total; i++) {
    int x = d[i].x, y = d[i].y;
    if (pos[x] > pos[y]) swap(x, y);
    int left = 0, right = pos[x] - 1, middle;
    while (left <= right) {
      middle = (left + right) / 2;
      long long area = Calc(id[middle], x, y);
      if (area == S) {
        puts("Yes");
        printf("%d %d\n", p[id[middle]].first, p[id[middle]].second);
        printf("%d %d\n", p[x].first, p[x].second);
        printf("%d %d\n", p[y].first, p[y].second);
        return 0;
      } else if (area < S) right = middle - 1;
      else left = middle + 1;
    }
    left = pos[y] + 1, right = n - 1;
    while (left <= right) {
      middle = (left + right) / 2;
      long long area = Calc(id[middle], x, y);
      if (area == S) {
        puts("Yes");
        printf("%d %d\n", p[id[middle]].first, p[id[middle]].second);
        printf("%d %d\n", p[x].first, p[x].second);
        printf("%d %d\n", p[y].first, p[y].second);
        return 0;
      } else if (area < S) right = middle - 1;
      else left = middle + 1;
    }
    swap(pos[x], pos[y]);
    swap(id[pos[x]], id[pos[y]]);
  }
  puts("No");
  return 0;
}
