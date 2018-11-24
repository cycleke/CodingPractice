#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef tuple<int, int, int> tiii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<long long> vll;

const int INF = 0x3fffffff;

bool flag = false;

int dfs(int u, int fa, vi &flow, vi &col, int cur_col, const vvi &g,
        const vi &req) {
  if (~req[u])
    cur_col = u;
  col[u] = cur_col;

  int cost = 0;

  for (auto &v : g[u]) {
    if (v != fa) {
      cost += dfs(v, u, flow, col, cur_col, g, req);
    }
  }
  if (~req[u]) {
    if (cost > req[u]) {
      flag = true;
    }
    flow[u] = req[u] - cost;
    cost = req[u];
  }
  return cost;
}

void readGraph(int m, vvi &g) {
  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    g[u - 1].push_back(v - 1);
    g[v - 1].push_back(u - 1);
  }
}

struct Graph {

  struct Edge {
    int to, flow, cap, cost, rev;

    Edge(int to, int cap, int cost, int rev)
        : to(to), flow(0), cap(cap), cost(cost), rev(rev) {}
  };

  int n;
  vector<vector<Edge>> graph;
  Graph() {}
  ~Graph() { graph.clear(); }

  void createGraph(int n) {
    this->n = n;
    graph = vector<vector<Edge>>(n);
  }
  void addEdge(int s, int t, int cap, int cost) {
    graph[s].push_back(Edge(t, cap, cost, graph[t].size()));
    graph[t].push_back(Edge(s, 0, -cost, graph[s].size() - 1));
  }
  void SPFA(int s, vi &dis) {
    fill(dis.begin(), dis.end(), INF);
    dis[s] = 0;
    vector<bool> inq(n, false);
    queue<int> q;
    q.push(s);
    inq[s] = true;
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      inq[u] = false;
      for (auto &e : graph[u]) {
        if (e.cap <= e.flow)
          continue;
        int v = e.to;
        int _dis = dis[u] + e.cost;
        if (_dis < dis[v]) {
          dis[v] = _dis;
          if (!inq[v]) {
            q.push(v);
            inq[v] = true;
          }
        }
      }
    }
  }
  pii minCostFlow(int s, int t, int max_flow) {
    vi pri(n), cur_flow(n), pre_edge(n), pre_node(n), pot(n);

    SPFA(s, pot);
    int flow = 0;
    int flow_cost = 0;
    while (flow < max_flow) {
      priority_queue<pii, vector<pii>, greater<pii>> q;
      q.push(pii(0, s));
      fill(pri.begin(), pri.end(), INF);
      pri[s] = 0;
      vector<bool> done(n, false);
      cur_flow[s] = INF;
      while (!done[t] && !q.empty()) {
        auto cur = q.top();
        q.pop();
        int u = cur.second;
        int priu = cur.first;
        if (priu != pri[u])
          continue;
        done[u] = true;
        for (int i = 0; i < (int)graph[u].size(); i++) {
          Edge &e = graph[u][i];
          if (e.flow >= e.cap)
            continue;
          int v = e.to;
          int _pri = priu + e.cost + pot[u] - pot[v];
          if (_pri < pri[v]) {
            pri[v] = _pri;
            q.push(pii(_pri, v));
            pre_node[v] = u;
            pre_edge[v] = i;
            cur_flow[v] = min(cur_flow[u], e.cap - e.flow);
          }
        }
      }
      if (pri[t] == INF)
        break;
      for (int i = 0; i < n; i++)
        if (done[i])
          pot[i] += pri[i] - pri[t];
      int delta = min(cur_flow[t], max_flow - flow);
      flow += delta;
      for (int v = t; v != s; v = pre_node[v]) {
        Edge &e = graph[pre_node[v]][pre_edge[v]];
        e.flow += delta;
        graph[v][e.rev].flow -= delta;
        flow_cost += delta * e.cost;
      }
    }
    return make_pair(flow, flow_cost);
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  int n, cap1, cap2;
  cin >> n >> cap1 >> cap2;
  cap1--;
  cap2--;

  int mx = 0, a[n];
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    mx = max(mx, a[i]);
  }

  vvi g1(n), g2(n);
  readGraph(n - 1, g1);
  readGraph(n - 1, g2);

  vi req(n, -1);
  int q;
  cin >> q;
  for (int i = 0; i < q; i++) {
    int x;
    cin >> x;
    cin >> req[x - 1];
  }
  int req_flow1 = req[cap1];
  vi col1(n), flow1(n, 1000);
  dfs(cap1, -1, flow1, col1, cap1, g1, req);
  if (flag) {
    cout << "-1" << endl;
    return 0;
  }

  fill(req.begin(), req.end(), -1);
  cin >> q;
  for (int i = 0; i < q; i++) {
    int x;
    cin >> x;
    cin >> req[x - 1];
  }
  int req_flow2 = req[cap2];
  if (req_flow1 != req_flow2) {
    cout << "-1" << endl;
    return 0;
  }
  vi col2(n), flow2(n, 1000);
  dfs(cap2, -1, flow2, col2, cap2, g2, req);
  if (flag) {
    cout << "-1" << endl;
    return 0;
  }
  Graph mcf;
  mcf.createGraph(2 * n + 2);
  int source = 0;
  int sink = 2 * n + 1;
  for (int i = 0; i < n; i++) {
    mcf.addEdge(source, i + 1, flow1[i], 0);
    mcf.addEdge(n + i + 1, sink, flow2[i], 0);
    mcf.addEdge(col1[i] + 1, col2[i] + n + 1, 1, mx - a[i]);
  }

  auto ans = mcf.minCostFlow(source, sink, n);
  if (ans.first != req_flow1) {
    cout << "-1" << endl;
    return 0;
  }

  cout << mx * req_flow1 - ans.second << endl;
  return 0;
}
