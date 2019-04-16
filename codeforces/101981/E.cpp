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

const int MAXN = 1e6 + 3;
int n, k;
char s1[MAXN], s2[MAXN];

int gao(char *s) {
  static int top, stk[MAXN], cnt[MAXN];
  top = 0;
  FOR(i, 0, n) {
    if (top && stk[top - 1] == s[i] - '0') {
      ++cnt[top - 1];
      if (cnt[top - 1] == k) {
        --top;
      }
    } else {
      stk[top] = s[i] - '0';
      cnt[top] = 1;
      ++top;
    }
  }
  int l = 0;
  FOR2(i, 0, top, j, 0, cnt[i]) s[l++] = stk[i];
  return l;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  cin >> n >> k >> s1 >> s2;
  if (k == 1) {
    cout << "Yes\n";
    return 0;
  }
  int l1 = gao(s1);
  int l2 = gao(s2);

  bool flag = l1 == l2;
  if (l1 == l2) {
    FOR(i, 0, l1) {
      if (s1[i] != s2[i]) {
        flag = false;
        break;
      }
    }
  }
  cout << (flag ? "Yes\n" : "No\n");
  return 0;
}
