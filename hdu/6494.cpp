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

const int MAXN = 10001;
int f[MAXN][11][11];
char s[MAXN];

struct Data {
  int x, y, z;
  Data(int i, int j) {
    if (i == 11 || j == 11) {
      x = y = 0;
      z = 1;
    } else {
      z = 0;
      if (i == 10 && j == 10) {
        x = y = 9;
      } else {
        x = i;
        y = j;
      }
    }
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  MUL_CASE {
    cin >> s;
    int n = strlen(s);
    memset(f, -1, sizeof(f));
    f[0][0][0] = 0;
    FOR(i, 1, n + 1) {
      FOR2(j, 0, 11, k, 0, 11) {
        if (f[i - 1][j][k] == -1) {
          continue;
        }
        if (s[i - 1] == 'A' || s[i - 1] == '?') {
          Data d(j + 1, k);
          f[i][d.x][d.y] = max(f[i][d.x][d.y], f[i - 1][j][k] + d.z);
        }
        if (s[i - 1] == 'B' || s[i - 1] == '?') {
          Data d(j, k + 1);
          f[i][d.x][d.y] = max(f[i][d.x][d.y], f[i - 1][j][k] + d.z);
        }
      }
    }
    int ans = 0;
    FOR2(j, 0, 11, k, 0, 11) { ans = max(ans, f[n][j][k]); }
    cout << ans << "\n";
  }

  return 0;
}
