#include <bits/stdc++.h>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n, m;
  cin >> n >> m;
  vector<int> deg(n, 0), ord;
  while (m--) {
    int x, y;
    cin >> x >> y;
    deg[x]++;
    deg[y]++;
  }
  for (int i = 0; i < n; ++i) ord.push_back(i);
  sort(ord.begin(), ord.end(),
       [&](const int &a, const int &y) { return deg[a] < deg[y]; });
  int ed = n, cnt = 0;
  typedef pair<int, int> pii;
  vector<int> lst;
  vector<pii> edge;
  // for (int d : deg)
  // cerr << d << " ";
  // cerr << endl;
  for (int i = 0; i < ed; ++i) {
    int x = ord[i];
    if (deg[x] == 1) {
      lst.push_back(x);
      cnt++;
      // cerr << x << " " << cnt << endl;
    } else if ((int)lst.size() >= deg[x] - 1) {
      for (int j = 0; j < deg[x] - 1; ++j) {
        edge.emplace_back(lst.back(), x);
        lst.pop_back();
      }
      lst.push_back(x);
      cnt++;
      // cerr << x << " " << cnt << endl;
    } else if ((int)lst.size() + ed - i - 1 >= deg[x] - 1) {
      for (int y : lst) edge.emplace_back(x, y);
      for (int j = 0; j < deg[x] - 1 - (int)lst.size(); ++j)
        edge.emplace_back(x, ord[--ed]);
      lst.clear();
      lst.push_back(x);
      cnt++;
      // cerr << x << " " << cnt << endl;
    } else {
      for (int y : lst) edge.emplace_back(x, y);
      for (int j = i + 1; j < ed; ++j) edge.emplace_back(x, ord[j]);
      lst.clear();
      break;
    }
  }

  if (lst.size() > 0) {
    if (lst.size() != 2) cnt--;
    for (int i = 1; i < (int)lst.size(); ++i) edge.emplace_back(lst[0], lst[i]);
  }
  cout << n - cnt << endl << n << " " << n - 1 << endl;
  for (pii e : edge) cout << e.first << " " << e.second << endl;
  return 0;
}
