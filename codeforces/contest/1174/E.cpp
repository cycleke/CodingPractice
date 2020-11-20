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

#define fi first
#define se second
#define pb push_back
#define mp make_pair

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
  cout << "debug: " << __FUNCTION__ << "() @ " << __TIMESTAMP__ << "\n"        \
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

const int MAXN = 1e6 + 3;
int dp[MAXN][21][2];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  int n;
  cin >> n;
  int p = 0;
  while ((1 << p) <= n) {
    ++p;
  }

  auto gao = [&](const int &x, const int &y) {
    ll t = n >> x;
    return y ? t / 3 : t;
  };
  auto add = [&](int &x, const int &y) {
    x += y;
    if (x >= MOD) {
      x -= MOD;
    }
  };

  dp[1][p - 1][0] = 1;
  dp[1][p - 2][1] = gao(p - 2, 1);
  FOR(i, 1, n) {
    FOR(x, 0, p) {
      FOR(y, 0, 2) {
        add(dp[i + 1][x][y], dp[i][x][y] * (gao(x, y) - i) % MOD);
        if (x) {
          add(dp[i + 1][x - 1][y],
              dp[i][x][y] * (gao(x - 1, y) - gao(x, y)) % MOD);
        }
        if (y) {
          add(dp[i + 1][x][y - 1],
              dp[i][x][y] * (gao(x, y - 1) - gao(x, y)) % MOD);
        }
      }
    }
  }
  cout << dp[n][0][0] << "\n";

  return 0;
}
