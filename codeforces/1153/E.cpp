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

map<pair<pii, pii>, int> mark;

int ask(int x1, int y1, int x2, int y2) {
  if (EXIST(mark, make_pair(pii(x1, y1), pii(x2, y2)))) {
    return mark[make_pair(pii(x1, y1), pii(x2, y2))];
  }
  printf("? %d %d %d %d\n", x1, y1, x2, y2);
  fflush(stdout);
  int x;
  scanf("%d", &x);
  return mark[make_pair(pii(x1, y1), pii(x2, y2))] = (x & 1);
}

int main() {
  int n, p;
  scanf("%d", &n);
  for (p = 1; p < n; ++p) {
    if (ask(1, 1, n, p)) {
      break;
    }
  }

  auto gao = [&](int p, bool dir) {
    int l = 1, r = n;
    while (l < r) {
      int mid = (l + r + 1) / 2;
      if (dir ? ask(mid, p, n, p) : ask(p, mid, p, n)) {
        l = mid;
      } else {
        r = mid - 1;
      }
    }

    return l;
  };

  if (p < n) {
    int _p = n;
    for (; _p > 1; --_p) {
      if (ask(1, _p, n, n)) {
        break;
      }
    }
    printf("! %d %d %d %d\n", gao(p, true), p, gao(_p, true), _p);
  } else {
    for (p = 1; p < n; ++p) {
      if (ask(1, 1, p, n)) {
        break;
      }
    }
    int _p = n;
    for (; _p > 1; --_p) {
      if (ask(_p, 1, n, n)) {
        break;
      }
    }
    printf("! %d %d %d %d\n", p, gao(p, false), _p, gao(_p, false));
  }
  return 0;
}
