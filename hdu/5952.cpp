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
#define dbg(x)                                                          \
  cerr << "debug: " << __FUNCTION__ << "() @ " << __TIMESTAMP__ << "\n" \
  << __FILE__ << " L" << __LINE__ << "\n"                               \
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

const int MAXN = 100 + 3;

vi adj[MAXN];
bool connected[MAXN][MAXN], vis[MAXN];
int n, m, s, top, stk[MAXN], ans;

inline bool check(int u) {
  FOR(i, 0, top)
    if (!connected[stk[i]][u]) return false;
  return true;
}

void dfs(int u) {
  if (top == s) return (void)(++ans);
  if (n - u + top < s) return;
  FOR(i, 0, adj[u].size()) {
    if (vis[adj[u][i]] || !check(adj[u][i])) continue;
    vis[adj[u][i]] = true;
    stk[top++] = adj[u][i];
    dfs(adj[u][i]);
    --top;
    vis[adj[u][i]] = false;
  }
}

void solve() {
  cin >> n >> m >> s;
  FOR(i, 0, n) adj[i].clear(), vis[i] = false;
  FOR2(i, 0, n, j, 0, n) connected[i][j] = false;
  for (int u, v; m; --m) {
    cin >> u >> v;
    if (--u > --v) swap(u, v);
    adj[u].push_back(v);
    connected[u][v] = true;
  }
  ans = 0;
  FOR(i, 0, n) {
    top = 1;
    stk[0] = i;
    vis[i] = true;
    dfs(i);
  }
  cout << ans << '\n';
}

int main(int argc, char *argv[]) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout << fixed << setprecision(10);

  int o_o;
  for (cin >> o_o; o_o; --o_o) solve();

  return 0;
}
