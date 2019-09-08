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
const int MOD = 1e9 + 7;
const ll HASH_KEY = 6151;
const ll HASH_MOD = 1610612741;

// mt19937 rdm(chrono::steady_clock::now().time_since_epoch().count());
// uniform_int_distribution<int> u_int(begin, end);
// uniform_real_distribution<double> u_read(begin, end);
/* -- HEAD END -- */

const int MAXL = 3e5 + 5;

struct PT {
  char s[MAXL];
  int fail[MAXL], ch[26][MAXL], l[MAXL], dep[MAXL], lst, nc, n, cnt[MAXL];
  void init() {
    l[0] = 0;
    l[1] = -1;
    fail[0] = fail[1] = 1;
    for (int i = 0; i < 26; ++i) {
      for (int j = 0; j < nc; ++j) { ch[i][j] = 0; }
    }
    for (int i = 2; i < nc; ++i) {
      l[i] = 0;
      fail[i] = 0;
    }

    lst = 0;
    nc = 2;
    n = 0;
    s[0] = '#';
  }

  int insert(char c) {
    int id = c - 'a';
    s[++n] = c;
    while (s[n - l[lst] - 1] != s[n]) { lst = fail[lst]; }
    if (ch[id][lst] == 0) {
      l[nc] = l[lst] + 2;
      int f = fail[lst];
      while (s[n - l[f] - 1] != s[n]) { f = fail[f]; }
      fail[nc] = ch[id][f];
      dep[nc] = dep[fail[nc]] + 1;
      ch[id][lst] = nc;
      ++nc;
    }
    ++cnt[lst = ch[id][lst]];
    return lst;
  }

  void count() {
    for (int i = nc - 1; ~i; --i) cnt[fail[i]] += cnt[i];
  }
} pt;

char S[MAXL];
bool vis[26];
ll ans;

void dfs(int u, int cnt) {
  ans += 1LL * pt.cnt[u] * cnt;
  FOR(i, 0, 26) if (pt.ch[i][u]) {
    if (vis[i]) {
      dfs(pt.ch[i][u], cnt);
    } else {
      vis[i] = true;
      dfs(pt.ch[i][u], cnt + 1);
      vis[i] = false;
    }
  }
}

void solve() {
  cin >> S;
  int n = strlen(S);
  pt.init();
  FOR(i, 0, n) pt.insert(S[i]);
  ans = 0;
  pt.count();
  dfs(1, 0);
  dfs(0, 0);
  cout << ans << '\n';
}

int main(int argc, char *argv[]) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout << fixed << setprecision(10);

  int o_o;
  for (o_o = 1; o_o; --o_o) solve();

  return 0;
}
