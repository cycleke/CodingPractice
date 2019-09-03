#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 5;

struct Node {
  int val;
  Node *left, *right;
} node_pool[MAXN * 2], *root, *pool, *nil;

void update(Node *&u, int l, int r, const int &pos, const int &val) {
  if (u == nil) *(u = pool) = *nil, ++pool;
  if (l == r) {
    u->val = val;
    return;
  }
  int mid = (l + r) >> 1;
  if (pos <= mid) {
    update(u->left, l, mid, pos, val);
  } else {
    update(u->right, mid + 1, r, pos, val);
  }
  u->val = max(u->left->val, u->right->val);
}
int query(Node *u, int l, int r, const int &x, const int &y) {
  if (r < y) return -1;
  if (l == r) return l;
  int mid = (l + r) >> 1, t;
  if (u->left->val > x && (t = query(u->left, l, mid, x, y)) > 0) return t;
  if (u->right->val > x) return query(u->right, mid + 1, r, x, y);
  return -1;
}

int a[MAXN];
void solve() {
  root = nil;
  pool = node_pool;

  int n, m, last_ans = 0;
  cin >> n >> m;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
    update(root, 1, n + 1, a[i], i);
  }
  update(root, 1, n + 1, n + 1, n + 1);
  for (int opt, x, y; m; --m) {
    cin >> opt >> x;
    if (opt == 1) {
      x ^= last_ans;
      if (a[x]) {
        update(root, 1, n + 1, a[x], INT_MAX);
        a[x] = 0;
      }
    } else {
      cin >> y;
      x ^= last_ans, y ^= last_ans;
      cout << (last_ans = query(root, 1, n + 1, x, y)) << '\n';
    }
  }
}

int main(int argc, char *argv[]) {
  // freopen("input.txt", "r", stdin);
  ios::sync_with_stdio(false);
  cin.tie(0);

  nil = new Node;
  nil->val = 0;
  nil->left = nil->right = nil;

  int o_o;
  for (cin >> o_o; o_o; --o_o) solve();

  delete nil;
  return 0;
}
