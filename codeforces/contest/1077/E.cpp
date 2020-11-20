#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int n;
  cin >> n;
  map<int, int> cnt;
  for (int i = 0; i < n; i++) {
    int x;
    cin >> x;
    cnt[x]++;
  }
  vector<int> c;
  for (auto &x : cnt) {
    c.push_back(x.second);
  }
  sort(c.begin(), c.end());
  vector<int> f(c.at(c.size() - 1) + 1, -1);
  f[0] = 0;
  for (size_t i = 0; i < c.size(); i++) {
    for (int j = c.at(i); j > 0; j--) {
      f[j] = max(f[j], j);
      if (j % 2 == 0)
        f[j] = max(f[j], f[j / 2] + j);
    }
  }
  int ans = -1;
  for (auto &x : f) {
    ans = max(ans, x);
  }
  cout << ans << endl;
  return 0;
}
