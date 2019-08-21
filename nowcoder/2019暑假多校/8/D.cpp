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

const int MAXS = 1e5 + 5;

void cmax(int &a, const int &b) {
  if (a < b) {
    a = b;
  }
}
void cmin(int &a, const int &b) {
  if (a > b) {
    a = b;
  }
}

int n, m, h, q;

struct BIT {
  int a[MAXS];

  void init() {
    FOR(i, 0, MAXS) { a[i] = -INF; }
  }

  int &get_value(int x, int y, int z) {
    return a[x + (y - 1) * n + (z - 1) * n * m];
  }

  void update(int x, int y, int z, const int &val) {
    for (int i = x; i <= n; i += i & -i) {
      for (int j = y; j <= m; j += j & -j) {
        for (int k = z; k <= h; k += k & -k) {
          cmax(get_value(i, j, k), val);
        }
      }
    }
  }

  int query(int x, int y, int z) {
    int res = -INF;
    for (int i = x; i > 0; i -= i & -i) {
      for (int j = y; j > 0; j -= j & -j) {
        for (int k = z; k > 0; k -= k & -k) {
          cmax(res, get_value(i, j, k));
        }
      }
    }
    return res;
  }
} bit[8];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cout << fixed << setprecision(10);

  cin >> n >> m >> h >> q;

  FOR(i, 0, 8) { bit[i].init(); }

  int opt, x, y, z;
  while (q--) {
    cin >> opt >> x >> y >> z;
    if (opt == 1) {
      bit[0].update(x, y, z, x + y + z);
      bit[1].update(x, y, h + 1 - z, x + y - z);
      bit[2].update(x, m + 1 - y, z, x - y + z);
      bit[3].update(n + 1 - x, y, z, -x + y + z);
      bit[4].update(x, m + 1 - y, h + 1 - z, x - y - z);
      bit[5].update(n + 1 - x, y, h + 1 - z, -x + y - z);
      bit[6].update(n + 1 - x, m + 1 - y, z, -x - y + z);
      bit[7].update(n + 1 - x, m + 1 - y, h + 1 - z, -x - y - z);
    } else {
      int ans = INT_MAX;
      cmin(ans, x + y + z - bit[0].query(x, y, z));
      cmin(ans, x + y - z - bit[1].query(x, y, h + 1 - z));
      cmin(ans, x - y + z - bit[2].query(x, m + 1 - y, z));
      cmin(ans, -x + y + z - bit[3].query(n + 1 - x, y, z));
      cmin(ans, x - y - z - bit[4].query(x, m + 1 - y, h + 1 - z));
      cmin(ans, -x + y - z - bit[5].query(n + 1 - x, y, h + 1 - z));
      cmin(ans, -x - y + z - bit[6].query(n + 1 - x, m + 1 - y, z));
      cmin(ans, -x - y - z - bit[7].query(n + 1 - x, m + 1 - y, h + 1 - z));
      cout << ans << "\n";
    }
  }

  return 0;
}
