#include <cstdio>
#include <algorithm>
using namespace std;

int max_jump[500], x[1000], y[1000], f[1000];

struct edge {
  int u, v, w;
  edge() {}
  edge(int _u, int _v, int _w) :
    u(_u), v(_v), w(_w) {}
  bool operator < (const edge &x) const {
    return this->w < x.w;
  }
}e[500000];

int dist(int u, int v) {
  static auto pow2 = [&](const int &x) {
    return x * x;
  };
  return pow2(x[u] - x[v]) + pow2(y[u] - y[v]);
}

int gFather(int x) {
  return x == f[x] ? x : f[x] = gFather(f[x]);
}

int main() {
  int m, n;
  scanf("%d", &m);
  for (int i = 0; i < m; i++) {
    scanf("%d", max_jump + i);
    max_jump[i] *= max_jump[i];
  }
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    f[i] = i;
    scanf("%d%d", x + i, y + i);
  }
  int cnt = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < i; j++) {
      e[cnt++] = edge(i, j, dist(i, j));
    }
  }
  sort(e, e + cnt);
  int it = 0, cnt_e = 0;
  for (; it < cnt; it++) {
    int u = e[it].u, v = e[it].v;
    if (gFather(u) != gFather(v)) {
      cnt_e++;
      f[gFather(u)] = gFather(v);
      if (cnt_e == n - 1) break;
    }
  }
  int ans = 0;
  for (int i = 0; i < m; i++)
    if (max_jump[i] >= e[it].w) ans++;
  printf("%d", ans);
  return 0;
}
