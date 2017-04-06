#include <cstdio>

int main() {
	static int n, m, ans, mod(20100403), fac[2000005], inv[2000005], fac_inv[2000005];
	fac[0] = fac_inv[0] = 1;
	fac[1] = inv[1] = fac_inv[1] = 1;
	scanf("%d%d", &n, &m);
	for (register int i = 2, t = n + m + 1; i < t; ++i) {
		fac[i] = 1ll * fac[i - 1] * i % mod;
		inv[i] = 1ll * (mod - mod / i) * inv[mod % i] % mod;
		fac_inv[i] = 1ll * fac_inv[i - 1] * inv[i] % mod;
	}
	ans = 1ll * fac[n + m] * fac_inv[n] % mod * fac_inv[m] % mod - 1ll * fac[n + m] * fac_inv[n + 1] % mod * fac_inv[m - 1] % mod;
	if (ans < 0) ans += mod;
	printf("%d\n", ans);
	return 0;
}
