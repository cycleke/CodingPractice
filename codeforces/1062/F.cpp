#include <bits/stdc++.h>
using namespace std;

void Exec(const vector<vector<int>> &g, vector<int> &cnt) {
  const int n = cnt.size();
  vector<int> in(n, 0);
  for (auto &ng : g) {
    for (const int &v : ng) {
      in[v]++;
    }
  }
  queue<int> q;
  int tot = n;
  for (int i = 0; i < n; i++) {
    if (in[i])
      continue;
    q.push(i);
    tot--;
  }
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    if (q.empty()) {
      cnt[u] += tot;
    } else if (q.size() == 1) {
      bool flag = true;
      for (const int &v : g[q.front()]) {
        flag &= in[v] > 1;
      }
      if (flag)
        cnt[u] += tot;
    }
    for (const int &v : g[u]) {
      in[v]--;
      if (in[v] == 0) {
        q.push(v);
        tot--;
      }
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  int n, m;
  cin >> n >> m;
  vector<vector<int>> g(n), fg(n);
  for (int step = 0; step < m; step++) {
    int u, v;
    cin >> u >> v;
    g[u - 1].push_back(v - 1);
    fg[v - 1].push_back(u - 1);
  }

  vector<int> cnt(n, 0);
  Exec(g, cnt);
  Exec(fg, cnt);
  int ans = 0;
  for (int &x : cnt) {
    if (x + 2 >= n) {
      ans++;
    }
  }
  cout << ans << endl;
  return 0;
}
