#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;

void debug_out() { cerr << endl; }
template <typename T> string to_string(const vector<T> &vec) {
  string res = "[";
  bool first = true;
  for (const T &x : vec) {
    if (first) {
      first = false;
    } else {
      res += ",";
    }
    res += to_string(x);
  }
  return res + "]";
}
template <typename Head, typename... Tail> void debug_out(Head H, Tail... T) {
  cerr << " " << to_string(H);
  debug_out(T...);
}
#ifdef ONLINE_JUDGE
#define debug(...)
#else
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#endif

constexpr int MAXT = 103;
constexpr int MAXB = 101;
constexpr int MAXN = 1e3 + 3;
constexpr int INF = 0x3f3f3f3f;

vector<tuple<int, int, int>> adj[MAXN];
int x[MAXN], y[MAXN], B, C[MAXT], g[MAXN][MAXN], dis[MAXN][MAXB];

int dist(int a, int b) { return ceil(hypot(x[a] - x[b], y[a] - y[b])); }

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
  cout << fixed << setprecision(10);

  cin >> x[0] >> y[0] >> x[1] >> y[1] >> B >> C[0];
  adj[0].emplace_back(1, dist(0, 1), C[0] * dist(0, 1));

  int t, n;
  cin >> t;
  for (int i = 1; i <= t; ++i) cin >> C[i];

  cin >> n;
  for (int i = 2; i < n + 2; ++i)
    for (int j = 2; j < n + 2; ++j) g[i][j] = INF;
  for (int i = 2, l, d; i < n + 2; ++i) {
    cin >> x[i] >> y[i] >> l;
    d = dist(0, i);
    adj[0].emplace_back(i, d, C[0] * d);
    d = dist(i, 1);
    adj[i].emplace_back(1, d, C[0] * d);

    for (int j, mj; l; --l) {
      cin >> j >> mj;
      j += 2;
      g[i][j] = g[j][i] = min(g[i][j], C[mj]);
    }
  }
  for (int i = 2; i < n + 2; ++i)
    for (int j = i + 1; j < n + 2; ++j) {
      if (g[i][j] == INF) continue;
      int d = dist(i, j), w = g[i][j] * d;
      adj[i].emplace_back(j, d, w);
      adj[j].emplace_back(i, d, w);
    }

  memset(dis, 0x3f, sizeof(dis));
  dis[0][0] = 0;
  priority_queue<tuple<int, int, int>> heap;
  heap.emplace(0, 0, 0);
  while (!heap.empty()) {
    auto [d0, d1, u] = heap.top();
    heap.pop();
    d0 = -d0, d1 = -d1;
    if (d0 != dis[u][d1]) continue;
    for (auto [v, w1, w0] : adj[u]) {
      int d0_ = d0 + w0, d1_ = d1 + w1;
      if (d1_ > B || d0_ >= dis[v][d1_]) continue;
      dis[v][d1_] = d0_;
      heap.emplace(-d0_, -d1_, v);
    }
  }

  int min_cost = INF;
  for (int i = 0; i <= B; ++i) min_cost = min(min_cost, dis[1][i]);
  cout << (min_cost == INF ? -1 : min_cost) << "\n";

  return 0;
}
