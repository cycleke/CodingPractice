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
const int MOD = 1e9 + 7;
const ll HASH_KEY = 6151;
const ll HASH_MOD = 1610612741;

// mt19937 rdm(chrono::steady_clock::now().time_since_epoch().count());
// uniform_int_distribution<int> u_int(begin, end);
// uniform_real_distribution<double> u_read(begin, end);
/* -- HEAD END -- */

const int MAXL = 1e6 + 5;

typedef int Mat[2][2];

Mat A, B, C, D;
char sn[MAXL];
int n[MAXL], two[MAXL * 4];

inline void mul(Mat A, Mat B, int mod) {
  FOR2(i, 0, 2, j, 0, 2) {
    C[i][j] = 0;
    FOR(k, 0, 2) { C[i][j] = (C[i][j] + 1LL * A[i][k] * B[k][j]) % mod; }
  }
  FOR2(i, 0, 2, j, 0, 2) { A[i][j] = C[i][j]; }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cout << fixed << setprecision(10);

  int x0, x1, a, b, mod, l;

  cin >> x0 >> x1 >> a >> b >> sn >> mod;

  l = strlen(sn);

  if (l == 1 && sn[0] == '1') {
    cout << x1;
    return 0;
  }

  FOR(i, 0, l) { n[i] = sn[l - 1 - i] - '0'; }
  --n[0];

  FOR(i, 0, l) {
    if (n[i] < 0) {
      n[i] += 10;
      --n[i + 1];
    } else {
      break;
    }
  }

  A[0][0] = A[1][1] = 1;
  A[0][1] = A[1][0] = 0;

  B[0][0] = a;
  B[0][1] = b;
  B[1][0] = 1;
  B[1][1] = 0;

  FOR(i, 0, l) {
    FOR(j, 0, n[i]) { mul(A, B, mod); }
    memcpy(D, B, sizeof(B));

    FOR2(x, 0, 2, y, 0, 2) { D[x][y] = B[x][y]; }
    FOR(j, 0, 9) { mul(B, D, mod); }
  }

  cout << (1LL * A[0][0] * x1 + 1LL * A[0][1] * x0) % mod << "\n";

  return 0;
}

