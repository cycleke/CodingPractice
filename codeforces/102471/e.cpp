#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 3;
const int MAXM = 2e5 + 3;

long long sum[MAXN];
vector<pair<int, int>> adj[MAXN];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);

  int n, m;
  long long flow = 0;
  cin >> n >> m;
  for (int u, v, w; m; --m) {
    cin >> u >> v >> w;
    adj[u].emplace_back(v, w);
    flow += w;
  }

  int len = 0;
  for (auto e : adj[1]) {
    static vector<int> path;
    
    path.clear();
    path.push_back(e.second);
    for (int x = e.first; x != n; x = adj[x][0].first)
      path.push_back(adj[x][0].second);
    
    sort(path.begin(), path.end());
    
    len = path.size();
    for (int i = 0; i < len; ++i) sum[i] += path[i];
  }

  // for (int i = 0; i < len; ++i) cout << sum[i] << " ";
  
  flow -= sum[0] * len;
  long long ans = 0;
  for (int i = 1; i < len; ++i) {
    long long temp = min(flow / len, sum[i] - sum[i - 1]);
    ans += temp * i, flow -= temp * len;
  }
  cout << ans << "\n";
  
  return 0;
}

