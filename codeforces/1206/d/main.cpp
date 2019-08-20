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

const int MAXN = 1e5 + 5;
vi p[65], adj[MAXN];
pii edges[65];
int n, d[MAXN];

priority_queue<pii> heap;

int gao(int _e) {
  FOR(i, 0, n) d[i] = INF;
  d[edges[_e].first] = 0;
  while (!heap.empty()) heap.pop();
  heap.emplace(0, edges[_e].first);
  while (!heap.empty()) {
    int u = heap.top().second;
    int dis = -heap.top().first;
    heap.pop();
    if (dis ^ d[u]) continue;
    for (int &e : adj[u]) {
      if (e == _e) continue;
      int v = edges[e].first ^ edges[e].second ^ u;
      if (d[v] > d[u] + 1) {
        d[v] = d[u] + 1;
        heap.emplace(-d[v], v);
      }
    }
  }
  return d[edges[_e].second] + 1;
}

int main(int argc, char *argv[]) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cout << fixed << setprecision(10);

  ll x;
  cin >> n;
  FOR(i, 0, n) {
    cin >> x;
    FOR(j, 0, 63) if (x >> j & 1) p[j].push_back(i);
  }
  int ec = 0;
  FOR(i, 0, 63) {
    if (p[i].size() >= 3) {
      cout << "3\n";
      return 0;
    } else if (p[i].size() > 1) {
      adj[p[i][0]].push_back(p[i][1]);
      adj[p[i][1]].push_back(p[i][0]);
      edges[ec++] = pii(p[i][0], p[i][1]);
    }
  }

  sort(edges, edges + ec);
  ec = unique(edges, edges + ec) - edges;
  FOR(i, 0, n) {
    for (int &e : adj[i]) {
      int id =
          lower_bound(edges, edges + ec, (pii){min(i, e), max(i, e)}) - edges;
      e = id;
    }
    sort(ALL(adj[i]));
    adj[i].erase(unique(ALL(adj[i])), adj[i].end());
  }

  int ans = INF;
  FOR(i, 0, ec) ans = min(gao(i), ans);

  cout << (ans < INF ? ans : -1) << '\n';

  return 0;
}
