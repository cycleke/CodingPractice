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

const int MAXN = 27000 + 3;

int tree[MAXN], n, m, k;
int ans, a[MAXN], una[MAXN], unc, res[MAXN];
int L[MAXN], R[MAXN], IDX[MAXN];

void modify(int p, int delta) {
  for (; p <= unc; p += p & -p) {
    tree[p] += delta;
  }
}
int query(int p) {
  int res = 0;
  for (; p > 0; p -= p & -p) {
    res += tree[p];
  }
  return res;
}

struct Event {
  int l, r, _l, idx;

  bool operator<(const Event &a) const {
    return (_l == a._l) ? r < a.r : _l < a._l;
  }
} e[MAXN];

void add(int id) {
  ans += query(R[id]) - query(L[id] - 1);
  modify(IDX[id], 1);
}
void del(int id) {
  ans -= query(R[id]) - query(L[id] - 1) - 1;
  modify(IDX[id], -1);
}

int main() {

  // freopen("input.txt", "r", stdin);

  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  cin >> n >> m >> k;
  FOR(i, 1, n + 1) {
    cin >> a[i];
    una[++unc] = a[i];
  }
  sort(una + 1, una + unc + 1);
  unc = unique(una + 1, una + unc + 1) - una - 1;

  FOR(i, 1, n + 1) {
    L[i] = lower_bound(una + 1, una + unc + 1, a[i] - k) - una;
    R[i] = upper_bound(una + 1, una + unc + 1, a[i] + k) - una - 1;
    IDX[i] = lower_bound(una + 1, una + unc + 1, a[i]) - una;
  }

  int block = sqrt(n);

  FOR(i, 0, m) {
    int l, r;
    cin >> l >> r;
    e[i] = (Event){l, r, l / block, i};
  }
  sort(e, e + m);

  int l = 1, r = 0;
  FOR(i, 0, m) {
    while (l > e[i].l) {
      add(--l);
    }
    while (r < e[i].r) {
      add(++r);
    }
    while (l < e[i].l) {
      del(l++);
    }
    while (r > e[i].r) {
      del(r--);
    }
    res[e[i].idx] = ans;
  }
  FOR(i, 0, m) { cout << res[i] << "\n"; }

  return 0;
}
