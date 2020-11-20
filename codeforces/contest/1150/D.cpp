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
const int MAXL = 255;
const int ALPHA_SIZE = 26;

int nxt[MAXN][ALPHA_SIZE];
int dp[MAXL][MAXL][MAXL];

string WoU;
string religion[3];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  int n, m;
  cin >> n >> m >> WoU;

  FOR(i, 0, ALPHA_SIZE) { nxt[n][i] = nxt[n + 1][i] = n; }
  REP(i, 0, n) {
    FOR(j, 0, ALPHA_SIZE) {
      nxt[i][j] = (WoU[i] == 'a' + j) ? i : nxt[i + 1][j];
    }
  }

  auto gao = [&](int a, int b, int c) {
    int &x = dp[a][b][c];
    x = n;
    if (a > 0) {
      x = min(x, nxt[dp[a - 1][b][c] + 1][religion[0][a - 1] - 'a']);
    }
    if (b > 0) {
      x = min(x, nxt[dp[a][b - 1][c] + 1][religion[1][b - 1] - 'a']);
    }
    if (c > 0) {
      x = min(x, nxt[dp[a][b][c - 1] + 1][religion[2][c - 1] - 'a']);
    }
  };

  dp[0][0][0] = -1;
  while (m--) {
    char op;
    int reli;
    cin >> op >> reli;
    --reli;
    if (op == '+') {
      char alpha;
      cin >> alpha;
      religion[reli] += alpha;

      int en0 = religion[0].size();
      int en1 = religion[1].size();
      int en2 = religion[2].size();
      int bg0 = reli != 0 ? 0 : en0;
      int bg1 = reli != 1 ? 0 : en1;
      int bg2 = reli != 2 ? 0 : en2;

      for (int i = bg0; i <= en0; ++i) {
        for (int j = bg1; j <= en1; ++j) {
          for (int k = bg2; k <= en2; ++k) {
            gao(i, j, k);
          }
        }
      }
    } else {
      religion[reli].pop_back();
    }

    cout << (dp[religion[0].size()][religion[1].size()][religion[2].size()] < n
                 ? "YES\n"
                 : "NO\n");
  }

  return 0;
}
