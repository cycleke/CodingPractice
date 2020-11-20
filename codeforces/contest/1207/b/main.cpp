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

const int MAXN = 50;

int a[MAXN][MAXN], b[MAXN][MAXN];

int main(int argc, char *argv[]) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cout << fixed << setprecision(10);

  int n, m;
  cin >> n >> m;
  FOR2(i, 0, n, j, 0, m) cin >> a[i][j];

  vector<pii> ops;
  FOR2(i, 0, n - 1, j, 0, m - 1) {
    bool able = a[i][j] && a[i + 1][j] && a[i][j + 1] && a[i + 1][j + 1];
    if (able && !(b[i][j] && b[i + 1][j] && b[i][j + 1] && b[i + 1][j + 1])) {
      b[i][j] = 1;
      b[i + 1][j] = 1;
      b[i][j + 1] = 1;
      b[i + 1][j + 1] = 1;
      ops.emplace_back(i + 1, j + 1);
    }
  }
  bool ok = true;
  FOR2(i, 0, n, j, 0, m)
  ok &= a[i][j] == b[i][j];

  if (ok) {
    cout << ops.size() << '\n';
    for (pii &p : ops) cout << p.first << ' ' << p.second << '\n';
  } else {
    cout << "-1\n";
  }

  return 0;
}
