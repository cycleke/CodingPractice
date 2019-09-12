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

const int MAXN = 1e3 + 5;

int n, m, d[2][MAXN], team[MAXN];
vector<pii> adj[MAXN];
priority_queue<pii> heap;

void dijkstra(int *s, int ss, int *d) {
  memset(d, 0x3f, n * sizeof(int));
  FOR(i, 0, ss) {
    d[s[i]] = 0;
    heap.emplace(0, s[i]);
  }
  while (!heap.empty()) {
    int u = heap.top().second;
    int dis = -heap.top().first;
    heap.pop();
    if (dis != d[u]) continue;
    for (pii &e : adj[u]) {
      if (d[e.first] > dis + e.second) {
        d[e.first] = dis + e.second;
        heap.emplace(-d[e.first], e.first);
      }
    }
  }
}

void solve() {
  int s, k, c;
  cin >> n >> m >> s >> k >> c;
  FOR(i, 0, n) adj[i].clear();
  FOR(i, 0, k) cin >> team[i], --team[i];
  FOR(i, 0, m) {
    int u, v, w;
    cin >> u >> v >> w;
    --u, --v;
    adj[u].emplace_back(v, w);
    adj[v].emplace_back(u, w);
  }

  int t[1] = {s - 1};
  dijkstra(t, 1, d[0]);
  dijkstra(team, k, d[1]);

  int ans0 = 0, ans1 = 0;
  FOR(i, 0, n) ans0 = max(ans0, d[0][i]), ans1 = max(ans1, d[1][i]);
  cout << (ans0 <= ans1 * c ? ans0 : ans1) << '\n';
}

int main(int argc, char *argv[]) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout << fixed << setprecision(10);

  int o_o;
  for (cin >> o_o; o_o; --o_o) solve();

  return 0;
}
