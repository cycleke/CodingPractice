#include <assert.h>
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

const int INF = 0x3ffffff;
const ll LL_INF = 0x3fffffffffffffffll;
const int MOD = 1e9 + 7;
const ll HASH_KEY = 6151;
const ll HASH_MOD = 1610612741;

// mt19937 rdm(chrono::steady_clock::now().time_since_epoch().count());
// uniform_int_distribution<int> u_int(begin, end);
// uniform_real_distribution<double> u_read(begin, end);
/* -- HEAD END -- */

const int MAXK = 2e5 + 3;

ll s[MAXK], sz[MAXK];
ll k, m, n, p;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  while (cin >> k >> m >> n >> p) {

    FOR(i, 0, k) { cin >> s[i]; }
    sort(s, s + k);

    ll res = 0;
    int idx = 0, nodes = 1;
    FOR(i, 1, m) {
      nodes *= n;
      idx += nodes;
    }
    REP(i, 0, idx) {
      sz[i] = 1;
      int id = (i + 1) * n;
      FOR(j, 0, n) {
        if (id >= idx) {
          break;
        }
        sz[i] += sz[id++];
      }
      res = (res + sz[i] * s[i] % p) % p;
    }

    cout << res << "\n";
  }
  return 0;
}
