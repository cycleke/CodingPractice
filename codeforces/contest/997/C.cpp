#include <cstdio>

const int MOD = 998244353;

long long ModPow(long long a, long long b) {
  long long res = 1;
  while (b) {
    if (b & 1) res = res * a % MOD;
    a = a * a % MOD;
    b >>= 1;
  }
  return res;
}

int main() {
  int n;
  scanf("%d", &n);
  long long c = 1;
  long long ans = ModPow(3, 1ll * n * n) - ModPow(ModPow(3, n) - 3, n);
  for (int i = 0; i <= n; ++i) {
    long long base = ModPow(3, n - i);
    long long result = c * (ModPow(base, n) - ModPow(base - (i == 0 ? 3 : 1) + MOD, n)) % MOD;
    if (i) result = result * 3 % MOD;
    if (i & 1) ans -= result;
    else ans += result;
    c = c * (n - i) % MOD * ModPow(i + 1, MOD - 2) % MOD;
  }
  ans = (ans % MOD + MOD) % MOD;
  printf("%lld\n", ans);
  return 0;
}
