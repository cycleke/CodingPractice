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

const int MAXN = 1e3 + 5;

vi adj[MAXN];
pii p[MAXN];
int n, val[MAXN], sz[MAXN], tot, d, m, rt, rt_w;

void find_root(int u, int from) {
  sz[u] = 1;
  int w = 0;
  for (int &v : adj[u]) {
    if (v == from) continue;
    find_root(v, u);
    if (sz[v] > w) w = sz[v];
    sz[u] += sz[v];
  }
  if (w < n - sz[u]) w = n - sz[u];
  if (w < rt_w) rt = u, rt_w = w;
}

void dfs(int u, int from) {
  val[u] = (tot += d);
  cout << u << ' ' << from << ' ' << val[u] - val[from] << '\n';
  for (int &v : adj[u])
    if (v ^ from) dfs(v, u);
}

int main(int argc, char *argv[]) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cout << fixed << setprecision(10);

  cin >> n;
  int u, v;
  FOR(i, 1, n) {
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  rt_w = INT_MAX;
  find_root(1, 1);
  find_root(rt, rt);
  for (int &v : adj[rt]) p[m++] = {sz[v], v};
  sort(p, p + m);
  int lim = -1;
  for (int i = 0, sum = 0; i < m; ++i)
    if ((sum += p[i].first) >= (n - 1) / 3) {
      lim = i + 1;
      break;
    }
  if (~lim) {
    d = 1;
    FOR(i, 0, lim) dfs(p[i].second, rt);
    d = tot + 1, tot = 0;
    FOR(i, lim, m) dfs(p[i].second, rt);
  }
  return 0;
}
