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

const int MAXN = 4e5 + 5;
const int MAX_NODE = 2 * MAXN;

int ch[MAX_NODE][26], fail[MAX_NODE], dep[MAX_NODE], node_c;
vi adj[MAX_NODE];

int add_char(int u, int id) {
  if (ch[u][id] < 0) ch[u][id] = node_c++;
  return ch[u][id];
}
void build_acam() {
  queue<int> que;
  FOR(i, 0, 26)
  if (~ch[0][i]) {
    que.push(ch[0][i]);
    fail[ch[0][i]] = 0;
    dep[ch[0][i]] = 1;
  } else {
    ch[0][i] = 0;
  }
  while (!que.empty()) {
    int u = que.front();
    que.pop();
    FOR(i, 0, 26)
    if (~ch[u][i]) {
      que.push(ch[u][i]);
      fail[ch[u][i]] = ch[fail[u]][i];
      dep[ch[u][i]] = dep[u] + 1;
    } else {
      ch[u][i] = ch[fail[u]][i];
    }
  }
  FOR(i, 1, node_c) adj[fail[i]].push_back(i);
}

int in[MAX_NODE], out[MAX_NODE], dfs_c;
int tree[MAX_NODE], ans[MAXN], q_node[MAXN];
vi ques[MAX_NODE];

void dfs(int u) {
  in[u] = ++dfs_c;
  for (int &v : adj[u]) dfs(v);
  out[u] = dfs_c;
}
void add(int x, int delta) {
  for (; x <= dfs_c; x += x & -x) tree[x] += delta;
}
int ask(int x) {
  int res = 0;
  for (; x; x &= x - 1) res += tree[x];
  return res;
}
void gao(int u) {
  add(in[u], 1);
  for (int &id : ques[u])
    ans[id] = ask(out[q_node[id]]) - ask(in[q_node[id]] - 1);
  FOR(i, 0, 26) if (dep[ch[u][i]] == dep[u] + 1) gao(ch[u][i]);
  add(in[u], -1);
}

int node[MAXN];

int main(int argc, char *argv[]) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout << fixed << setprecision(10);

  int n, q;
  cin >> n;
  node_c = 1;
  memset(ch, -1, sizeof(ch));
  FOR(i, 1, n + 1) {
    int opt, j;
    char c;
    cin >> opt;
    if (opt == 1) {
      cin >> c;
      node[i] = add_char(0, c - 'a');
    } else {
      cin >> j >> c;
      node[i] = add_char(node[j], c - 'a');
    }
  }

  cin >> q;
  FOR(i, 1, q + 1) {
    int id;
    string s;
    cin >> id >> s;
    q_node[i] = 0;
    for (char &ch : s) q_node[i] = add_char(q_node[i], ch - 'a');
    ques[node[id]].push_back(i);
  }
  build_acam();
  dfs(0);
  gao(0);
  FOR(i, 1, q + 1) cout << ans[i] << '\n';
  return 0;
}
