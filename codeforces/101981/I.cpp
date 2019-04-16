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
//#define debug(...) fprintf(stderr, __VA_ARGS__)
#define debug(...)

const int INF = 0x3ffffff;
const int MOD = 1e9 + 7;
const ll HASH_KEY = 6151;
const ll HASH_MOD = 1610612741;

// mt19937 rdm(chrono::steady_clock::now().time_since_epoch().count());

const int MAXN = 503;
const int MAXE = 2 * (MAXN * MAXN + 4 * MAXN);

struct Edge {
  int to, cap, nxt;
} edges[MAXE];
int que[MAXN * 2], gap[MAXN * 2], d[MAXN * 2], S, T;
int edge_cnt = 0, adj[MAXN * 2], lst[MAXN * 2];
void add_edge(int from, int to, int cap) {
  debug("%d -> %d [%d]\n", from, to, cap);
  edges[edge_cnt] = (Edge){to, cap, adj[from]};
  adj[from] = edge_cnt++;
  edges[edge_cnt] = (Edge){from, 0, adj[to]};
  adj[to] = edge_cnt++;
}

int dfs(int u, int flow) {
  if (u == T || flow == 0) {
    return flow;
  }
  int res = 0;
  for (int &it = lst[u]; ~it; it = edges[it].nxt) {
    int v = edges[it].to;
    if (d[u] == d[v] + 1) {
      int t = dfs(v, min(flow, edges[it].cap));
      res += t;
      flow -= t;
      edges[it].cap -= t;
      edges[it ^ 1].cap += t;
      if (flow == 0) {
        return res;
      }
    }
  }
  if (!--gap[d[u]]) {
    d[S] = T + 3;
  }
  ++gap[++d[u]];
  lst[u] = adj[u];
  return res;
}

int isap() {
  ZERO(d);
  ZERO(gap);
  gap[d[T] = 1] = 1;
  FOR(i, S, T + 1) { lst[i] = adj[i]; }
  int *head = que, *tail = que;
  *tail++ = T;
  while (head < tail) {
    int u = *head++;
    for (int it = lst[u]; ~it; it = edges[it].nxt) {
      int v = edges[it].to;
      if (!d[v]) {
        ++gap[d[v] = d[u] + 1];
        *tail++ = v;
      }
    }
  }
  int res = 0;
  while (d[S] < T + 3) {
    res += dfs(S, INF);
  }
  return res;
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  int n, m, k;
  cin >> n >> m >> k;

  memset(adj, -1, sizeof(adj));
  S = 0;
  T = m + n + 2;
  add_edge(S, 1, k);
  FOR(i, 0, n) {
    add_edge(S, i + 2, 1);
    add_edge(1, i + 2, 1);
    int t;
    cin >> t;
    FOR(j, 0, t) {
      int x;
      cin >> x;
      add_edge(i + 2, n + 1 + x, 1);
    }
  }
  FOR(i, 0, m) { add_edge(n + 2 + i, T, 1); }
  cout << isap() << "\n";

  return 0;
}
