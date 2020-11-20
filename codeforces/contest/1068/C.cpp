#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int n, m;
  vector<pair<int, int> >ans[101];

  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    ans[i].emplace_back(i, i);
  }
  int raw = n + 1;
  for (int step = 0; step < m; step++) {
    int x, y;
    cin >> x >> y;
    ans[x].emplace_back(raw, x);
    ans[y].emplace_back(raw, y);
    raw++;
  }
  for (int i = 1; i <= n; i++) {
    cout << ans[i].size() << endl;
    for (auto pos : ans[i]) {
      cout << pos.first << " " << pos.second << endl;
    }
  }
  return 0;
}
