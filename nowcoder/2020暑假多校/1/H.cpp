#include <algorithm>
#include <bitset>
#include <cassert>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iostream>
#include <limits>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <typeinfo>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<pii> vpii;

class MinCostFlow {
public:
  struct Result {
    int flow, cost;
  };
  struct Edge {
    int to, next, rest, cost;
  };

  vector<bool> inq;
  vector<int> head, dist, from, flow;
  vector<Edge> edges;

  MinCostFlow(int n, int m) : inq(n), head(n, -1), dist(n), from(n), flow(n) {
    edges.reserve(2 * m);
  }

  void add_edge(int u, int v, int capacity, int cost) {
    internal_add_edge(u, v, capacity, cost);
    internal_add_edge(v, u, 0, -cost);
  }

  void internal_add_edge(int u, int v, int capacity, int cost) {
    edges.push_back((Edge){v, head[u], capacity, cost});
    head[u] = edges.size() - 1;
  }

  Result augment(int source, int sink) {
    fill(dist.begin(), dist.end(), INT_MAX);
    dist[source] = 0;
    flow[source] = INT_MAX;
    queue<int> q;
    q.push(source);
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      inq[u] = false;
      for (int it = head[u]; ~it; it = edges[it].next) {
        auto &e = edges[it];
        int v = e.to;
        if (e.rest > 0 && dist[u] + e.cost < dist[v]) {
          from[v] = it;
          dist[v] = dist[u] + e.cost;
          flow[v] = min(e.rest, flow[u]);
          if (!inq[v]) {
            q.push(v);
            inq[v] = true;
          }
        }
      }
    }

    if (dist[sink] == INT_MAX) return {0, 0};
    int min_flow = flow[sink];
    for (int u = sink; u != source; u = edges[from[u] ^ 1].to) {
      edges[from[u]].rest -= min_flow;
      edges[from[u] ^ 1].rest += min_flow;
    }
    return {min_flow, dist[sink]};
  }
};

int main(int argc, char *argv[]) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  while (cin >> n >> m) {
    MinCostFlow mcf(n, m);
    for (int i = 0, a, b, c; i < m; ++i) {
      cin >> a >> b >> c;
      mcf.add_edge(a - 1, b - 1, 1, c);
    }
    vi psum(1);
    int sum = 0;
    for (;;) {
      auto result = mcf.augment(0, n - 1);
      if (!result.flow) break;
      psum.push_back(sum += result.cost);
    }

    int q, u, v;
    for (cin >> q; q; --q) {
      cin >> u >> v;
      if (u == 0) {
        cout << "NaN\n";
        continue;
      }
      int flow = (v - 1) / u + 1;
      if (flow >= static_cast<int>(psum.size())) {
        cout << "NaN\n";
        continue;
      }
      int delta = psum[flow] - psum[flow - 1];
      ll a = 1LL * psum[flow] * u - delta * (1LL * flow * u - v);
      ll g = __gcd(a, 1LL * v);
      cout << a / g << "/" << v / g << "\n";
    }
  }

  return 0;
}
