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
  cout << "debug: " << __FUNCTION__ << "() @ " << __TIMESTAMP__ << "\n"        \
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

const int MAXN = 3e3 + 3;

int h[MAXN][MAXN], mi[MAXN][MAXN];
int que[MAXN], head, tail;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  int n, m, a, b, x, y, z, g;
  cin >> n >> m >> a >> b;
  cin >> g >> x >> y >> z;

  FOR2(i, 0, n, j, 0, m) {
    h[i][j] = g;
    g = (1LL * x * g + y) % z;
  }

  FOR(i, 0, n) {
    head = tail = 0;
    FOR(j, 0, b) {
      while (head < tail && h[i][j] <= h[i][que[tail - 1]]) {
        --tail;
      }
      que[tail++] = j;
    }
    mi[i][b - 1] = h[i][que[head]];

    FOR(j, b, m) {
      if (j - que[head] >= b) {
        ++head;
      }
      while (head < tail && h[i][j] <= h[i][que[tail - 1]]) {
        --tail;
      }
      que[tail++] = j;
      mi[i][j] = h[i][que[head]];
    }
  }

  ll ans = 0;
  FOR(j, b - 1, m) {
    head = tail = 0;
    FOR(i, 0, a) {
      while (head < tail && mi[i][j] <= mi[que[tail - 1]][j]) {
        --tail;
      }
      que[tail++] = i;
    }
    ans += mi[que[head]][j];
    FOR(i, a, n) {
      if (i - que[head] >= a) {
        ++head;
      }
      while (head < tail && mi[i][j] <= mi[que[tail - 1]][j]) {
        --tail;
      }
      que[tail++] = i;
      ans += mi[que[head]][j];
    }
  }

  cout << ans << "\n";

  return 0;
}
