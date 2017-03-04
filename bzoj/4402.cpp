#include <cstdio>

#define un unsigned

const un int mod = 1000000007;
un int fac[2000003], inv[2000003];
#define rep(i, l, r) for (i = l; i <= r; ++i)
inline un int mmo(int a) {
	while (a >= mod) a -= mod;
	return a;
}
inline un int C(un int n, un int m) {
	if (n < 0) return 0U;
	n = (n >> 1) + m;
	return (un long long)fac[n] * inv[m] % mod * inv[n - m] % mod;
}
int main() {
	un int n, m, i, ans = 0;
	scanf("%u%u", &n, &m);
	fac[1] = inv[1] = 1;
	fac[0] = inv[0] = 1;
	rep(i, 2, n) fac[i] = (un long long)fac[i - 1] * i % mod;
	rep(i, 2, n) inv[i] = (un long long)inv[mod % i] * (mod - mod / i) % mod;
	rep(i, 2, n) inv[i] = (un long long)inv[i - 1] * inv[i] % mod;
	if (n && m) ans = 1;
	rep(i, 2, m) ans = mmo(ans + mmo(C(n - i, i - 1) + C(n - i - 1, i - 1)));
	printf("%u\n", ans);
	return 0;
}
