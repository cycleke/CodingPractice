#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef tuple<int, int, int> tiii;

const int MAXN = 1e5 + 5;

int n, q;
tiii edges[MAXN];

namespace BIT {
ll tree[MAXN];

void add(int x, const int &val) {
  for (; x <= n; x += x & -x) tree[x] += val;
}
void add(int l, int r, const int &val) { add(l, val), add(r + 1, -val); }

ll ask(int x) {
  ll res = 0;
  for (; x; x &= x - 1) res += tree[x];
  return res;
}
} // namespace BIT

namespace tcs {

int size[MAXN], son[MAXN], fa[MAXN], top[MAXN], dep[MAXN], val[MAXN];
int in[MAXN], out[MAXN], idx[MAXN], dfs_c;
vector<pii> adj[MAXN];

void cal_son(int u) {
  son[u] = 0;
  size[u] = 1;
  for (pii &e : adj[u]) {
    int v = e.first;
    if (v == fa[u]) continue;
    fa[v] = u;
    dep[v] = dep[u] + 1;
    val[v] = e.second;
    cal_son(v);
    if (size[v] > size[son[u]]) son[u] = v;
    size[u] += size[v];
  }
}

void cal_top(int u, int anc) {
  top[u] = anc;
  idx[in[u] = ++dfs_c] = u;

  if (son[u]) {
    cal_top(son[u], anc);
    BIT::add(in[son[u]], out[son[u]], val[son[u]]);
    for (pii &e : adj[u])
      if (e.first != son[u] && e.first != fa[u]) {
        cal_top(e.first, e.first);
        BIT::add(in[e.first], out[e.first], val[e.first]);
      }
  }
  out[u] = dfs_c;
}

void init() {
  cal_son(1);
  cal_top(1, 1);
}

int lca(int u, int v) {
  while (top[u] ^ top[v]) {
    if (dep[top[u]] < dep[top[v]]) swap(u, v);
    u = fa[top[u]];
  }
  return dep[u] < dep[v] ? u : v;
}

ll dist(int u, int v) {
  int g = lca(u, v);
  return BIT::ask(in[u]) + BIT::ask(in[v]) - 2 * BIT::ask(in[g]);
}
} // namespace tcs

namespace SGT {
struct Node {
  int u, v;
  ll d;
  Node *left, *right;

  void change(int _u, int _v, ll _d) { u = _u, v = _v, d = _d; }
  void change(int _u, int _v) {
    ll _d = tcs::dist(_u, _v);
    if (_d > d) change(_u, _v, _d);
  }
  void change(Node *a) { change(a->u, a->v, a->d); }
} node_pool[MAXN * 2], *node_it, *root;

void maintain(Node *u) {
  if (u->left->d > u->right->d) {
    u->change(u->left);
  } else {
    u->change(u->right);
  }
  int a = u->left->u, b = u->left->v;
  int c = u->right->u, d = u->right->v;
  u->change(a, c), u->change(a, d);
  u->change(b, c), u->change(b, d);
}

void build(Node *&u, int l, int r) {
  u = node_it++;
  if (l == r) {
    *u = (Node){tcs::idx[l], tcs::idx[l], 0, NULL, NULL};
    return;
  }
  int mid = (l + r) >> 1;
  build(u->left, l, mid);
  build(u->right, mid + 1, r);
  maintain(u);
}

void init() {
  node_it = node_pool;
  build(root, 1, n);
}

void update(Node *u, int l, int r, const int &x, const int &y) {
  if (x <= l && r <= y) return;
  int mid = (l + r) >> 1;
  if (x <= mid) update(u->left, l, mid, x, y);
  if (y > mid) update(u->right, mid + 1, r, x, y);
  maintain(u);
}

} // namespace SGT

int main() {
  // freopen("a.in", "r", stdin);
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n;
  for (int i = 1, u, v, w; i < n; ++i) {
    cin >> u >> v >> w;
    tcs::adj[u].emplace_back(v, w);
    tcs::adj[v].emplace_back(u, w);
    edges[i] = (tiii){u, v, w};
  }

  tcs::init();
  SGT::init();

  cin >> q;
  char op[3];
  for (int id, _w, u, v, w, p1 = SGT::root->u, p2 = SGT::root->v; q; --q) {
    cin >> op;
    if (*op == 'Q') {
      cin >> u;
      cout << max(tcs::dist(p1, u), tcs::dist(p2, u)) << '\n';
    } else {
      cin >> id >> _w;
      tie(u, v, w) = edges[id];
      if (tcs::dep[u] > tcs::dep[v]) swap(u, v);
      BIT::add(tcs::in[v], tcs::out[v], _w - w);
      SGT::update(SGT::root, 1, n, tcs::in[v], tcs::out[v]);
      p1 = SGT::root->u, p2 = SGT::root->v;
      edges[id] = (tiii){u, v, _w};
    }
  }
  return 0;
}
