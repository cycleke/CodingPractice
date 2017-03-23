#include <map>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
#define N 100005
struct edge {
  int t, v;
  edge *n;
} me[N << 1], *ce = me, *g[N];
#define adde(a, b, c) (*ce = (edge){b, c, g[a]}, g[a] = ce++)
typedef int arr[N];
arr dep, dis, siz, son, tp, fa, dq, in;
int dfn, n, K;
void d1(int u) {
  siz[u] = 1;
  for (edge *it = g[u]; it; it = it->n)
    if (it->t ^ fa[u]) {
      fa[it->t] = u;
      dep[it->t] = dep[u] + 1;
      dis[it->t] = dis[u] + it->v;
      d1(it->t);
      siz[u] += siz[it->t];
      if (siz[it->t] > siz[son[u]])
        son[u] = it->t;
    }
}
void d2(int u, int anc) {
  dq[in[u] = ++dfn] = u;
  tp[u] = anc;
  if (son[u]) d2(son[u], anc);
  for (edge *it = g[u]; it; it = it->n)
    if (!tp[it->t]) d2(it->t, it->t);
}
int Lca(int u, int v) {
  while (tp[u] ^ tp[v]) dep[tp[u]] < dep[tp[v]] ? v = fa[tp[v]] : u = fa[tp[u]];
  return dep[u] < dep[v] ? u : v;
}
int disc(int u, int v) {
  return dis[u] + dis[v] - (dis[Lca(u, v)] << 1);
}
int jump(int u, int d) {
  while (dep[tp[u]] > d) u = fa[tp[u]];
  return dq[in[u] - (dep[u] - d)];
}
int Getadj(int c, int u) {
  return (Lca(u, c) ^ c) ? fa[c] : jump(u, dep[c] + 1);
}
arr f, Dis;
int SZ, rt;
bool vis[N];
inline void cmax(int &a, const int &b) {
  if (a < b) a = b;
}
typedef vector<int> vii;
struct node {
  int pre;
  vii vec;
  map<int, vii> adj_vec;
} dc[N];
void grt(int u, int fa) {
  f[u] = 0, siz[u] = 1;
  for (edge *it = g[u]; it; it = it->n)
    if (!vis[it->t] && (it->t ^ fa)) {
      grt(it->t, u);
      cmax(f[u], siz[it->t]);
      siz[u] += siz[it->t];
    }
  cmax(f[u], SZ - siz[u]);
  if (f[u] < f[rt]) rt = u;
}
void dfs(int u, int fa, vii &v1, vii &v2) {
  v1.push_back(Dis[u]);
  v2.push_back(Dis[u]);
  siz[u] = 1;
  for (edge *it = g[u]; it; it = it ->n)
    if ((it->t ^ fa) && !vis[it->t]) {
      Dis[it->t] = Dis[u] + it->v;
      dfs(it->t, u, v1, v2);
      siz[u] += siz[it->t];
    }
}
void solve(int u) {
  vis[u] = 1;
  dc[u].vec.push_back(0);
  for (edge *it = g[u]; it; it = it->n)
    if (!vis[it->t]) {
      Dis[it->t] = it->v;
      vii &v0 = dc[u].adj_vec[it->t];
      dfs(it->t, u, dc[u].vec, v0);
      sort(v0.begin(), v0.end());
    }
  sort(dc[u].vec.begin(), dc[u].vec.end());
  for (edge *it = g[u]; it; it = it->n)
    if (!vis[it->t]){
      f[rt = 0] = SZ = siz[it->t];
      grt(it->t, u);
      dc[rt].pre = u;
      solve(rt);
    }
}
int GetLess(vii &v, const int &x) {
  if (v.empty() || x < *v.begin())
    return 0;
  if (x >= *v.rbegin())
    return v.size();
  return upper_bound(v.begin(), v.end(), x) - v.begin();
}
int cal(int u, const int &v, const int &d) {
  int ret = 0;
  if (dc[u].pre)
    ret = cal(dc[u].pre, v, d);
  if (ret > K)
    return ret;
  vii &v1 = dc[u].vec;
  int x = disc(u, v);
  ret += GetLess(v1, d - x);
  if (u ^ v) {
    int t = Getadj(u, v);
    ret -= GetLess(dc[u].adj_vec[t], d - x);
  }
  return ret;
}
int R;
void GetAns(int u) {
  int l = 0, r = R, mid;
  while (l <= r)
    if (cal(u, u, mid = (l + r) >> 1) <= K)
      l = mid + 1;
    else
      r = mid - 1;
  printf("%d\n", r + 1);
}
int main() {
  scanf("%*s%d%d", &n, &K);
  int u, v, w;
  for (int i = 1; i < n; ++i) {
    scanf("%d%d%d", &u, &v, &w);
    adde(u, v, w);
    adde(v, u, w);
    R += w;
  }
  d1(1);
  d2(1, 1);
  f[rt = 0] = n;
  SZ = n;
  rt = 0;
  grt(1, 0);
  solve(rt);
  for (int i = 1; i <= n; ++i) GetAns(i);
  return 0;
}
