#pragma GCC optimize(2)
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

const int MAXN = 2e5 + 3;

struct Node {
  ll sum;
  Node *left, *right;
} * nil, node_pool[MAXN * 100], *pool_ptr = node_pool, *root[MAXN];

inline Node *new_node(int sum = 0) {
  *pool_ptr = {sum, nil, nil};
  return pool_ptr++;
}

void update(Node *(&u), int l, int r, int pos, int delta) {
  if (u == nil) {
    u = new_node(delta);
  } else {
    u->sum += delta;
  }
  if (l == r) return;
  int mid = (l + r) / 2;
  if (pos <= mid) {
    update(u->left, l, mid, pos, delta);
  } else {
    update(u->right, mid + 1, r, pos, delta);
  }
}

int n, q;

void update(int pos, int value, int delta) {
  for (int i = pos; i <= n; i += i & -i) update(root[i], 1, MAXN, value, delta);
}

ll query(int pos, int upper) {
  if (pos <= 0) return 0;

  static Node *rts[25];
  ll sum = 0, cnt = 0;
  for (int i = pos; i > 0; i &= i - 1) rts[cnt++] = root[i];
  for (int l = 1, r = MAXN;;) {
    int mid = (l + r) / 2;
    if (upper > mid) {
      l = mid + 1;
      for (int i = 0; i < cnt; ++i) {
        sum += rts[i]->left->sum;
        rts[i] = rts[i]->right;
      }
    } else if (upper < mid) {
      r = mid;
      for (int i = 0; i < cnt; ++i) rts[i] = rts[i]->left;
    } else {
      for (int i = 0; i < cnt; ++i) sum += rts[i]->left->sum;
      break;
    }
  }
  return sum;
}

int a[MAXN];

int main(int argc, char *argv[]) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
  cout << fixed << setprecision(10);

  nil = new_node();
  nil->left = nil->right = nil;

  cin >> n >> q;
  fill(root + 1, root + n + 1, nil);
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
    update(i, a[i], a[i]);
  }
  for (int op, x, y; q; --q) {
    cin >> op >> x >> y;
    if (op == 1) {
      update(x, a[x], -a[x]);
      update(x, y, y);
      a[x] = y;
    } else if (op == 2) {
      int mx;
      ll sum = 0, temp;
      do {
        temp = sum + 1;
        mx = temp <= MAXN ? temp : MAXN;
        sum = query(y, mx) - query(x - 1, mx);
      } while (sum >= temp);
      cout << sum + 1 << "\n";
    } else {
      assert(0);
    }
  }
  return 0;
}
