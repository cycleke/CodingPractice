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

const int MAXN = 1e5 + 5;

int n, m, f[MAXN], sz[MAXN];

inline int gf(int x) {
  while (f[x] ^ x) x = f[x];
  return x;
}
inline int link(int x, int y) {
  x = gf(x), y = gf(y);
  if (x ^ y) {
    if (sz[x] < sz[y]) swap(x, y);
    f[y] = x;
    sz[x] += sz[y];
    return y;
  }
  return 0;
}

struct Node {
  vi edges, linked;
  Node *left, *right;
} node_pool[MAXN * 4], *pool, *root;

pii edges[MAXN];
int ans, idx[MAXN * 2], idc, L[MAXN], R[MAXN];
void update(Node *(&u), int l, int r, const int &x, const int &y,
            const int &e) {
  if (u == nullptr) u = pool++;
  if (x <= l && r <= y) {
    u->edges.push_back(e);
    return;
  }
  int mid = (l + r) / 2;
  if (x < mid) update(u->left, l, mid, x, y, e);
  if (y > mid) update(u->right, mid, r, x, y, e);
}
void dfs(Node *(&u), int l, int r) {
  if (u == nullptr) return;
  for (int &e : u->edges)
    u->linked.push_back(link(edges[e].first, edges[e].second));

  if (gf(1) == gf(n)) {
    ans += idx[r] - idx[l];
  } else if (l ^ r) {
    int mid = (l + r) / 2;
    dfs(u->left, l, mid);
    dfs(u->right, mid, r);
  }

  for (int &y : u->linked) sz[f[y]] -= sz[y], f[y] = y;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cout << fixed << setprecision(10);

  cin >> n >> m;
  idc = 0;
  FOR(i, 0, m) {
    cin >> edges[i].first >> edges[i].second >> L[i] >> R[i];
    idx[idc++] = L[i], idx[idc++] = ++R[i];
  }
  sort(idx, idx + idc);
  idc = unique(idx, idx + idc) - idx;

  pool = node_pool, root = nullptr;
  FOR(i, 0, m) {
    int x = lower_bound(idx, idx + idc, L[i]) - idx;
    int y = lower_bound(idx, idx + idc, R[i]) - idx;
    update(root, 0, idc - 1, x, y, i);
  }

  ans = 0;
  iota(f + 1, f + n + 1, 1);
  fill(sz + 1, sz + n + 1, 1);
  dfs(root, 0, idc - 1);
  cout << ans << '\n';

  return 0;
}
