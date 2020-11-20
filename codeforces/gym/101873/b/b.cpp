#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

int mod_pow(int a, int b) {
  int r = 1;
  for (; b; b >>= 1, a = 1LL * a * a % MOD)
    if (b & 1) r = 1LL * a * r % MOD;
  return r;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m, c;
  cin >> n >> m >> c;

  int ans = 0;
  for (int i = 1; i <= m; ++i)
    ans = (ans + mod_pow(c, n * n * __gcd(i, m))) % MOD;
  ans = 1LL * ans * mod_pow(m, MOD - 2) % MOD;
  cout << ans << '\n';
  return 0;
}
