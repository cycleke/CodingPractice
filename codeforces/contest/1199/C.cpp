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

const int MAXN = 4e5 + 3;

map<int, int> cnt;
pii a[MAXN];

int main() {

  // freopen("input.txt", "r", stdin);

  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  int n, I;
  cin >> n >> I;

  int k = 8 * I / n;

  FOR(i, 0, n) {
    int x;
    cin >> x;
    ++cnt[x];
  }

  // dbg(k);
  int m = 0;
  for (auto p : cnt) {
    a[m++] = p;
  }

  if (ceil(log(m) / log(2)) <= k) {
    cout << "0\n";
    return 0;
  }

  sort(a, a + m);
  int L = 1 << k, it = 0;
  int ans = 0, cur = 0;

  FOR(i, 0, m) {
    while (it < m && it - i + 1 <= L) {
      cur += a[it++].second;
    }
    ans = max(ans, cur);
    cur -= a[i].second;
  }

  cout << n - ans << "\n";
  return 0;
}
