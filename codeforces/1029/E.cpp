#include <cstdio>
#include <vector>
using namespace std;

#define MAXN 200003
vector<int> g[MAXN];
int dep[MAXN], d[MAXN][3];

void Dfs(int u, int from) {
  dep[u] = dep[from] + 1;
  d[u][0] = 0;
  d[u][1] = g[u].size() == 1 ? 1e6 : 0;
  d[u][2] = 1;
  int mininum = 1e9;
  for (int v : g[u]) {
    if (v == from) continue;
    Dfs(v, u);
    d[u][0] += d[v][1];
    d[u][1] += min(d[v][1], d[v][2]);
    mininum = min(mininum, d[v][2] - d[v][1]);
    d[u][2] += min(d[v][0], min(d[v][1], d[v][2]));
    for (int i = 0; i < 3; i++) if (d[u][i] > 1e6) d[u][i] = 1e6;
  }
  if (mininum > 0) d[u][1] += mininum;
  for (int i = 0; i < 3; i++) if (d[u][i] > 1e6) d[u][i] = 1e6;
}

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 1; i < n; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    g[u].push_back(v);
    g[v].push_back(u);
  }
  Dfs(1, 0);
  int ans = 0;
  for (int i = 1; i <= n; i++) {
    if (dep[i] != 3) continue;
    ans += min(d[i][0], min(d[i][1], d[i][2]));
  }
  printf("%d\n", ans);
  return 0;
}
