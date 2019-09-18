#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

inline int mod_pow(int a, long long b) {
  int res = 1;
  for (; b; b >>= 1, a = 1LL * a * a % MOD)
    if (b & 1) res = 1LL * res * a % MOD;
  return res;
}

void solve() {
  long long n;
  int m, sum = 0, C = 1;
  cin >> n >> m;
  for (int i = 0, end = (m >> 1) + 1; i < end; ++i) {
    sum = (sum + 1LL * C * mod_pow(i * 2 + (m & 1), n)) % MOD;
    C = 1LL * C * (m / 2 - i) % MOD * mod_pow(i + 1, MOD - 2) % MOD;
  }
  static int inv2 = mod_pow(2, MOD - 2);
  cout << 1LL * sum * mod_pow(inv2, m / 2) % MOD << '\n';
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  
  int o_o;
  for (cin >> o_o; o_o; --o_o) solve();

  return 0;
}
