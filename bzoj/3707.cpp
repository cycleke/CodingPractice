#include <cstdio>
#include <algorithm>
using namespace std;

#define MAXN 1000

pair<double, double> p[MAXN];
int pos[MAXN], id[MAXN];
struct Data {
  double x, y;
  double slope;
} d[MAXN * MAXN];

bool operator < (const Data &a, const Data &b) {
  return a.slope < b.slope;
}

double Calc(int a, int b, int c) {
  double dx1 = p[a].first - p[b].first, dx2 = p[a].first - p[c].first;
  double dy1 = p[a].second - p[b].second, dy2 = p[a].second - p[c].second;
  double s = dx1 * dy2 - dx2 * dy1;
  return (s < 0 ? -s : s) * 0.5;
}

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    id[i] = pos[i] = i;
    scanf("%lf%lf", &p[i].first, &p[i].second);
  }
  sort(p, p + n);
  int total = 0;
  for (int i = 0; i < n; i++)
    for (int j = i + 1; j < n; j++) {
      Data &data = d[total++];
      data.x = i;
      data.y = j;
      data.slope = (p[i].second-p[j].second) / (p[i].first-p[j].first);
    }
  sort(d, d + total);
  double ans = 1e18;
  for (int i = 0; i < total; i++) {
    int x = d[i].x, y = d[i].y;
    if (pos[x] > pos[y]) swap(x, y);
    if (pos[x] > 0) ans = min(ans, Calc(x, y, id[pos[x] - 1]));
    if (pos[y] < n - 1) ans = min(ans, Calc(x, y, id[pos[y] + 1]));
    swap(pos[x], pos[y]);
    swap(id[pos[x]], id[pos[y]]);
  }
  return 0;

}
