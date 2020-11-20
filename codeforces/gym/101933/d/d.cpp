#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, int> pli;

const int MAXN = 1e3 + 5;

struct Order {
  int s, u, t;
} o[MAXN];

int n, m, k;
ll d[MAXN][MAXN];
vector<pii> adj[MAXN];

void dijkstra(int s, ll *d) {
  memset(d, 0x3f, sizeof(ll) * (n + 1));
  d[s] = 0;

  static priority_queue<pli> heap;
  while (!heap.empty()) heap.pop();

  heap.emplace(0, s);
  while (!heap.empty()) {
    ll dis = -heap.top().first;
    int u = heap.top().second;
    heap.pop();
    if (dis != d[u]) continue;
    for (pii &e : adj[u]) {
      int v = e.first;
      if (d[v] > dis + e.second) {
        d[v] = dis + e.second;
        heap.emplace(-d[v], v);
      }
    }
  }
}

bool gao(ll delay) {
  static ll dp[MAXN];
  memset(dp, 0x3f, sizeof(ll) * (k + 1));
  dp[0] = 0;
  for (int i = 0; i < k; ++i) {
    ll cur = 0, wait = LLONG_MIN, st = dp[i];
    for (int j = i + 1; j <= k; ++j) {
      cur += (j > i + 1) ? d[o[j - 1].u][o[j].u] : d[1][o[j].u];
      if (st < o[j].t) wait += o[j].t - st, st = o[j].t;
      wait = max(wait, st + cur - o[j].s);
      if (wait > delay) break;
      dp[j] = min(dp[j], d[o[j].u][1] + st + cur);
    }
  }
  return dp[k] < 0x3f3f3f3f3f3f3f3fLL;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> m;
  for (int u, v, w; m; --m) {
    cin >> u >> v >> w;
    adj[u].emplace_back(v, w);
    adj[v].emplace_back(u, w);
  }
  cin >> k;
  for (int i = 1; i <= k; ++i) cin >> o[i].s >> o[i].u >> o[i].t;

  for (int i = 1; i <= n; ++i) dijkstra(i, d[i]);
  ll l = 0, r = 0x3f3f3f3f3f3f3f3fLL, ans = 0x3f3f3f3f3f3f3f3fLL;
  while (l <= r) {
    ll mid = (l + r) >> 1;
    if (gao(mid)) {
      ans = mid;
      r = mid - 1;
    } else {
      l = mid + 1;
    }
  }
  cout << ans << '\n';
  return 0;
}
