#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;
typedef pair<long long, int> pli;
typedef pair<pli, pii> node;
const int MAXN = 5e4 + 5;

priority_queue<node> heap;

int ques[MAXN];
long long ans[MAXN];
vector<pii> adj[MAXN];

node make_node(long long a, int b, int c, int d) {
  return make_pair(make_pair(a, b), make_pair(c, d));
}

void exp_node(node x, long long &a, int &b, int &c, int &d) {
  a = x.first.first, b = x.first.second;
  c = x.second.first, d = x.second.second;
}

void solve() {
  int n, m, q;
  cin >> n >> m >> q;
  for (int i = 1; i <= n; ++i) adj[i].clear();
  for (int u, v, w; m; --m) {
    cin >> u >> v >> w;
    adj[u].push_back(make_pair(w, v));
  }
  int max_k = 0;
  for (int i = 0; i < q; ++i) cin >> ques[i], max_k = max(max_k, ques[i]);
  while (!heap.empty()) heap.pop();
  for (int i = 1; i <= n; ++i) {
    sort(adj[i].begin(), adj[i].end());
    if (!adj[i].empty())
      heap.push(make_node(-1LL * adj[i][0].first, 0, i, adj[i][0].second));
  }

  for (int step = 1; step <= max_k; ++step) {
    long long dist;
    int idx, u, v;
    exp_node(heap.top(), dist, idx, u, v);
    heap.pop();
    ans[step] = -dist;
    if (!adj[v].empty())
      heap.push(make_node(dist - adj[v][0].first, 0, v, adj[v][0].second));
    ++idx;
    if (idx ^ adj[u].size())
      heap.push(make_node(dist + adj[u][idx - 1].first - adj[u][idx].first, idx,
                          u, adj[u][idx].second));
  }
  for (int i = 0; i < q; ++i) cout << ans[ques[i]] << '\n';
}

int main(int argc, char *argv[]) {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int o_o;
  for (cin >> o_o; o_o; --o_o) solve();

  return 0;
}
