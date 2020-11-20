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

const int MAXN = 1e5 + 5;

set<pii> xy, yx, sum, delta;
int n, x[MAXN], y[MAXN];

bool gao(int i) {
  int sx = x[i - 1];
  int sy = y[i - 1];
  int ex = x[i];
  int ey = y[i];

  if (sx == ex) {
    if (sy > ey) swap(sy, ey);
    auto it = xy.upper_bound(make_pair(sx, sy));
    return it->second ^ ey;
  }
  if (sy == ey) {
    if (sx > ex) swap(sx, ex);
    auto it = yx.upper_bound(make_pair(sy, sx));
    return it->second ^ ex;
  }
  if (sx + sy == ex + ey) {
    int l = min(sx, ex), r = sx ^ ex ^ l;
    auto it = sum.upper_bound(make_pair(sx + sy, l));
    return it->second ^ r;
  }
  if (sx - sy == ex - ey) {
    int l = min(sx, ex), r = sx ^ ex ^ l;
    auto it = delta.upper_bound(make_pair(sx - sy, l));
    return it->second ^ r;
  }
  return true;
}

void solve() {
  cin >> n;
  xy.clear(), yx.clear(), sum.clear(), delta.clear();
  for (int i = 1; i <= n; ++i) {
    cin >> x[i] >> y[i];
    xy.emplace(x[i], y[i]);
    yx.emplace(y[i], x[i]);
    sum.emplace(x[i] + y[i], x[i]);
    delta.emplace(x[i] - y[i], x[i]);
  }
  int ans = n;
  x[0] = y[0] = 0;
  xy.emplace(0, 0);
  yx.emplace(0, 0);
  sum.emplace(0, 0);
  delta.emplace(0, 0);
  for (int i = 0; i < n; ++i) {
    if (gao(i + 1)) {
      ans = i;
      break;
    }
    xy.erase(make_pair(x[i], y[i]));
    yx.erase(make_pair(y[i], x[i]));
    sum.erase(make_pair(x[i] + y[i], x[i]));
    delta.erase(make_pair(x[i] - y[i], x[i]));
  }
  cout << ans << '\n';
}

int main(int argc, char *argv[]) {
  freopen("queen2.in", "r", stdin);
  freopen("queen2.out", "w", stdout);
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout << fixed << setprecision(10);

  int o_o;
  for (o_o = 1; o_o; --o_o) solve();

  return 0;
}
