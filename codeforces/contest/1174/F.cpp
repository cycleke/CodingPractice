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

const int MAXN = 2e5 + 3;

int interact(char oper, int u) {
  printf("%c %d\n", oper, u);
  fflush(stdout);
  int res;
  scanf("%d", &res);
  return res;
}

vi adj[MAXN];
bool deleted[MAXN];
int fa[MAXN], size[MAXN], dep[MAXN], depx;

void dfs(int u) {
  for (int v : adj[u]) {
    if (v == fa[u]) {
      continue;
    }
    fa[v] = u;
    dep[v] = dep[u] + 1;
    dfs(v);
  }
}

int sub_size, root, root_key;

void get_root(int u, int from) {
  int key = 0;
  size[u] = 1;
  for (int v : adj[u]) {
    if (deleted[v] || v == from) {
      continue;
    }
    get_root(v, u);
    size[u] += size[v];
    key = max(key, size[v]);
  }
  key = max(key, sub_size - key);
  if (key < root_key) {
    root = u;
    root_key = key;
    // debug("root = %d root_key = %d\n", root, root_key);
  }
  // debug("u = %d key = %d\n", u, key);
}

int gao(int u) {
  if (size[u] == 1) {
    return u;
  }
  sub_size = size[u];
  root = u;
  root_key = sub_size;
  get_root(u, 0);
  int dist = interact('d', root);
  if (dist == 0) {
    return root;
  }
  deleted[root] = true;
  if (dep[root] + dist == depx) {
    return gao(interact('s', root));
  } else {
    return gao(fa[root]);
  }
}

int main() {
  int n;
  scanf("%d", &n);

  FOR(i, 1, n) {
    int u, v;
    scanf("%d %d", &u, &v);
    adj[u].pb(v);
    adj[v].pb(u);
  }
  dfs(1);

  depx = interact('d', 1);
  size[1] = n;
  printf("! %d\n", gao(1));

  return 0;
}
