#pragma GCC optimize(2)
#include <bits/stdc++.h>

inline char get_char() {
  static char b[1 << 16 | 3], *s = b, *e = b;
  if (s == e) e = (s = b) + fread(b, 1, 1 << 16 | 3, stdin);
  return (s == e) ? EOF : *s++;
}

inline int get_uint() {
  int x = 0, c;
  while ((c = get_char()) < '0') {}
  for (x = c ^ 48; isdigit(c = get_char());) x = x * 10 + (c ^ 48);
  return x;
}

const int ALPHABET = 26;
const int MAXN = 1e5 + 7;

struct Edge {
  int to;
  Edge *next;
} pool[MAXN], *g[MAXN], *pool_ptr;

inline void add_edge(int u, int v) {
  *pool_ptr = {v, g[u]};
  g[u] = pool_ptr++;
}

long long tree1[MAXN], tree2[MAXN];
int ch[MAXN][ALPHABET], fail[MAXN];
int in[MAXN], out[MAXN], que[MAXN], dfs_clock;
int son[MAXN], top[MAXN], size[MAXN];

inline void build_acam() {
  fail[0] = 1;
  int *l = que, *r = que;
  for (int i = 0; i ^ ALPHABET; ++i)
    if (ch[ch[0][i] = 1][i]) {
      fail[ch[1][i]] = 1;
      *r++ = ch[1][i];
    }
  while (l < r) {
    int p = *l++, f = fail[p];
    add_edge(f, p);
    for (int i = 0; i ^ ALPHABET; ++i)
      if (ch[p][i]) {
        for (f = fail[p]; !ch[f][i]; f = fail[f]) {}
        fail[ *r++ = ch[p][i]] = ch[f][i];
      }
  }
}

void dfs1(int u) {
  size[u] = 1, son[u] = 0;
  for (Edge *it = g[u]; it; it = it->next) {
    int v = it->to;
    dfs1(v);
    size[u] += size[v];
    size[v] > size[son[u]] ? son[u] = v : 0;
  }
}

void dfs2(int u, int anc) {
  in[u] = ++dfs_clock, top[u] = anc;
  if (son[u]) dfs2(son[u], anc);
  for (Edge *it = g[u]; it; it = it->next) {
    int v = it->to;
    if (v ^ son[u]) dfs2(v, v);
  }
  out[u] = dfs_clock;
}

inline long long sum(long long *tree, int x) {
  long long res = 0;
  while (x) res += tree[x], x &= x - 1;
  return res;
}

inline long long sum(int x) { return sum(tree1, x) * (x + 1) - sum(tree2, x); }

inline long long query(int l, int r) { return sum(r) - sum(l - 1); }

inline void add(long long *tree, int x, long long val) {
  for (; x < dfs_clock; x += x & -x) tree[x] += val;
}

inline void add(int x, long long val) {
  add(tree1, x, val), add(tree2, x, x * val);
}

inline void modify(int l, int r) { add(l, 1), add(r + 1, -1); }

void get_sum(int u, long long &v) {
  if (!u || que[top[u]] >= in[u]) return;
  if (que[top[u]]) {
    v += query(que[top[u]] + 1, in[u]);
  } else {
    v += query(in[top[u]], in[u]);
    get_sum(fail[top[u]], v);
  }
  que[top[u]] = in[u];
}

inline void clear(int u) {
  for (; u; u = fail[top[u]]) que[top[u]] = 0;
}

struct Pair {
  int l, r;
} a[MAXN];
bool operator<(const Pair &a, const Pair &b) { return a.l < b.l; }
int main(int argc, char *argv[]) {
  for (int _ = get_uint(); _; --_) {
    int n = get_uint();
    pool_ptr = pool;
    memset(g, 0, (n + 3) * sizeof(Edge *));
    memset(ch, 0, (n + 3) * sizeof(ch[0]));
    memset(fail, 0, (n + 3) * sizeof(int));
    memset(tree1, 0, (n + 3) * sizeof(long long));
    memset(tree2, 0, (n + 3) * sizeof(long long));
    for (int i = 2; i <= n; ++i) {
      int x = get_uint();
      char ch = get_char();
      while (ch < 'a') ch = get_char();
      ::ch[x][ch - 'a'] = i;
    }
    build_acam();
    fail[1] = 0;
    dfs1(1);
    dfs_clock = 0;
    dfs2(1, 1);
    ++dfs_clock;

    for (int _ = get_uint(); _; --_) {
      int op = get_uint(), k = get_uint();
      if (op < 2) {
        for (int i = 0, x; i < k; ++i) {
          x = get_uint();
          a[i] = (Pair){in[x], out[x]};
        }
        std::sort(a, a + k);
        int x = 0;
        for (int i = 0; i < k; ++i) {
          if (a[i].r <= x) continue;
          x = a[i].r;
          modify(a[i].l, a[i].r);
        }
      } else {
        for (int i = 0, x; i < k; ++i) {
          x = get_uint();
          clear(son[i] = x);
        }
        long long ans = 0;
        for (int i = 0; i < k; ++i) get_sum(son[i], ans);
        printf("%lld\n", ans);
      }
    }
  }
  return 0;
}
