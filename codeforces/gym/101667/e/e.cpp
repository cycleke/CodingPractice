#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;
const int MAXM = 505;

struct MF {
  struct Edge {
    int to, cap, flow;
  } edges[MAXM * 4];

  vector<int> adj[MAXN];
  int n, edges_c, dep[MAXN], depc[MAXN], s, t, last[MAXN];

  void init(int _n) {
    n = _n;
    for (int i = 1; i <= n; ++i) adj[i].clear();
    edges_c = 0;
  }

  void add_edge(int v, int u, int cap) {
    edges[edges_c] = {v, cap, 0};
    adj[u].push_back(edges_c++);
    edges[edges_c] = {u, 0, 0};
    adj[v].push_back(edges_c++);
  }

  int dfs(int u, int flow) {
    if (u == t || !flow) return flow;
    int v, e, temp, res = 0;
    for (int &i = last[u]; i < (int)adj[u].size(); ++i) {
      e = adj[u][i];
      v = edges[e].to;
      if (edges[e].cap == edges[e].flow) continue;
      if (dep[v] != dep[u] - 1) continue;
      temp = dfs(v, min(flow, edges[e].cap - edges[e].flow));
      edges[e].flow += temp, edges[e ^ 1].flow -= temp;
      res += temp, flow -= temp;
      if (!flow) return res;
      if (!dep[s]) return res;
    }
    last[u] = 0;
    if (!(--depc[dep[u]])) dep[s] = n + 1;
    ++depc[++dep[u]];
    return res;
  }
  int max_flow(int s, int t) {
    this->s = s, this->t = t;

    static queue<int> que;
    memset(dep + 1, 0, sizeof(int) * n);
    memset(depc + 1, 0, sizeof(int) * n);
    memset(last + 1, 0, sizeof(int) * n);
    while (!que.empty()) que.pop();
    dep[t] = 1, que.push(t);

    while (!que.empty()) {
      int u = que.front();
      que.pop();
      ++depc[dep[u]];
      for (int i = 0, v; i < (int)adj[u].size(); ++i) {
        v = edges[adj[u][i]].to;
        if (dep[v]) continue;
        dep[v] = dep[u] + 1;
        que.push(v);
      }
    }

    int res = 0;
    while (dep[s] <= n) res += dfs(s, INT_MAX);
    return res;
  }
} mf;

struct Edge {
  int u, v, w;
} edges[MAXM];

int main() {
  // freopen("in1.txt", "r", stdin);
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;
  for (int i = 0; i < m; ++i) cin >> edges[i].u >> edges[i].v >> edges[i].w;
  sort(edges, edges + m,
       [&](const Edge &a, const Edge &b) { return a.w < b.w; });

  int ans = 0;
  for (int i = 1; i < m; ++i) {
    mf.init(n);
    for (int j = 0; j < m; ++j) {
      if (edges[j].w == edges[i].w) break;
      mf.add_edge(edges[j].u, edges[j].v, 1);
      mf.add_edge(edges[j].v, edges[j].u, 1);
    }
    ans += mf.max_flow(edges[i].u, edges[i].v);
  }
  cout << ans << '\n';
  return 0;
}
