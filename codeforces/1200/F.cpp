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

const int MAXN = 1e3;
const int LCM = 2520;

int k[MAXN], e[10], ans[MAXN][LCM];
pii nxt[MAXN][LCM], mark[MAXN][LCM];

void dfs(int x, int y, const pii &st) {
  mark[x][y] = st;
  int _x = nxt[x][y].first;
  int _y = nxt[x][y].second;

  if (mark[_x][_y] == pii(-1, -1)) {
    dfs(_x, _y, st);
    ans[x][y] = ans[_x][_y];
  } else {
    if (mark[_x][_y] == st) {
      int cx = x;
      int cy = y;
      static set<int> s;
      s.clear();
      do {
        s.insert(cx);
        _x = nxt[cx][cy].first;
        _y = nxt[cx][cy].second;
        cx = _x;
        cy = _y;
      } while (cx != x || cy != y);
      ans[x][y] = s.size();
    } else {
      ans[x][y] = ans[_x][_y];
    }
  }
}

int main() {

  // freopen("input.txt", "r", stdin);

  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cout << fixed << setprecision(10);

  int n;
  cin >> n;
  FOR(i, 0, n) {
    cin >> k[i];
    k[i] %= LCM;
    if (k[i] < 0) {
      k[i] += LCM;
    }
  }
  FOR(i, 0, n) {
    int m;
    cin >> m;
    FOR(j, 0, m) {
      cin >> e[j];
      --e[j];
    }
    FOR(j, 0, LCM) {
      int c = (k[i] + j) % LCM;
      int v = e[c % m];
      nxt[i][j] = {v, c};
    }
  }

  memset(ans, -1, sizeof(ans));
  memset(mark, -1, sizeof(mark));
  FOR(i, 0, n) {
    FOR(j, 0, LCM) {
      if (mark[i][j] != pii(-1, -1)) {
        continue;
      }
      dfs(i, j, {i, j});
    }
  }

  int q;
  cin >> q;
  while (q--) {
    int x, y;
    cin >> x >> y;
    cout << ans[x - 1][(y % LCM + LCM) % LCM] << "\n";
  }

  return 0;
}
