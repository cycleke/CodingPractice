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

const int MAXN = 2e3 + 5;

char s[MAXN][MAXN];
int cols[MAXN], rows[MAXN];
bool l[MAXN][MAXN], r[MAXN][MAXN], u[MAXN][MAXN], d[MAXN][MAXN], mark[MAXN];
int sc[MAXN][MAXN], sr[MAXN][MAXN];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cout << fixed << setprecision(10);

  int n, k;
  cin >> n >> k;
  FOR(i, 1, n + 1) { cin >> (s[i] + 1); }

  FOR(i, 1, n + 1) {
    int x = 1;
    FOR(j, 1, n + 1) {
      if (s[i][j] == 'B') {
        x = 0;
        break;
      }
    }
    rows[i] = rows[i - 1] + x;
  }
  FOR(i, 1, n + 1) {
    int x = 1;
    FOR(j, 1, n + 1) {
      if (s[j][i] == 'B') {
        x = 0;
        break;
      }
    }
    cols[i] = cols[i - 1] + x;
  }

  fill(mark + 1, mark + n + 1, 1);
  FOR(i, 1, n + 1) {
    FOR(j, 1, n + 1) {
      u[i][j] = mark[j];
      if (s[i][j] == 'B') {
        mark[j] = 0;
      }
    }
  }
  fill(mark + 1, mark + n + 1, 1);
  FOR(j, 1, n + 1) {
    FOR(i, 1, n + 1) {
      l[i][j] = mark[i];
      if (s[i][j] == 'B') {
        mark[i] = 0;
      }
    }
  }
  fill(mark + 1, mark + n + 1, 1);
  REP(i, 1, n + 1) {
    FOR(j, 1, n + 1) {
      d[i][j] = mark[j];
      if (s[i][j] == 'B') {
        mark[j] = 0;
      }
    }
  }
  fill(mark + 1, mark + n + 1, 1);
  REP(j, 1, n + 1) {
    FOR(i, 1, n + 1) {
      r[i][j] = mark[i];
      if (s[i][j] == 'B') {
        mark[i] = 0;
      }
    }
  }
  /*

  FOR(i, 1, n + 1) { debug("%d rows:%d cols:%d\n", i, rows[i], cols[i]); }

  FOR2(i, 1, n + 1, j, 1, n + 1) {
    debug("(%d,%d) l:%d r:%d u:%d d:%d\n", i, j, l[i][j], r[i][j], u[i][j],
          d[i][j]);
  }
  */
  FOR2(i, 1, n + 1, j, 1, n + 1) {
    if (j >= k) {
      sr[i][j] = sr[i - 1][j] + (l[i][j - k + 1] && r[i][j]);
    }
    if (i >= k) {
      sc[i][j] = sc[i][j - 1] + (u[i - k + 1][j] && d[i][j]);
    }
    // debug("(%d,%d) sr:%d sc:%d\n", i, j, sr[i][j], sc[i][j]);
  }

  int ans = 0;
  FOR2(i, k, n + 1, j, k, n + 1) {
    ans =
        max(ans, rows[i - k] + rows[n] - rows[i] + sr[i][j] - sr[i - k][j] +
                     cols[j - k] + cols[n] - cols[j] + sc[i][j] - sc[i][j - k]);
  }
  cout << ans << "\n";

  return 0;
}
