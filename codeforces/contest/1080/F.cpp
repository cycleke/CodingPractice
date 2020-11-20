#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef tuple<int, int, int> tiii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<long long> vll;

const int MAXK = 3e5 + 5;
const int MAX_SIZE = 1.2e7 + 5;
const int INF = 0x3f3f3f3f;

struct Node {
  int value;
  Node *left, *right;

  void maintain() { this->value = min(left->value, right->value); }
} pool[MAX_SIZE], *pool_it(pool), *root[MAXK], *nil;

Node *new_node() {
  *pool_it = *nil;
  return pool_it++;
}

void Insert(Node *&cur, Node *pre, int l, int r, int pos, int value) {
  cur = new_node();
  if (r - l == 1) {
    cur->value = max(pre->value, value);
    return;
  }
  int mid = (l + r) / 2;
  if (pos <= mid) {
    cur->right = pre->right;
    Insert(cur->left, pre->left, l, mid, pos, value);
  } else {
    cur->left = pre->left;
    Insert(cur->right, pre->right, mid, r, pos, value);
  }
  cur->maintain();
}

int Query(Node *cur, int l, int r, int x, int y) {
  if (x <= l && r <= y)
    return cur->value;
  int mid = (l + r) / 2;
  int res = INF;
  if (x < mid)
    res = min(res, Query(cur->left, l, mid, x, y));
  if (y > mid)
    res = min(res, Query(cur->right, mid, r, x, y));
  return res;
}

pair<pii, int> d[MAXK];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  int n, m, k;
  cin >> n >> m >> k;
  for (int i = 1; i <= k; i++) {
    cin >> d[i].first.first >> d[i].first.second >> d[i].second;
  }
  sort(d + 1, d + k + 1, [](const pair<pii, int> &a, const pair<pii, int> &b) {
    return a.first.second < b.first.second;
  });

  nil = pool_it++;
  nil->value = 0;
  nil->left = nil->right = nil;

  root[0] = new_node();
  for (int i = 1; i <= k; i++) {
    Insert(root[i], root[i - 1], 0, n, d[i].second, d[i].first.first);
  }

  while (m--) {
    int a, b, x, y;
    cin >> a >> b >> x >> y;
    int l = 0, r = k;
    while (l < r) {
      int mid = (l + r + 1) / 2;
      if (d[mid].first.second <= y)
        l = mid;
      else
        r = mid - 1;
    }
    cout << (Query(root[r], 0, n, a - 1, b) >= x ? "yes" : "no") << endl;
    cout.flush();
  }

  return 0;
}
