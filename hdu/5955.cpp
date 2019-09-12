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

const int MAX_NODE = 103;

int ch[MAX_NODE][6], fail[MAX_NODE], node_c;

int add_char(int u, int id) {
  if (ch[u][id] < 0) ch[u][id] = node_c++;
  return ch[u][id];
}

void build_acam() {
  queue<int> que;
  FOR(i, 0, 6)
  if (~ch[0][i]) {
    que.push(ch[0][i]);
    fail[ch[0][i]] = 0;
  } else {
    ch[0][i] = 0;
  }
  while (!que.empty()) {
    int u = que.front();
    que.pop();
    FOR(i, 0, 6)
    if (~ch[u][i]) {
      que.push(ch[u][i]);
      fail[ch[u][i]] = ch[fail[u]][i];
    } else {
      ch[u][i] = ch[fail[u]][i];
    }
  }
}

const double EPS = 1e-9;
const int MAXN = MAX_NODE;
double a[MAXN][MAXN], x[MAXN];
int equ, var;

int gauss() {
  int i, j, k, col, max_r;
  for (k = 0, col = 0; k < equ && col < var; k++, col++) {
    max_r = k;
    for (i = k + 1; i < equ; i++)
      if (fabs(a[i][col]) > fabs(a[max_r][col])) max_r = i;
    if (fabs(a[max_r][col]) < EPS) return 0;

    if (k != max_r) {
      for (j = col; j < var; j++) swap(a[k][j], a[max_r][j]);
      swap(x[k], x[max_r]);
    }

    x[k] /= a[k][col];
    for (j = col + 1; j < var; j++) a[k][j] /= a[k][col];
    a[k][col] = 1;

    for (i = k + 1; i < equ; i++)
      if (i != k) {
        x[i] -= x[k] * a[i][col];
        for (j = col + 1; j < var; j++) a[i][j] -= a[k][j] * a[i][col];
        a[i][col] = 0;
      }
  }

  for (col = equ - 1, k = var - 1; ~col; --col, --k) {
    if (fabs(a[col][k]) > 0) {
      for (i = 0; i < k; ++i) {
        x[i] -= x[k] * a[i][col];
        for (j = col + 1; j < var; j++) a[i][j] -= a[k][j] * a[i][col];
        a[i][col] = 0;
      }
    }
  }

  return 1;
}

int ed_node[10], id[MAXN];

void solve() {
  int n, l, t;
  cin >> n >> l;

  node_c = 1;
  memset(ch, -1, sizeof(ch));
  memset(id, -1, sizeof(id));
  FOR(i, 0, n) {
    ed_node[i] = 0;
    FOR(j, 0, l) cin >> t, ed_node[i] = add_char(ed_node[i], t - 1);
    id[ed_node[i]] = i;
  }
  build_acam();

  FOR(step, 0, n) {
    equ = var = node_c;
    FOR(i, 0, equ) {
      x[i] = 0;
      FOR(j, 0, var) a[i][j] = 0;
    }
    FOR(i, 0, node_c) {
      a[i][i] = 1;
      if (~id[i]) {
        x[i] = id[i] == step ? 1 : 0;
      } else {
        FOR(j, 0, 6) a[i][ch[i][j]] += -1.0 / 6;
      }
    }

    /*
    FOR(i, 0, node_c) {
      FOR(j, 0, var) cout << a[i][j] << ' ';
      cout << x[i] << '\n';
    }
    */

    gauss();
    if (step) cout << ' ';
    cout << x[0];
  }
  cout << '\n';
}

int main(int argc, char *argv[]) {
  // freopen("in.txt", "r", stdin);
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout << fixed << setprecision(6);

  int o_o;
  for (cin >> o_o; o_o; --o_o) solve();

  return 0;
}
