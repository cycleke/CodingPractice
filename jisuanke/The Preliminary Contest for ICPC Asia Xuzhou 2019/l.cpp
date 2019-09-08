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

const int MAXN = 17;
const int MAXS = 1 << 16 | 3;

inline int dis(int x, int y) {
  if (!x && !y) return 0;
  if (x < 0) x = -x;
  if (y < 0) y = -y;
  if (x == 1 && y == 1) return 6;
  if (x > y) swap(x, y);
  if (x < 2) return x + y + 2 * (y % 4 != 0);
  return x + y;
}

int n, m, x[MAXN], y[MAXN], f[MAXN][MAXS];

void cmin(int &a, int b) {
  if (a > b) a = b;
}

void solve() {
  cin >> n;
  m = 0;
  FOR(i, 0, n) {
    cin >> x[m] >> y[m];
    if (!x[m] && !y[m]) continue;
    ++m;
  }

  if (m == 0) {
    cout << "0\n";
    return;
  }

  memset(f, 0x3f, sizeof(f));
  FOR(i, 0, m) f[i][1 << i] = dis(x[i], y[i]);

  int S = 1 << m;
  FOR2(s, 0, S, i, 0, m) {
    if (~s >> i & 1) continue;
    FOR(j, 0, m)
    if (~s >> j & 1)
        cmin(f[j][s ^ (1 << j)], f[i][s] + dis(x[i] - x[j], y[i] - y[j]));
  }
  int ans = INT_MAX;
  FOR(i, 0, m) cmin(ans, f[i][S - 1]);
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
