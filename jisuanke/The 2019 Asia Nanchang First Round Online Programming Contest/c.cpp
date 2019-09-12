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

const int MAXN = 2e5 + 5;

struct Mat {
  int a[5][5];
  void init() {
    memset(a, 0x3f, sizeof(a));
    FOR(i, 0, 5) a[i][i] = 0;
  }
  Mat operator*(const Mat &x) const {
    Mat res;
    memset(res.a, 0x3f, sizeof(res.a));
    FOR(k, 0, 5)
    FOR2(i, 0, 5, j, 0, 5) res.a[i][j] = min(res.a[i][j], a[i][k] + x.a[k][j]);
    return res;
  }
  void change(const char &ch) {
    init();
    switch (ch) {
    case '2': a[0][1] = 0, a[0][0] = 1; break;
    case '0': a[1][2] = 0, a[1][1] = 1; break;
    case '1': a[2][3] = 0, a[2][2] = 1; break;
    case '9': a[3][4] = 0, a[3][3] = 1; break;
    case '8': a[3][3] = 1, a[4][4] = 1; break;
    }
  }
};

struct Node {
  Mat v;
  Node *left, *right;
} node_pool[MAXN * 2], *node_it, *root;

char s[MAXN];

void build(Node *&u, int l, int r) {
  u = node_it, ++node_it;
  if (l == r) {
    u->v.change(s[l - 1]);
  } else {
    int mid = (l + r) >> 1;
    build(u->left, l, mid);
    build(u->right, mid + 1, r);
    u->v = u->left->v * u->right->v;
  }
}

Mat query(Node *u, int l, int r, const int &x, const int &y) {
  if (x <= l && r <= y) return u->v;
  int mid = (l + r) >> 1;
  if (y <= mid) return query(u->left, l, mid, x, y);
  if (x > mid) return query(u->right, mid + 1, r, x, y);
  return query(u->left, l, mid, x, y) * query(u->right, mid + 1, r, x, y);
}

void solve() {
  int n, q;
  cin >> n >> q >> s;
  reverse(s, s + n);
  node_it = node_pool;
  build(root, 1, n);
  for (int l, r, t; q; --q) {
    cin >> l >> r;
    l = n + 1 - l, r = n + 1 - r;
    t = query(root, 1, n, r, l).a[0][4];
    if (t == 0x3f3f3f3f) t = -1;
    cout << t << '\n';
  }
}

int main(int argc, char *argv[]) {
  // freopen("in.txt", "r", stdin);
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout << fixed << setprecision(10);

  int o_o;
  for (o_o = 1; o_o; --o_o) solve();

  return 0;
}
