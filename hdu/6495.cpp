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

const int INF = 0x3ffffff;
const ll LL_INF = 0x3fffffffffffffffll;
const int MOD = 1e9 + 7;
const ll HASH_KEY = 6151;
const ll HASH_MOD = 1610612741;

// mt19937 rdm(chrono::steady_clock::now().time_since_epoch().count());
// uniform_int_distribution<int> u_int(begin, end);
// uniform_real_distribution<double> u_read(begin, end);
/* -- HEAD END -- */

const int MAXN = 1003;

ll f[MAXN][MAXN];
int a[MAXN], b[MAXN], c[MAXN];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  MUL_CASE {
    int n, m;
    cin >> n >> m;
    FOR(i, 0, n) { cin >> a[i] >> b[i] >> c[i]; }
    FOR2(i, 0, n + 1, j, 0, n + 1) { f[i][j] = 0; }
    f[0][0] = m;
    FOR2(i, 0, n, j, 0, i + 1) {
      if (f[i][j] == 0) {
        continue;
      }
      f[i + 1][j] = max(f[i + 1][j], f[i][j] + c[i]);
      if (min(f[i][j], ll(b[i])) > a[i]) {
        f[i + 1][j + 1] =
            max(f[i + 1][j + 1], min(f[i][j], ll(b[i])) - a[i] + c[i]);
      }
    }
    REP(i, 0, n + 1) {
      if (f[n][i] > 0) {
        cout << i << "\n";
        break;
      }
    }
  }

  return 0;
}
