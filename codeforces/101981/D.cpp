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

const int MAXN = 100;
struct Point {
  double x, y, z;
} p[MAXN];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cout << setprecision(10);

  int n;
  cin >> n;
  FOR(i, 0, n) { cin >> p[i].x >> p[i].y >> p[i].z; }
  auto dis = [&](const Point &a, const Point &b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) +
                (a.z - b.z) * (a.z - b.z));
  };
  Point c;
  c.x = c.y = c.z = 0;
  double ans = 1e18, x = 10000;
  FOR(step, 0, 10000) {
    int s = 0;
    double mx = dis(c, p[0]);
    FOR(i, 1, n) {
      double d = dis(c, p[i]);
      if (d > mx) {
        mx = d;
        s = i;
      }
    }
    ans = min(ans, mx);
    c.x += (p[s].x - c.x) / mx * x;
    c.y += (p[s].y - c.y) / mx * x;
    c.z += (p[s].z - c.z) / mx * x;
    x *= 0.99;
  }
  debug("%lf %lf %lf %lf\n", c.x, c.y, c.z, x);
  cout << ans << "\n";
  return 0;
}
