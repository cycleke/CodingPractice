#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int n, k;
  cin >> n >> k;
  vector<vector<int> > g(n);
  for (int step = 1; step < n; step++) {
    int u, v;
    cin >> u >> v;
    g[u - 1].push_back(v - 1);
    g[v - 1].push_back(u - 1);
  }

  auto Check =
    [&]() {
      auto leastNodes =
        [](const int &k) {
          switch (k) {
          case 1 : return 4;
          case 2 : return 13;
          case 3 : return 40;
          case 4 : return 121;
          case 5 : return 364;
          case 6 : return 1093;
          case 7 : return 3280;
          case 8 : return 9841;
          case 9 : return 29524;
          case 10 : return 88573;
          default : return 0x3fffffff;
          }
        };
      if (n < leastNodes(k))
        return false;
      vector<int> dep(n, -1);
      vector<bool> vis(n, false);
      queue<int> q;
      for (int i = 0; i < n; i++) {
        if (g[i].size() > 1) continue;
        q.push(i);
        dep[i] = 0;
      }
      while (!q.empty()) {
        int u = q.front();
        q.pop();
        vis[u] = true;
        bool foundFather = false;
        for (auto v : g[u]) {
          if (vis[v]) continue;
          if (foundFather)
            return false;
          foundFather = true;
          if (dep[v] > -1) {
            if (dep[v] != dep[u] + 1)
              return false;
          } else {
            q.push(v);
            dep[v] = dep[u] + 1;
          }
        }
        if (foundFather) {
          if (g[u].size() > 1 && g[u].size() < 4)
            return false;
        } else {
          if (g[u].size() < 3 || dep[u] != k)
            return false;
        }
      }
      return true;
    };
  cout << (Check() ? "Yes" : "No") << endl;
  return 0;
}
