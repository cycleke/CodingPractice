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

#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define REP(i, a, b) for (int i = (b)-1; i >= a; --i)
#define FOR2(i, a, b, j, c, d) FOR(i, a, b) FOR(j, c, d)
#define REP2(i, a, b, j, c, d) REP(i, a, b) REP(j, c, d)
#define EACH(i, s) for (auto i = (s).begin(); i != (s).end(); ++i)
#define MUL_CASE                                                               \
  int o_o;                                                                     \
  cin >> o_o;                                                                  \
  for (int case_count = 0; case_count < o_o; ++case_count)
#define debug(...) fprintf(stderr, __VA_ARGS__)

const int INF = 0x3ffffff;
const int MOD = 1e9 + 7;
const ll HASH_KEY = 6151;
const ll HASH_MOD = 1610612741;

// mt19937 rdm(chrono::steady_clock::now().time_since_epoch().count());
// uniform_int_distribution<int> u_int(begin, end);
// uniform_real_distribution<double> u_read(begin, end);
/* -- HEAD END -- */

const int MAXN = 100000 + 3;

int n, m, p[MAXN * 2];
char s[MAXN], ss[MAXN * 2];
ll pre[MAXN * 2], suf[MAXN * 2], sum[MAXN * 2];

void manacher() {
  m = 0;
  ss[m++] = '$';
  ss[m++] = '#';
  FOR(i, 0, n) {
    ss[m++] = s[i];
    ss[m++] = '#';
  }
  ss[m] = 0;
  int mx = 0, id = 0;
  FOR(i, 0, m) {
    p[i] = mx > i ? min(p[2 * id - i], mx - i) : 1;
    while (ss[i - p[i]] == ss[i + p[i]])
      ++p[i];
    if (i + p[i] > mx) {
      id = i;
      mx = i + p[i];
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  while (cin >> s) {
    ZERO(pre);
    ZERO(suf);
    ZERO(sum);

    n = strlen(s);
    manacher();

    FOR(i, 2, 2 * n + 1) {
      int x = (i + 1) / 2;
      ++suf[x];
      --suf[x + (p[i] / 2)];
    }
    REP(i, 2, 2 * n + 1) {
      int x = i / 2;
      ++pre[x];
      --pre[x - (p[i] / 2)];
    }
    REP(i, 1, n + 1) { pre[i] += pre[i + 1]; }
    FOR(i, 1, n + 1) {
      suf[i] += suf[i - 1];
      sum[i] = sum[i - 1] + suf[i];
    }
    ll ans = 0;
    FOR(i, 1, n + 1) { ans += pre[i] * sum[i - 1]; }
    cout << ans << "\n";
  }

  return 0;
}
