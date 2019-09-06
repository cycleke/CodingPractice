#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 5;
const int MAXM = 3e5 + 5;
typedef pair<int, int> pii;

int f[MAXN], in_tree[MAXM];
tuple<int, int, int> edges[MAXM];

int find(int x) { return f[x] == x ? x : f[x] = find(f[x]); }

int pre;
pii tree[MAXN * 4];
void init(int n) {
  memset(tree, -1, sizeof(tree));
  for (pre = 1; pre <= n; pre <<= 1) {}
}
pii merge(pii a, pii b) {
  int l[5] = {a.first, a.second, b.first, b.second, -1};
  sort(l, l + 5, greater<int>());
  unique(l, l + 5);
  return make_pair(l[0], l[1]);
}
pii query(int s, int t) {
  pii res(0, 0);
  for (s += pre - 1, t += pre + 1; s ^ t ^ 1; s >>= 1, t >>= 1) {
    if (~s & 1) res = merge(res, tree[s ^ 1]);
    if (t & 1) res = merge(res, tree[t ^ 1]);
  }
  return res;
}

struct Edge {
  int to, weight;
  Edge *next;
} tree_edges[MAXN * 2], *edge_it, *head[MAXN];

inline void add_edge(int u, int v, int w) {
  *edge_it = (Edge){v, w, head[u]};
  head[u] = edge_it++;
}

int fa[MAXN], dep[MAXN], son[MAXN], size[MAXN];
int top[MAXN], dfn[MAXN], dfs_c, val[MAXN];

void dfs1(int u, int from) {
  size[u] = 1;
  for (Edge *it = head[u]; it; it = it->next) {
    int v = it->to;
    if (v == from) continue;
    fa[v] = u;
    dep[v] = dep[u] + 1;
    dfs1(v, u);
    if (size[v] > size[son[u]]) son[u] = v;
    size[u] += size[v];
    val[v] = it->weight;
  }
}

void dfs2(int u, int anc) {
  top[u] = anc;
  dfn[u] = ++dfs_c;
  if (son[u]) {
    dfs2(son[u], anc);
    for (Edge *it = head[u]; it; it = it->next)
      if (it->to != fa[u] && it->to != son[u]) dfs2(it->to, it->to);
  }
}

pair<int, pii> lca(int u, int v) {
  pii res(0, 0);
  while (top[u] ^ top[v]) {
    if (dep[top[u]] < dep[top[v]]) swap(u, v);
    res = merge(res, query(dfn[top[u]], dfn[u]));
    u = fa[top[u]];
  }
  if (dep[u] > dep[v]) swap(u, v);
  if (u ^ v) res = merge(res, query(dfn[u] + 1, dfn[v]));
  return make_pair(u, res);
}

int main(int argc, char *argv[]) {
  // freopen("input.txt", "r", stdin);
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;
  for (int i = 0, u, v, w; i < m; ++i) {
    cin >> u >> v >> w;
    edges[i] = make_tuple(w, u, v);
  }

  sort(edges, edges + m);
  iota(f + 1, f + n + 1, 1);

  long long mst = 0;
  edge_it = tree_edges;
  for (int i = 0, u, v, w; i < m; ++i) {
    tie(w, u, v) = edges[i];
    if (find(u) != find(v)) {
      mst += w;
      f[f[u]] = f[v];
      add_edge(u, v, w);
      add_edge(v, u, w);
      in_tree[i] = true;
    }
  }

  init(n);
  dfs_c = 0;
  dfs1(1, 1);
  dfs2(1, 1);
  for (int i = 1; i <= n; ++i) tree[dfn[i] + pre] = make_pair(val[i], -1);
  for (int i = pre; i; --i) tree[i] = merge(tree[i << 1], tree[i << 1 | 1]);

  long long ans = LLONG_MAX;
  for (int i = 0, u, v, w; i < m; ++i) {
    if (in_tree[i]) continue;
    tie(w, u, v) = edges[i];
    if (u == v) continue;
    auto p = lca(u, v);
    if (p.second.first ^ w) ans = min(ans, mst - p.second.first + w);
    if (~p.second.second) ans = min(ans, mst - p.second.second + w);
  }
  cout << ans << '\n';
  return 0;
}
