#include <cstdio>
#include <cstring>

const int mod(1e6 + 3);

int fac[mod], inv[mod], fac_inv[mod];

inline void init() {
	fac[0] = fac_inv[0] = 1;
	fac[1] = inv[1] = fac_inv[1] = 1;
	for (register int i = 2; i < mod; ++i) {
		fac[i] = 1ll * fac[i - 1] * i % mod;
		inv[i] = (mod - mod / i) * 1ll * inv[mod % i] % mod;
		fac_inv[i] = 1ll * fac_inv[i - 1] * inv[i] % mod;
	}
}

inline int lucas(int n, int m) {
	int ret = 1, _n, _m;
	while (n && m) {
		_n = n % mod, _m = m % mod;
		if (_n < _m) return 0;
		ret = 1ll * ret * fac[_n] % mod * fac_inv[_m] % mod * fac_inv[_n - _m] % mod;
		n /= mod, m /= mod;
	}
	return ret;
}

int main() {
	init();

	int o_o, n, l, r, ans;
	scanf("%d", &o_o);

	while (o_o--) {
		scanf("%d%d%d", &n, &l, &r);
		ans = lucas(n + r - l + 1, n) - 1;
		if (ans < 0) ans += mod;
		printf("%d\n", ans);

	}

	return 0;
}
