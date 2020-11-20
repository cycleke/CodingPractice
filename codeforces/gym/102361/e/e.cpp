#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>
#define N 2000000
#define INF 4000000
#define M 4000000
#define pot(x, y, flag) ((x - 1) * m + y + flag * (n * m))

#define DEBUG printf("Passed [%s] in LINE %d\n", __FUNCTION__, __LINE__)

using namespace std;

inline int read() {
  int num = 0, k = 1;
  char ch = getchar();
  while (ch > '9' || ch < '0') {
    if (ch == '-') k = -1;
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9') {
    num *= 10;
    num += ch - 48;
    ch = getchar();
  }
  return num * k;
}

struct Edge {
  int link, next, rest, from;
} ed[2 * M + 5];

int n, m, son[N + 5], ecnt = 0, level[N + 5], a, b, tot;
char s[N + 5];
void add(int u, int v, int w) {
  // printf("addEdge %d %d\n", u, v);
  ed[++ecnt].link = v, ed[ecnt].next = son[u], son[u] = ecnt, ed[ecnt].from = u,
  ed[ecnt].rest = w;
  ed[++ecnt].link = u, ed[ecnt].next = son[v], son[v] = ecnt, ed[ecnt].from = v,
  ed[ecnt].rest = 0;
}
bool bfs(int s, int t) {
  queue<int> q;
  q.push(s);
  for (int i = 1; i <= tot; i++) level[i] = 0;
  level[s] = 1;
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (int i = son[u], v = ed[i].link; i; i = ed[i].next, v = ed[i].link)
      if (!level[v] && ed[i].rest) {
        level[v] = level[u] + 1;
        q.push(v);
      }
  }
  return level[t];
}
int dfs(int u, int flow, int t) {
  if (u == t) return flow;
  int tmp = flow;
  for (int i = son[u], v = ed[i].link; i; i = ed[i].next, v = ed[i].link)
    if (level[u] + 1 == level[v] && ed[i].rest) {
      int a = dfs(v, min(flow, ed[i].rest), t);
      if (!a) continue;
      flow -= a;
      ed[i].rest -= a;
      ed[(i - 1 ^ 1) + 1].rest += a;
      if (!flow) return tmp;
    }
  if (tmp == flow) {
    level[u] = -1;
    return 0;
  }
  return tmp - flow;
}
int Dinic(int s, int t) {
  int ans = 0;
  while (bfs(s, t)) ans += dfs(s, INF, t);
  return ans;
}
int mp[200][200];
bool check(int x, int y) {
  if (x < 1 || y < 1 || x > n || y > m || mp[x][y]) return 0;
  return 1;
}
void work() {
  scanf("%d%d%d%d", &n, &m, &a, &b);
  tot = pot(n, m, 1) + 2;
  ecnt = 0;
  for (int i = 1; i <= tot; i++) son[i] = 0;
  for (int i = 1; i <= n; i++) {
    scanf("%s", s);
    for (int j = 1; j <= m; j++) mp[i][j] = s[j - 1] - '0';
  }
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++)
      if (!mp[i][j]) {
        if (check(i - 1, j)) add(pot(i, j, 0), pot(i - 1, j, 0), 1);
        if (check(i, j - 1)) add(pot(i, j, 1), pot(i, j - 1, 1), 1);
        if (check(i + 1, j)) add(pot(i, j, 0), pot(i + 1, j, 0), 1);
        if (check(i, j + 1)) add(pot(i, j, 1), pot(i, j + 1, 1), 1);
        add(pot(i, j, 0), pot(i, j, 1), 1);
        add(pot(i, j, 1), pot(i, j, 0), 1);
      }
  for (int i = 1; i <= a; i++) {
    int x;
    scanf("%d", &x);
    if (!mp[1][x]) add(tot - 1, pot(1, x, 0), 1);
  }
  for (int i = 1; i <= b; i++) {
    int x;
    scanf("%d", &x);
    if (!mp[n][x]) add(pot(n, x, 0), tot, 1);
  }
  if (Dinic(tot - 1, tot) == a)
    puts("Yes");
  else
    puts("No");
}
int main() {
  int T;
  scanf("%d", &T);
  while (T--) work();
  return 0;
}
