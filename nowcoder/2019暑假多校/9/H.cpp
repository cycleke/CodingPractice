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

const int MAXN = int(2e5) + 5;
const int MAXH = int(1e5);
const double EPS = 1e-11;

struct Node {
  int size;
  ll sum;
  Node *left, *right;
} node_pool[MAXN * 20], *root[MAXN], *pool;

void update(Node *(&cur), Node *pre, int l, int r, const int &val) {
  cur = pool++;
  *cur = *pre;
  ++cur->size, cur->sum += val;
  if (!(l ^ r)) return;
  int mid = (l + r) / 2;
  if (val <= mid)
    update(cur->left, pre->left, l, mid, val);
  else
    update(cur->right, pre->right, mid + 1, r, val);
}

double query(Node *cur, Node *pre, int l, int r, double val, int num) {
  if (!(l ^ r)) return l - val / (num + cur->size - pre->size);
  int mid = (l + r) / 2;
  int cnt = cur->right->size - pre->right->size;
  ll t = cur->right->sum - pre->right->sum - 1LL * cnt * mid +
         1LL * num * (r - mid);
  if (t + EPS < val)
    return query(cur->left, pre->left, l, mid, val - t, num + cnt);
  return query(cur->right, pre->right, mid + 1, r, val, num);
}

int h[MAXN];
ll sum[MAXN];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cout << fixed << setprecision(12);

  int n, q;
  cin >> n >> q;
  pool = node_pool;
  root[0] = pool++;
  root[0]->sum = root[0]->size = 0;
  root[0]->left = root[0]->right = root[0];
  FOR(i, 1, n + 1) {
    cin >> h[i];
    sum[i] = sum[i - 1] + h[i];
    update(root[i], root[i - 1], 1, MAXH, h[i]);
  }
  for (int x, y, l, r; q; --q) {
    cin >> l >> r >> x >> y;
    cout << query(root[r], root[l - 1], 1, MAXH,
                  1.0 * (sum[r] - sum[l - 1]) / y * x, 0)
         << '\n';
  }

  return 0;
}
