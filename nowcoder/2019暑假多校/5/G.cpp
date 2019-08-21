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
  cerr << "debug: " << __FUNCTION__ << "() @ " << __TIMESTAMP__ << "\n"        \
       << __FILE__ << " L" << __LINE__ << "\n"                                 \
       << #x " = " << (x) << endl

const int INF = 0x3ffffff;
const ll LL_INF = 0x3fffffffffffffffll;
const int MOD = 998244353;
const ll HASH_KEY = 6151;
const ll HASH_MOD = 1610612741;

// mt19937 rdm(chrono::steady_clock::now().time_since_epoch().count());
// uniform_int_distribution<int> u_int(begin, end);
// uniform_real_distribution<double> u_read(begin, end);
/* -- HEAD END -- */

const int MAXN = 3e3 + 5;

char s[MAXN], t[MAXN];
int dp[MAXN][MAXN][3], p2[MAXN], sum[3][MAXN];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cout << fixed << setprecision(10);

  p2[0] = 1;
  FOR(i, 1, MAXN) { p2[i] = 2LL * p2[i - 1] % MOD; }

  auto add = [&](int &a, const int &b) {
    a += b;
    if (a >= MOD) {
      a -= MOD;
    }
  };

  MUL_CASE {
    int n, m;
    cin >> n >> m >> (s + 1) >> (t + 1);

    int ans = 0;

    dp[0][0][0] = 1;
    dp[0][0][1] = 0;
    dp[0][0][2] = 0;

    // 0 : == , 1 : >, 2 : <

    FOR(i, 0, m + 1) { sum[0][i] = sum[1][i] = sum[2][i] = 0; }
    sum[0][0] = 1;
    FOR(i, 1, n + 1) REP(j, 1, m + 1) {
      int &f0 = dp[i][j][0] = 0;
      int &f1 = dp[i][j][1] = 0;
      int &f2 = dp[i][j][2] = 0;

      if (s[i] == '0' && j == 1) {
        continue;
      }

      // 0
      if (s[i] == t[j]) {
        f0 = sum[0][j - 1];
      }

      // 1
      f1 = sum[1][j - 1];
      if (s[i] > t[j]) {
        add(f1, sum[0][j - 1]);
      }

      // 2
      f2 = sum[2][j - 1];
      if (s[i] < t[j]) {
        add(f2, sum[0][j - 1]);
      }

      // debug("i = %d, j = %d, 0: %d, 1: %d, 2: %d\n", i, j, f0, f1, f2);

      add(sum[0][j], f0);
      add(sum[1][j], f1);
      add(sum[2][j], f2);

      if (j == m) {
        ans = (ans + 1LL * f1 * p2[n - i] + 1LL * (f0 + f2) * (p2[n - i] - 1)) %
              MOD;
      }
    }

    cout << ans << "\n";
  }

  return 0;
}
