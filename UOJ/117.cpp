#include <bits/stdc++.h>
using namespace std;

const int MAXBUF = 1 << 23 | 1;
char B[MAXBUF], *Si = B, *Ti = B;
inline char getc() {
  if (Si == Ti) Ti = (Si = B) + fread(B, 1, MAXBUF, stdin);
  if (Si == Ti)
    return 0;
  else
    return *Si++;
}
template <class T>
inline void read(T &a) {
  static char c;
  static int fh;
  while (((c = getc()) < '0' || c > '9') && c != '-')
    ;
  if (c == '-')
    fh = -1, a = 0;
  else
    fh = 1, a = c - '0';
  while ((c = getc()) <= '9' && c >= '0') a = (a << 3) + (a << 1) + c - '0';
  if (fh == -1) a = -a;
}
char Buff[MAXBUF], *sti = Buff;
template <class T>
inline void write(T a) {
  if (a == 0) {
    *sti++ = '0';
    return;
  }
  if (a < 0) *sti++ = '-', a = -a;
  static char c[20];
  static int c0;
  c0 = 0;
  while (a) c[c0++] = a % 10 + '0', a /= 10;
  while (c0--) *sti++ = c[c0];
}

const int maxn = 100003;
int in_deg[maxn], out_deg[maxn];
int ans_stack[maxn * 2], *ans_top;
bool vis[maxn * 2];

struct Edge {
  int to, id;
  Edge *next;
} * g[maxn], edge_pool[maxn * 4];

void AddEdge(int u, int v, int id) {
  static Edge *cedge = edge_pool;
  *cedge = (Edge){v, id, g[u]};
  g[u] = cedge++;
  in_deg[v]++;
  out_deg[u]++;
}

void dfs(int u) {
  for (Edge *e = g[u]; e != NULL; e = g[u]) {
    g[u] = e->next;
    if (vis[abs(e->id)]) continue;
    vis[abs(e->id)] = true;
    dfs(e->to);
    *ans_top++ = e->id;
  }
}

int main() {
  int type, n, m;
  read(type);
  read(n);
  read(m);
  int u, v;
  for (int i = 1; i <= m; ++i) {
    read(u);
    read(v);
    AddEdge(u, v, i);
    if (type == 1) {
      AddEdge(v, u, -i);
    }
  }
  if (type == 1) {
    for (int i = 1; i <= n; ++i)
      if ((out_deg[i] & 1) == 1) {
        puts("NO");
        return 0;
      }
  } else if (type == 2) {
    for (int i = 1; i <= n; ++i)
      if (in_deg[i] != out_deg[i]) {
        puts("NO");
        return 0;
      }
  } else {
    puts("DATA ERROR");
    printf("%d %d %d", type, n, m);
    return -1;
  }
  ans_top = ans_stack;
  for (int i = 1; i <= n; ++i)
    if (out_deg[i] != 0) {
      dfs(i);
      break;
    }
  if ((ans_stack + m) != ans_top) {
    puts("NO");
  } else {
    puts("YES");
    while (ans_top > ans_stack) {
      write(*(--ans_top));
      *sti++ = ' ';
    }
    fwrite(Buff, 1, sti - Buff, stdout);
  }
  return 0;
}
