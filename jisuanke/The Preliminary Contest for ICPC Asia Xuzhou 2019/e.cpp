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

const int MAXN = 5e5 + 5;

int n, m, cnt, a[MAXN], b[MAXN], c[MAXN], ans[MAXN];

void add(int x, const int &val) {
  for (; x; x &= x - 1) c[x] = max(c[x], val);
}
int ask(int x) {
  int res = -1;
  for (; x <= cnt; x += x & -x) res = max(res, c[x]);
  return res;
}

void solve() {
  cin >> n >> m;
  FOR(i, 0, n) cin >> a[i], b[i] = a[i];
  b[n] = INT_MAX;
  sort(b, b + n + 1);
  cnt = unique(b, b + n + 1) - b;
  memset(c, -1, sizeof(c));
  for (int i = n - 1, x; ~i; --i) {
    x = lower_bound(b, b + cnt, a[i] + m) - b;
    if (b[x] == INT_MAX) {
      ans[i] = -1;
    } else {
      ans[i] = max(-1, ask(x) - i - 1);
    }
    x = lower_bound(b, b + cnt, a[i]) - b;
    add(x, i);
  }
  cout << ans[0];
  FOR(i, 1, n) cout << ' ' << ans[i];
  cout << "\n";
}

int main(int argc, char *argv[]) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout << fixed << setprecision(10);

  int o_o;
  for (o_o = 1; o_o; --o_o) solve();

  return 0;
}
