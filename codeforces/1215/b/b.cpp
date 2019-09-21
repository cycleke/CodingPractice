#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, cur = 0, s[2] = {1, 0};
  long long ans[2] = {0, 0};

  cin >> n;
  for (int i = 0, a; i < n; ++i) {
    cin >> a;
    if (a < 0) cur ^= 1;
    ans[0] += s[cur];
    ans[1] += s[cur ^ 1];
    ++s[cur];
  }
  cout << ans[1] << ' ' << ans[0] << '\n';
  return 0;
}
