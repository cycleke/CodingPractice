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
  cerr << "debug: " << __FUNCTION__ << "() @ " << __TIMESTAMP__ << "\n"        \
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

const int MAXN = 5e5 + 5;

struct Data {
  ll a, b, his_a, his_b;
};

Data &operator+=(Data &a, const Data &b) {
  a.his_a = max(a.his_a, a.a + b.his_a);
  a.his_b = max(a.his_b, max(a.b + b.his_a, b.his_b));
  a.a = max(a.a + b.a, -LL_INF);
  a.b = max(a.b + b.a, b.b);
  return a;
}

struct Node {
  Data d;
  Node *ls, *rs;
} node_pool[MAXN * 2], *root, *pool_it;

void build(Node *(&u), int l, int r) {
  u = pool_it++;
  *u = {{0, 0, 0, 0}, NULL, NULL};
  if (l == r) {
    return;
  }
  int mid = (l + r) / 2;
  build(u->ls, l, mid);
  build(u->rs, mid + 1, r);
}

void push_down(Node *u) {
  u->ls->d += u->d;
  u->rs->d += u->d;
  u->d = {0, 0, 0, 0};
}

void update(Node *u, int l, int r, int x, int y, const Data &delta) {
  if (x <= l && r <= y) {
    u->d += delta;
    return;
  }
  push_down(u);
  int mid = (l + r) / 2;
  if (x <= mid) {
    update(u->ls, l, mid, x, y, delta);
  }
  if (y > mid) {
    update(u->rs, mid + 1, r, x, y, delta);
  }
}

Data query(Node *u, int l, int r, const int &pos) {
  if (l == r) {
    return u->d;
  }
  push_down(u);
  int mid = (l + r) / 2;
  if (pos <= mid) {
    return query(u->ls, l, mid, pos);
  } else {
    return query(u->rs, mid + 1, r, pos);
  }
}

int a[MAXN];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cout << fixed << setprecision(10);

  int n, m;
  cin >> n >> m;

  pool_it = node_pool;
  build(root, 0, n - 1);
  FOR(i, 0, n) { cin >> a[i]; }

  while (m--) {
    int op;
    cin >> op;
    switch (op) {
    case 1: {
      int l, r, x;
      cin >> l >> r >> x;
      update(root, 0, n - 1, l - 1, r - 1, {x, 0, x, 0});
      break;
    }
    case 2: {
      int l, r, x;
      cin >> l >> r >> x;
      update(root, 0, n - 1, l - 1, r - 1, {-x, 0, 0, 0});
      break;
    }
    case 3: {
      int l, r, x;
      cin >> l >> r >> x;
      update(root, 0, n - 1, l - 1, r - 1, {-LL_INF, x, 0, x});
      break;
    }
    case 4: {
      int y;
      cin >> y;
      auto d = query(root, 0, n - 1, y - 1);
      cout << max(a[y - 1] + d.a, d.b) << "\n";
      break;
    }
    case 5: {
      int y;
      cin >> y;
      auto d = query(root, 0, n - 1, y - 1);
      cout << max(a[y - 1] + d.his_a, d.his_b) << "\n";
    }
    }
  }
  return 0;
}
