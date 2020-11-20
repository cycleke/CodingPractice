#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  string s;
  cin >> s;
  int n = s.length();

  set<int> zero;
  zero.insert(-1), zero.insert(n);
  for (int i = 0; i < n; ++i)
    if (s[i] == '0') zero.insert(i);
  for (int i = 0; i < n; ++i) {
    if (s[i] == '2') {
      auto it = zero.lower_bound(i);
      int r = *it;
      int l = *--it;
      if (~l) zero.erase(l);
      if (r < n) zero.erase(r);
      zero.insert(l + r - i);
    }
  }

  string ans(n, '1');
  for (int x : zero) {
    if (x < 0 || x >= n) continue;
    ans[x] = '0';
  }
  cout << ans << '\n';
  return 0;
}
