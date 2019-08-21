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

typedef pair<ll, ll> pll;
const int MAXN = 1e5;

pll p[MAXN];
multiset<ll> s1, s2;

int main(int argc, char *argv[]) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cout << fixed << setprecision(10);

  MUL_CASE {
    int n;
    cin >> n;
    FOR(i, 0, n) cin >> p[i].first >> p[i].second;
    sort(p, p + n);
    s1.clear(), s2.clear();
    FOR(i, 0, n) s2.insert(p[i].second);

    ll ans = LLONG_MAX;
    FOR(i, 0, n) {
      auto it = s2.lower_bound(p[i].second);
      s2.erase(it);
      if (!s2.empty()) ans = min(ans, abs(p[i].first - *s2.rbegin()));
      if (!s1.empty()) {
        it = s1.lower_bound(p[i].first);
        if (it != s1.end() && (s2.empty() || *it > *s2.rbegin()))
          ans = min(ans, *it - p[i].first);
        if (it != s1.begin() && (s2.empty() || *prev(it) > *s2.rbegin()))
          ans = min(ans, p[i].first - *prev(it));
      }
      s1.insert(p[i].second);
    }
    cout << ans << '\n';
  }

  return 0;
}
