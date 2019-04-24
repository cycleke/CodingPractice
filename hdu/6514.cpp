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
#define debug(...) // fprintf(stderr, __VA_ARGS__)

const int INF = 0x3ffffff;
const ll LL_INF = 0x3fffffffffffffffll;
const int MOD = 1e9 + 7;
const ll HASH_KEY = 6151;
const ll HASH_MOD = 1610612741;

// mt19937 rdm(chrono::steady_clock::now().time_since_epoch().count());
// uniform_int_distribution<int> u_int(begin, end);
// uniform_real_distribution<double> u_read(begin, end);
/* -- HEAD END -- */

const int MAXN = 2e7 + 3;
int s[MAXN], g[MAXN];

#define gao(x, y) ((x - 1 + 1) * (m) + ((y) + 1))

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  int n, m, p, q;
  while (cin >> n >> m) {
    ZERO(s);
    ZERO(g);
    cin >> p;
    FOR(step, 0, p) {
      int a, b, c, d;
      cin >> a >> b >> c >> d;
      ++g[gao(a, b)];
      --g[gao(a, d + 1)];
      --g[gao(c + 1, b)];
      ++g[gao(c + 1, d + 1)];
    }

    FOR2(i, 1, n + 1, j, 1, m + 1) {
      g[gao(i, j)] = g[gao(i, j)] - g[gao(i - 1, j - 1)] + g[gao(i, j - 1)] +
                     g[gao(i - 1, j)];
      int t = min(g[gao(i, j)], 1);

      s[gao(i, j)] =
          t - s[gao(i - 1, j - 1)] + s[gao(i, j - 1)] + s[gao(i - 1, j)];
    }

    cin >> q;
    FOR(step, 0, q) {
      int a, b, c, d;
      cin >> a >> b >> c >> d;
      int area = s[gao(c, d)] + s[gao(a - 1, b - 1)] - s[gao(a - 1, d)] -
                 s[gao(c, b - 1)];
      debug("%d\n", area);
      if (area == (d - b + 1) * (c - a + 1)) {
        cout << "YES\n";
      } else {
        cout << "NO\n";
      }
    }
  }

  return 0;
}
