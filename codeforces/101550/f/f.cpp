#include <bits/stdc++.h>
using namespace std;

typedef double ld;

int n, p;

inline ld gao(int d) {
  ld ans = 1.0 * p * d / (n + d + 1 - p);
  for (int i = 0; i <= p - 2; ++i) ans = ans * (n - i) / (n + d - i);
  return ans;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout << fixed << setprecision(10);

  cin >> n >> p;
  cout << gao(n / (p - 1)) << '\n';
  // cout << ans << '\n';
  return 0;
}
