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

const int MAXN = 100;
const int MAXM = 1e6;

int d[MAXN][MAXN], p[MAXM];

inline void cmin(int &a, const int &b) {
  if (a > b) a = b;
}

int main(int argc, char *argv[]) {
  // freopen("in1.txt", "r", stdin);
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cout << fixed << setprecision(10);

  int n, m;
  cin >> n;
  FOR(i, 0, n) {
    string s;
    cin >> s;
    FOR(j, 0, n) d[i][j] = s[j] == '1' ? 1 : INF;
    d[i][i] = 0;
  }
  FOR(k, 0, n) FOR2(i, 0, n, j, 0, n) cmin(d[i][j], d[i][k] + d[k][j]);

  cin >> m;
  FOR(i, 0, m) cin >> p[i], --p[i];

  int k = 2;
  FOR(i, 2, m) {
    while (k >= 2 &&
           d[p[k - 2]][p[i]] == d[p[k - 2]][p[k - 1]] + d[p[k - 1]][p[i]])
      --k;

    p[k] = p[i];
    ++k;
  }
  cout << k << '\n';
  FOR(i, 0, k) cout << p[i] + 1 << ' ';

  return 0;
}
