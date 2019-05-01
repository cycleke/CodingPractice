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

map<int, int> idx;
vector<int> rev_idx;

int getIdx(const int &x) {
  if (EXIST(idx, x)) {
    return idx[x];
  }
  idx[x] = rev_idx.size();
  rev_idx.pb(x);
  return idx[x];
}

const int MAXN = 2e5 + 3;

struct Edge {
  int u, v;
  bool used;
};

vector<Edge> edges;
vi ans;
int head[MAXN];
vi adj[MAXN];

void dfs(int u) {
  for (; head[u] < adj[u].size(); ++head[u]) {
    int e = adj[u][head[u]];
    if (!edges[e].used) {
      edges[e].used = true;
      dfs(edges[e].u + edges[e].v - u);
    }
  }
  ans.push_back(u);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  int n;
  cin >> n;
  vi b(n - 1), c(n - 1);
  FOR(i, 1, n) {
    int x;
    cin >> x;
    b[i - 1] = getIdx(x);
  }
  FOR(i, 1, n) {
    int x;
    cin >> x;
    c[i - 1] = getIdx(x);
  }

  FOR(i, 0, n - 1) {
    if (rev_idx[b[i]] > rev_idx[c[i]]) {
      cout << "-1\n";
      return 0;
    }
  }

  FOR(i, 0, n - 1) {
    adj[b[i]].pb(edges.size());
    adj[c[i]].pb(edges.size());
    edges.pb((Edge){b[i], c[i], false});
  }

  vi p;
  FOR(i, 0, rev_idx.size()) {
    if (adj[i].size() & 1) {
      p.pb(i);
    }
  }

  if (p.empty()) {
    p.pb(0);
    p.pb(0);
  }

  if (p.size() != 2) {
    cout << "-1\n";
    return 0;
  }

  dfs(p[0]);

  if (ans.size() != n) {
    cout << "-1\n";
    return 0;
  }

  for (int x : ans) {
    cout << rev_idx[x] << " ";
  }
  cout << "\n";

  return 0;
}
