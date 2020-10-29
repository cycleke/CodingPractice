#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2e5 + 3;

struct Node {
  int sum;
  Node *left, *right;
} pool[MAXN * 100], *pool_ptr, *nil, *root[MAXN];

Node *newNode() {
  *pool_ptr = {0, nil, nil};
  return pool_ptr++;
}

void update(Node *(&u), int l, int r, int pos, int delta) {
  if (u == nil) u = newNode();
  u->sum += delta;
  if (l == r) return;
  int mid = (l + r) / 2;
  if (pos <= mid)
    update(u->left, l, mid, pos, delta);
  else
    update(u->right, mid + 1, r, pos, delta);
  // cerr << l << " " << r << " " << pos << " " << delta << " " << u->sum <<
  // "\n";
}
int query(Node *u, int l, int r, int x, int y) {
  if (u == nil) return 0;
  if (x <= l && r <= y) return u->sum;
  int mid = (l + r) / 2, res = 0;
  if (x <= mid) res = query(u->left, l, mid, x, y);
  if (y > mid) res += query(u->right, mid + 1, r, x, y);
  return res;
}

int n, ch[MAXN][26], pos[MAXN], in[MAXN], out[MAXN], tot, dfn;

void update(int x, int pos, int delta) {
  for (; x <= n; x += x & -x) update(root[x], 1, tot, pos, delta);
}
int query(int x, int l, int r) {
  int res = 0;
  for (; x > 0; x &= x - 1) res += query(root[x], 1, tot, l, r);
  return res;
}

void init() {
  tot = 1;
  memset(ch, -1, sizeof(ch));
  pool_ptr = pool;
  nil = newNode();
  nil->left = nil->right = nil;
  fill(root + 1, root + n + 1, nil);
}

void dfs(int u) {
  in[u] = ++dfn;
  for (int i = 0; i < 26; ++i) {
    int v = ch[u][i];
    if (v < 0) continue;
    dfs(v);
  }
  out[u] = dfn;
}

int main() {
  // freopen("in.txt", "r", stdin);
  // freopen("out.txt", "w", stdout);
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
  cout << fixed << setprecision(10);

  int m;
  cin >> n >> m;
  init();

  static char buf[MAXN];
  for (int i = 1; i <= n; ++i) {
    cin >> buf;
    int u = 0;
    for (char *it = buf; *it; ++it) {
      int chr = *it - 'a';
      if (ch[u][chr] < 0) ch[u][chr] = tot++;
      u = ch[u][chr];
    }
    pos[i] = u;
  }

  dfs(0);
  for (int i = 1; i <= n; ++i) update(i, in[pos[i]], 1);
  // cerr << "########" << endl;
  for (int opt, i, j, k; m; --m) {
    cin >> opt;
    if (opt == 1) {
      cin >> i >> j;
      if (i == j) continue;
      update(i, in[pos[i]], -1);
      update(i, in[pos[j]], 1);
      update(j, in[pos[j]], -1);
      update(j, in[pos[i]], 1);
      swap(pos[i], pos[j]);
    } else {
      cin >> buf >> k >> i >> j;
      int u = 0;
      for (int step = 0; (~u) && step < k; ++step) {
        int chr = buf[step] - 'a';
        u = ch[u][chr];
      }
      if (u < 0) {
        cout << "0\n";
      } else {
        // cerr << in[u] << " " << out[u] << endl;
        int l = in[u] ? in[u] : 1, r = out[u];
        if (l > r) {
          cout << "0\n";
        } else {
          cout << query(j, in[u], out[u]) - query(i - 1, in[u], out[u]) << "\n";
        }
      }
    }
  }

  return 0;
}
