#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100001;

vector<int> g[MAXN];
int in[MAXN], fin[MAXN];
int son[MAXN], top[MAXN], fa[MAXN], dep[MAXN];

int dfs1(int u) {
  static int dfs_id = 0;
  ++dfs_id;
  in[u] = dfs_id;
  fin[dfs_id] = u;
  int size = 1, mx = 0;
  for (int &v : g[u]) {
    fa[v] = u;
    dep[v] = dep[u] + 1;
    int t = dfs1(v);
    if (t > mx) {
      son[u] = v;
      mx = t;
    }
    size += t;
  }
  return size;
}

void dfs2(int u, int tp) {
  top[u] = tp;
  if (son[u]) {
    dfs2(son[u], tp);
  }
  for (int &v : g[u]) {
    if (v == son[u])
      continue;
    dfs2(v, v);
  }
}

int LCA(int u, int v) {
  while (top[u] ^ top[v]) {
    if (dep[top[u]] < dep[top[v]])
      u ^= v ^= u ^= v;
    u = fa[top[u]];
  }
  return (dep[u] < dep[v]) ? u : v;
}

int mx[17][MAXN], mi[17][MAXN];
void Init_ST(const int &n) {
  for (int i = 1; i <= n; ++i)
    mx[0][i] = mi[0][i] = in[i];
  for (int i = 1; i < 17; ++i) {
    for (int j = 1; j + (1 << (i - 1)) <= n; ++j) {
      mx[i][j] = max(mx[i - 1][j], mx[i - 1][j + (1 << (i - 1))]);
      mi[i][j] = min(mi[i - 1][j], mi[i - 1][j + (1 << (i - 1))]);
    }
  }
}

void Ask(int l, int r, int &r_mx, int &r_mi) {
  int e = floor(log2(r - l + 1));
  r_mx = max(mx[e][l], mx[e][r - (1 << e) + 1]);
  r_mi = min(mi[e][l], mi[e][r - (1 << e) + 1]);
}

int GetExc(int x, int l, int r) {
  int u, v;
  if (x == l) {
    Ask(l + 1, r, u, v);
  } else if (x == r) {
    Ask(l, r - 1, u, v);
  } else {
    int u1, u2, v1, v2;
    Ask(l, x - 1, u1, v1);
    Ask(x + 1, r, u2, v2);
    u = max(u1, u2);
    v = min(v1, v2);
  }
  return LCA(fin[u], fin[v]);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  int n, q;
  cin >> n >> q;
  for (int i = 2; i <= n; i++) {
    int p;
    cin >> p;
    g[p].push_back(i);
  }
  dfs1(1);
  dfs2(1, 1);
  Init_ST(n);
  while (q--) {
    int l, r;
    cin >> l >> r;
    if (n == 2) {
      cout << "1 1" << endl;
      continue;
    }
    int ld, rd;
    Ask(l, r, ld, rd);
    int lca1 = GetExc(fin[ld], l, r);
    int lca2 = GetExc(fin[rd], l, r);
    if (dep[lca1] >= dep[lca2]) {
      cout << fin[ld] << " " << dep[lca1] << endl;
    } else {
      cout << fin[rd] << " " << dep[lca2] << endl;
    }
  }
  return 0;
}
