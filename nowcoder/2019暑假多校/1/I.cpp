#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<int, int> pii;
typedef tuple<int, int, int> tiii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<long long> vll;
typedef vector<pii> vpii;

#define fi first
#define se second
#define pb push_back
#define mp make_pair

#define SZ(a) int((a).size())
#define ALL(a) (a).begin(), (a).end()
#define EXIST(s, x) ((s).find(x) != (s).end())
#define A_EXIST(a, x) (find(ALL(a), x) != (a).end())
#define ZERO(a) memset((a), 0, sizeof(a))

#define FOR(i, a, b) for (int i = int(a); i < int(b); ++i)
#define REP(i, a, b) for (int i = int(b) - 1; i >= a; --i)
#define FOR2(i, a, b, j, c, d) FOR(i, a, b) FOR(j, c, d)
#define REP2(i, a, b, j, c, d) REP(i, a, b) REP(j, c, d)
#define EACH(i, s) for (auto i = (s).begin(); i != (s).end(); ++i)
#define MUL_CASE                                                               \
  int o_o;                                                                     \
  cin >> o_o;                                                                  \
  for (int case_count = 0; case_count < o_o; ++case_count)
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define dbg(x)                                                                 \
  cout << "debug: " << __FUNCTION__ << "() @ " << __TIMESTAMP__ << "\n"        \
       << __FILE__ << " L" << __LINE__ << "\n"                                 \
       << #x " = " << (x) << endl

const int INF = 0x3ffffff;
const ll LL_INF = 0x3fffffffffffffffll;
const int MOD = 1e9 + 7;
const ll HASH_KEY = 6151;
const ll HASH_MOD = 1610612741;

// mt19937 rdm(chrono::steady_clock::now().time_since_epoch().count());
// uniform_int_distribution<int> u_int(begin, end);
// uniform_real_distribution<double> u_read(begin, end);
/* -- HEAD END -- */

const int MAXN = 1e5 + 5;

struct Node {
  ll val, tag;
  Node *left, *right;

  void push_down() {
    if (tag) {
      left->val += tag;
      left->tag += tag;
      right->val += tag;
      right->tag += tag;
      tag = 0;
    }
  }

  void maintain() { val = max(left->val, right->val); }

} node_pool[MAXN * 2], *pool_it, *root;

void build(Node *(&u), int l, int r) {
  u = pool_it;
  *u = (Node){0, 0, NULL, NULL};
  ++pool_it;
  if (l < r) {
    int mid = (l + r) / 2;
    build(u->left, l, mid);
    build(u->right, mid + 1, r);
  }
}

void add(Node *u, int l, int r, const int &x, const int &y, const ll delta) {
  if (x <= l && r <= y) {
    u->val += delta;
    u->tag += delta;
    return;
  }
  u->push_down();
  int mid = (l + r) / 2;
  if (x <= mid) {
    add(u->left, l, mid, x, y, delta);
  }
  if (y > mid) {
    add(u->right, mid + 1, r, x, y, delta);
  }
  u->maintain();
}

void modify(Node *u, int l, int r, const int &pos, const ll val) {
  if (l == r && l == pos) {
    u->val = val;
    u->tag = 0;
    return;
  }
  u->push_down();
  int mid = (l + r) / 2;
  if (pos <= mid) {
    modify(u->left, l, mid, pos, val);
  } else {
    modify(u->right, mid + 1, r, pos, val);
  }
  u->maintain();
}

ll query(Node *u, int l, int r, const int &x, const int &y) {
  if (x <= l && r <= y) {
    return u->val;
  }
  u->push_down();
  int mid = (l + r) / 2;
  ll res = 0;
  if (x <= mid) {
    res = max(res, query(u->left, l, mid, x, y));
  }
  if (y > mid) {
    res = max(res, query(u->right, mid + 1, r, x, y));
  }
  return res;
}

pair<pii, pii> p[MAXN];
int Y[MAXN];

int main() {

  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  int n, cnt;
  while (cin >> n) {
    FOR(i, 0, n) {
      int x, y, a, b;
      cin >> x >> y >> a >> b;
      p[i] = mp(mp(x, y), mp(a, b));
      Y[i] = y;
    }

    Y[n] = 0;
    sort(p, p + n, [&](const pair<pii, pii> &a, const pair<pii, pii> &b) {
      return a.first.first == b.first.first ? (a.first.second > b.first.second)
                                            : a.first.first < b.first.first;
    });
    sort(Y, Y + n + 1);
    cnt = unique(Y, Y + n + 1) - Y;
    pool_it = node_pool;
    build(root, 1, cnt);

    FOR(i, 0, n) {
      int y = lower_bound(Y, Y + cnt, p[i].first.second) - Y + 1;
      ll temp = query(root, 1, cnt, 1, y);
      modify(root, 1, cnt, y, temp + p[i].second.second);
      if (y > 1) {
        add(root, 1, cnt, 1, y - 1, p[i].second.first);
      }
      if (y < cnt) {
        add(root, 1, cnt, y + 1, cnt, p[i].second.second);
      }
    }

    cout << query(root, 1, cnt, 1, cnt) << "\n";
  }

  return 0;
}
