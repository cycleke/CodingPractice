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
#define debug(...) // fprintf(stderr, __VA_ARGS__)

const int INF = 0x3ffffff;
const int MOD = 1e9 + 7;
const ll HASH_KEY = 6151;
const ll HASH_MOD = 1610612741;

// mt19937 rdm(chrono::steady_clock::now().time_since_epoch().count());
// uniform_int_distribution<int> u_int(begin, end);
// uniform_real_distribution<double> u_read(begin, end);
/* -- HEAD END -- */

const int MAXN = 1e6 + 3;
char S[MAXN], T[MAXN], revS[MAXN], ss[MAXN * 2];
ll hash_s[MAXN], hash_t[MAXN], P[MAXN];
int n, m, lcp[MAXN], p[MAXN * 2], pre[MAXN * 2];

void gen_hash(char *s, int n, ll *hash) {
  hash[0] = 0;
  FOR(i, 1, n + 1) { hash[i] = (hash[i - 1] * HASH_KEY + s[i - 1]) % HASH_MOD; }
}

void gen_lcp() {
  FOR(i, 0, n) {
    int &ans = lcp[i];
    if (revS[i] != T[0]) {
      ans = 0;
      continue;
    }
    int l = 1, r = min(n - i, m);
    while (l <= r) {
      int mid = (l + r) / 2;
      if ((HASH_MOD + hash_s[i + mid] - hash_s[i] * P[mid] % HASH_MOD) %
              HASH_MOD ==
          hash_t[mid]) {
        ans = mid;
        l = mid + 1;
      } else {
        r = mid - 1;
      }
    }
    debug("LCP %d %d\n", i, ans);
  }
}

void manacher() {
  ss[0] = '$';
  ss[1] = '#';
  int len = 2;
  FOR(i, 0, n) {
    ss[len++] = S[i];
    ss[len++] = '#';
  }
  ss[len] = 0;
  int id = 0, mx = 0;
  FOR(i, 1, len) {
    p[i] = i < mx ? min(p[2 * id - i], mx - i) : 1;
    while (ss[i - p[i]] == ss[i + p[i]])
      ++p[i];
    if (mx < i + p[i]) {
      id = i;
      mx = i + p[i];
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  cin >> S >> T;
  n = strlen(S);
  m = strlen(T);

  P[0] = 1;
  FOR(i, 1, MAXN) { P[i] = P[i - 1] * HASH_KEY % HASH_MOD; }
  FOR(i, 0, n) { revS[i] = S[n - 1 - i]; }
  debug("revS %s\n", revS);

  gen_hash(revS, n, hash_s);
  gen_hash(T, m, hash_t);
  gen_lcp();

  manacher();
  REP(i, 1, n * 2 + 1) {
    int x = i / 2;
    ++pre[x];
    --pre[x - (p[i] / 2)];
  }
  REP(i, 1, n + 1) {
    pre[i] += pre[i + 1];
    debug("PRE %d %d\n", i, pre[i]);
  }
  ll ans = 0;
  FOR(i, 1, n + 1) { ans += 1ll * lcp[n - i + 1] * pre[i]; }
  cout << ans << "\n";

  return 0;
}
