#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 5;

char s[MAXN];
int sa[MAXN], x[MAXN], y[MAXN], c[MAXN];
int rk[MAXN], height[MAXN], st[17][MAXN], lg[MAXN];

bool cmp(int *r, int i, int j, int l) {
  return r[i] == r[j] && r[i + l] == r[j + l];
}
void da(char *s, int n, int m) {
  int i, j, p;
  for (i = 0; i < m; ++i) c[i] = 0;
  for (i = 0; i < n; ++i) ++c[x[i] = s[i]];
  for (i = 1; i < m; ++i) c[i] += c[i - 1];
  for (i = n - 1; ~i; --i) sa[--c[x[i]]] = i;
  for (p = j = 1; p < n; j <<= 1, m = p) {
    for (p = 0, i = n - j; i < n; ++i) y[p++] = i;
    for (i = 0; i < n; ++i)
      if (sa[i] >= j) y[p++] = sa[i] - j;
    for (i = 0; i < m; ++i) c[i] = 0;
    for (i = 0; i < n; ++i) ++c[x[y[i]]];
    for (i = 1; i < m; ++i) c[i] += c[i - 1];
    for (i = n - 1; ~i; --i) sa[--c[x[y[i]]]] = y[i];
    for (swap(x, y), p = 1, x[sa[0]] = 0, i = 1; i < n; ++i)
      x[sa[i]] = cmp(y, sa[i], sa[i - 1], j) ? p - 1 : p++;
  }
}

void get_height(char *s, int n) {
  int i, j, k;
  for (i = 0; i < n; ++i) rk[sa[i]] = i;
  for (i = k = height[rk[0]] = 0; i < n; height[rk[i++]] = k)
    if (rk[i])
      for (k > 0 ? --k : 0, j = sa[rk[i] - 1]; s[i + k] == s[j + k]; ++k) {}
}

void init_st_table(int n) {
  int lgn = lg[n];
  for (int i = 0; i < n; ++i) st[0][i] = height[i];
  for (int i = 1; i <= lgn; ++i)
    for (int j = 0; j + (1 << i - 1) < n; ++j)
      st[i][j] = min(st[i - 1][j], st[i - 1][j + (1 << i - 1)]);
}

int lcp(int i, int j) {
  if (i > j) swap(i, j);
  ++i;
  int lgl = lg[j - i + 1];
  return min(st[lgl][i], st[lgl][j - (1 << lgl) + 1]);
}

struct Node {
  int sum;
  Node *left, *right;
} node_pool[MAXN * 20], *node_it, *root[MAXN];

void update(Node *&cur, Node *pre, int l, int r, int pos) {
  cur = node_it, ++node_it;
  *cur = (Node){pre->sum + 1, pre->left, pre->right};
  if (l == r) return;
  int mid = (l + r) >> 1;
  if (pos <= mid)
    update(cur->left, pre->left, l, mid, pos);
  else
    update(cur->right, pre->right, mid + 1, r, pos);
}

int query(Node *L, Node *R, int l, int r, int k) {
  if (l == r) return l;
  int mid = (l + r) >> 1, sum = R->left->sum - L->left->sum;
  if (k <= sum) return query(L->left, R->left, l, mid, k);
  return query(L->right, R->right, mid + 1, r, k - sum);
}

void solve() {
  int n, q, l, r, k;
  cin >> n >> q >> s;
  s[n++] = '$';
  da(s, n, 128);
  get_height(s, n);
  init_st_table(n);

  node_it = node_pool;
  root[0] = node_it, ++node_it;
  root[0]->sum = 0;
  root[0]->left = root[0]->right = root[0];
  for (int i = 1; i <= n; ++i) update(root[i], root[i - 1], 1, n, sa[i] + 1);

  for (; q; --q) {
    cin >> l >> r >> k;
    --l, --r;

    int len = r - l + 1, down = rk[l], up = rk[l];
    int le = 1, ri = down - 1;
    while (le <= ri) {
      int mid = (le + ri) >> 1;
      if (lcp(mid, rk[l]) >= len) {
        down = mid;
        ri = mid - 1;
      } else {
        le = mid + 1;
      }
    }
    le = up + 1, ri = n;
    while (le <= ri) {
      int mid = (le + ri) >> 1;
      if (lcp(mid, rk[l]) >= len) {
        up = mid;
        le = mid + 1;
      } else {
        ri = mid - 1;
      }
    }
    if (up - down + 1 < k) {
      cout << "-1\n";
    } else {
      cout << query(root[down - 1], root[up], 1, n, k) << '\n';
    }
  }
}

int main(int argc, char *argv[]) {
  // freopen("input.txt", "r", stdin);
  ios::sync_with_stdio(false);
  cin.tie(0);

  lg[1] = 0;
  for (int i = 2; i < MAXN; ++i) lg[i] = lg[i >> 1] + 1;

  int o_o;
  for (cin >> o_o; o_o; --o_o) solve();

  return 0;
}
