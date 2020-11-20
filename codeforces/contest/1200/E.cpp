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

void get_next(char *S, int *nxt, int n) {
  nxt[0] = -1;
  int j = -1;
  for (int i = 1; i < n; ++i) {
    while ((~j) && S[j + 1] != S[i]) {
      j = nxt[j];
    }
    nxt[i] = (S[j + 1] == S[i]) ? (++j) : j;
  }
}

int pattern(char *S, char *T, int *nxt, int n, int m) {
  int j = -1;
  for (int i = 0; i < m; ++i) {
    while ((~j) && S[j + 1] != T[i]) {
      j = nxt[j];
    }
    j += S[j + 1] == T[i];
  }
  return j;
}

const int MAXL = 1e6 + 5;
char s[MAXL], ans[MAXL];
int nxt[MAXL];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cout << fixed << setprecision(10);

  int n;
  cin >> n;
  cin >> ans;
  int l2 = strlen(ans);
  FOR(i, 1, n) {
    cin >> s;
    int l1 = strlen(s);
    get_next(s, nxt, l1);
    int pl = min(l1, l2);
    int j = pattern(s, ans + l2 - pl, nxt, l1, pl);
    FOR(k, j + 1, l1) { ans[l2++] = s[k]; }
  }
  cout << ans << "\n";
  return 0;
}
