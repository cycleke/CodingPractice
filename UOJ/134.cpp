#include <bits/stdc++.h>
using namespace std;

const int maxn = 5000;
int connection[maxn][maxn];
int a[maxn], b[maxn], mark[maxn], ans[maxn];
int mark_clock;

struct Edge {
  int to;
  Edge *next;
} *g[maxn], edge_pool[maxn * 2];

void dfs(int u) {
  mark[u] = mark_clock;
  for (Edge *it = g[u]; it != NULL; it = it->next)
    if (mark[it->to] != mark_clock && connection[u][it->to] > 0) dfs(it->to);
}

void AddEdge(int x, int y) {
  static Edge *cedge = edge_pool;
  *cedge = (Edge) {y, g[x]};
  g[x] = cedge++;
  connection[x][y]++;
}

int main() {
  int n, m;
  scanf("%d %d", &n, &m);
  for (int i = 0; i < m; i++) {
    scanf("%d %d %d", a + i, b + i, ans + i);
    a[i]--, b[i]--;
    AddEdge(a[i], b[i]);
    if (ans[i] == 0) {
      AddEdge(b[i], a[i]);
    }
  }
  mark_clock = 0;
  for (int i = 0; i < m; i++) {
    if (ans[i] == 1) {
      ans[i] = 0;
      continue;
    }
    const int &x = a[i], &y = b[i];
    connection[x][y]--;
    mark_clock++;
    dfs(x);
    connection[x][y]++;
    if (mark[y] == mark_clock) {
      ans[i] = 1;
      connection[x][y]--;
    } else {
      ans[i] = 0;
      connection[y][x]--;
    }
  }

  for (int i = 0; i < m; i++)
    puts(ans[i] == 1 ? "1" : "0");

	return 0;
}
