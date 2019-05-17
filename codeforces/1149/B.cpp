#include <assert.h>
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

const int INF = 0x3ffffff;
const ll LL_INF = 0x3fffffffffffffffll;
const int MOD = 1e9 + 7;
const ll HASH_KEY = 6151;
const ll HASH_MOD = 1610612741;

// mt19937 rdm(chrono::steady_clock::now().time_since_epoch().count());
// uniform_int_distribution<int> u_int(begin, end);
// uniform_real_distribution<double> u_read(begin, end);
/* -- HEAD END -- */

const int MAXN = 1e5 + 3;
const int MAXT = 255;
const int ALPHA_SIZE = 26;

char s[MAXN], t[3][MAXT];
int dp[MAXT][MAXT][MAXT], nxt[MAXN][ALPHA_SIZE], lt[3];

int main() {

  // freopen("input.txt", "r", stdin);

  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  int n, m;
  cin >> n >> m >> s;

  FOR(i, 0, ALPHA_SIZE) { nxt[n][i] = nxt[n + 1][i] = n; }
  REP(i, 0, n) FOR(j, 0, ALPHA_SIZE) {
    nxt[i][j] = (s[i] == 'a' + j) ? i : nxt[i + 1][j];
  }

  auto gao = [&](int a, int b, int c) {
    int &x = dp[a][b][c];
    x = n;
    if (a > 0) {
      x = min(x, nxt[dp[a - 1][b][c] + 1][t[0][a - 1] - 'a']);
    }
    if (b > 0) {
      x = min(x, nxt[dp[a][b - 1][c] + 1][t[1][b - 1] - 'a']);
    }
    if (c > 0) {
      x = min(x, nxt[dp[a][b][c - 1] + 1][t[2][c - 1] - 'a']);
    }
  };

  dp[0][0][0] = -1;
  while (m--) {
    char op;
    int idx;
    cin >> op >> idx;
    // assert(op == '+' || op == '-');
    --idx;

    if (op == '+') {
      char ch;
      cin >> ch;
      t[idx][lt[idx]++] = ch;

      int ed0 = lt[0];
      int ed1 = lt[1];
      int ed2 = lt[2];
      int bg0 = idx != 0 ? 0 : ed0;
      int bg1 = idx != 1 ? 0 : ed1;
      int bg2 = idx != 2 ? 0 : ed2;

      FOR(i, bg0, ed0 + 1) FOR2(j, bg1, ed1 + 1, k, bg2, ed2 + 1) {
        gao(i, j, k);
      }
    } else {
      --lt[idx];
    }

    cout << (dp[lt[0]][lt[1]][lt[2]] < n ? "Yes\n" : "No\n");
  }
  return 0;
}
