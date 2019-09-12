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
const ll HASH_KEY = 6151;
const ll HASH_MOD = 1610612741;

// mt19937 rdm(chrono::steady_clock::now().time_since_epoch().count());
// uniform_int_distribution<int> u_int(begin, end);
// uniform_real_distribution<double> u_read(begin, end);
/* -- HEAD END -- */

const int MAXN = 7;
const ull MOD = 2147493647;

typedef ull Mat[MAXN][MAXN];

void mul(Mat &a, const Mat &b) {
  static Mat c;
  ZERO(c);
  FOR2(i, 0, MAXN, j, 0, MAXN)
  FOR(k, 0, MAXN) c[i][j] = (c[i][j] + a[i][k] * b[k][j]) % MOD;
  memcpy(a, c, sizeof(c));
}

Mat A, B;

const Mat P = {{1, 2, 1, 4, 6, 4, 1}, {1, 0, 0, 0, 0, 0, 0},
               {0, 0, 1, 4, 6, 4, 1}, {0, 0, 0, 1, 3, 3, 1},
               {0, 0, 0, 0, 1, 2, 1}, {0, 0, 0, 0, 0, 1, 1},
               {0, 0, 0, 0, 0, 0, 1}};

void solve() {
  int n, a, b;
  cin >> n >> a >> b;
  if (n < 3) {
    cout << (n == 1 ? a : b) << '\n';
    return;
  }
  ZERO(A);
  memcpy(B, P, sizeof(P));
  FOR(i, 0, MAXN) A[i][i] = 1;
  for (n -= 2; n; n >>= 1, mul(B, B))
    if (n & 1) mul(A, B);
  ull ans = 0;
  const ull L[] = {1ULL * b, 1ULL * a, 16, 8, 4, 2, 1};
  FOR(i, 0, MAXN) ans = (ans + A[0][i] * L[i]) % MOD;
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
