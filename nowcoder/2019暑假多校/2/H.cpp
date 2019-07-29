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

const int MAXN = 1e3 + 5;

char a[MAXN][MAXN];
int h[MAXN], l[MAXN], r[MAXN];
bool vis[MAXN];
vi bound[MAXN];

int main() {

  int n, m;
  scanf("%d %d", &n, &m);
  FOR(i, 1, n + 1) { scanf("%s", a[i] + 1); }

  int top1 = 0, top2 = 0;
  static auto gao = [&](int area) {
    if (area >= top1) {
      top2 = top1;
      top1 = area;
    } else if (area > top2) {
      top2 = area;
    }
  };

  h[0] = h[m + 1] = -1;
  FOR(i, 1, n + 1) {
    FOR(j, 1, m + 1) { h[j] = (a[i][j] == '1') ? (h[j] + 1) : 0; }

    FOR(j, 1, m + 1) {
      int &k = l[j] = j;
      while (h[j] <= h[k - 1]) {
        k = l[k - 1];
      }
    }
    REP(j, 1, m + 1) {
      int &k = r[j] = j;
      while (h[j] <= h[k + 1]) {
        k = r[k + 1];
      }
    }

    FOR(j, 1, m + 1) {
      for (int &x : bound[j]) {
        vis[x] = false;
      }
      bound[j].clear();
      if (vis[h[j]]) {
        continue;
      }

      vis[h[j]] = true;
      bound[r[j] + 1].pb(h[j]);

      int width = r[j] - l[j] + 1;
      int height = h[j];
      gao(width * height);
      gao(width * height - width);
      gao(width * height - height);
    }

    for (int &x : bound[m + 1]) {
      vis[x] = false;
    }
    bound[m + 1].clear();
  }

  printf("%d\n", top2);

  return 0;
}
