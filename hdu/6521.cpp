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

const int INF = 0x3ffffff;
const ll LL_INF = 0x3fffffffffffffffll;
const int MOD = 1e9 + 7;
const ll HASH_KEY = 6151;
const ll HASH_MOD = 1610612741;

// mt19937 rdm(chrono::steady_clock::now().time_since_epoch().count());
// uniform_int_distribution<int> u_int(begin, end);
// uniform_real_distribution<double> u_read(begin, end);
/* -- HEAD END -- */

const int MAXN = 5e5 + 3;

struct Node {
  int mx, mi, lz;
  int l, r;
  ll sum;
  Node *ls, *rs;

  void push_down() {
    if (lz) {
      ls->mx = ls->mi = ls->lz = lz;
      ls->sum = ll(ls->r - ls->l + 1) * lz;
      rs->mx = rs->mi = rs->lz = lz;
      rs->sum = ll(rs->r - rs->l + 1) * lz;
      lz = 0;
    }
  }

  void maintiaon() {
    sum = ls->sum + rs->sum;
    mx = max(ls->mx, rs->mx);
    mi = min(ls->mi, rs->mi);
  }

} node_pool[MAXN * 2], *rt, *it_pool;

void build(Node *&u, int l, int r) {
  u = it_pool;
  ++it_pool;
  *u = (Node){r, l, 0, l, r, (l + r) * (r - l + 1ll) / 2, NULL, NULL};
  if (l < r) {
    int mid = (l + r) / 2;
    build(u->ls, l, mid);
    build(u->rs, mid + 1, r);
  }
}

ll ans;

void update(Node *&u, int x, int y, int val) {
  if (x <= u->l && u->r <= y) {
    if (u->mx <= val) {
      return;
    }
    if (u->mi >= val) {
      ll t = val * ll(u->r - u->l + 1);
      ans += u->sum - t;
      u->mx = u->mi = u->lz = val;
      u->sum = t;
      return;
    }
  }
  u->push_down();
  int mid = (u->l + u->r) / 2;
  if (x <= mid) {
    update(u->ls, x, y, val);
  }
  if (mid < y) {
    update(u->rs, x, y, val);
  }
  u->maintiaon();
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  int n, m;
  while (cin >> n >> m) {
    it_pool = node_pool;
    build(rt, 1, n);
    while (m--) {
      int a, b;
      cin >> a >> b;
      ans = 0;
      update(rt, a, b, a);
      cout << ans << "\n";
    }
  }
  return 0;
}
