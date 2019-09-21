#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int a1, a2, k1, k2, n;
  cin >> a1 >> a2 >> k1 >> k2 >> n;
  if (k1 > k2) swap(a1, a2), swap(k1, k2);

  cout << max(n - a1 * (k1 - 1) - a2 * (k2 - 1), 0) << ' ';

  int ans = min(n / k1, a1);
  n -= ans * k1;
  ans += min(n / k2, a2);
  cout << ans << '\n';
  return 0;
}
