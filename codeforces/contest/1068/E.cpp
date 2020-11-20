#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int n, k;
  cin >> n >> k;
  if (n < 4 || k >= 11) {
    cout << "No" << endl;
    return 0;
  }
  vector<vector<int> >g(n);
  for (int i = 1; i < n; i++) {
    int u, v;
    cin >> u >> v;
    g[u - 1].push_back(v - 1);
    g[v - 1].push_back(u - 1);
  }

  queue<int> que;
  vector<int> dep(n, -1);
  vector<bool> visited(n, false);
  for (int i = 0; i < n; i++) {
    if (g[i].size() > 1) continue;
    que.push(i);
    dep[i] = 0;
  }
  while (!que.empty()) {
    int u = que.front();
    que.pop();
    visited[u] = true;
    int cnt = 0;
    for (int v : g[u]) {
      if (visited[v]) continue;
      cnt++;
      if (cnt > 1) {
        cout << "No" << endl;
        return 0;
      }
      if (dep[v] == -1) {
        dep[v] = dep[u] + 1;
        que.push(v);
      } else {
        if (dep[v] != dep[u] + 1) {
          cout << "No" << endl;
          return 0;
        }
      }
    }
    if (cnt == 0) {
      if (dep[u] != k || g[u].size() < 3) {
        cout << "No" << endl;
        return 0;
      }
    } else {
      if (g[u].size() > 1 && g[u].size() <= 3) {
        cout << "No" << endl;
        return 0;
      }
    }
  }
  cout << "Yes" << endl;
  return 0;
}
