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

const int INF = 0x3ffffff;
const int MOD = 1e9 + 7;
const ll HASH_KEY = 6151;
const ll HASH_MOD = 1610612741;

// mt19937 rdm(chrono::steady_clock::now().time_since_epoch().count());

const int MAXN = 1e6 + 3;

int a[MAXN];
int fac[MAXN], p[MAXN], pp[MAXN];
bool vis[MAXN];
vi primes;

void silver() {
  FOR(i, 2, MAXN) {
    if (!vis[i]) {
      primes.push_back(i);
      fac[i] = i;
    }
    for (int prime : primes) {
      int t = prime * i;
      if (t >= MAXN) {
        break;
      }
      vis[t] = true;
      fac[t] = prime;
      if (i % prime == 0) {
        break;
      }
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  silver();

  int n;
  cin >> n;
  FOR(i, 0, n) { cin >> a[i]; }

  ll ans = 0;
  FOR(i, 0, n) {
    int x = a[i];
    while (x != 1) {
      int f = fac[x];
      while (fac[x] == f) {
        x /= f;
      }
      ans += ll(p[f] - pp[f]) * (n - p[f] + 1);
      // cout << "DEBUG: " << f << " [" << pp[f] << ", " << p[f] << ", " << i +
      // 1   << "]\n";
      pp[f] = p[f];
      p[f] = i + 1;
    }
  }

  for (int prime : primes) {
    ans += ll(p[prime] - pp[prime]) * (n + 1 - p[prime]);
  }

  cout << ans << "\n";
  return 0;
}
