#include <cstdio>

typedef unsigned long long u64;
const u64 mod = 19940417;
const u64 inv2 = 9970209, inv3 = 3323403;


inline u64 g1(u64 n, u64 m) {
	u64 ans = 0, i = 1, last, t;
	for (; i <= n; i = last + 1) {
		t = m / i;
		last = m / t;
		if (last > n) last = n;
		ans += ((last - i + 1) * (i + last) >> 1) % mod * t % mod;
		if (ans >= mod) ans -= mod;
	}
	return ans;
}

inline u64 s2(u64 n) {
	u64 t1 = n, t2 = n + 1, t3 = n << 1 | 1;
	if (t1 & 1) t2 >>= 1;
	else t1 >>= 1;
	if (t1 % 3 == 0) t1 /= 3;
	else if (t2 % 3 == 0) t2 /= 3;
	else t3 /= 3;
	return t1 * t2 % mod * t3 % mod;
}

inline u64 min(const u64 &a, const u64 &b) {
	return a < b ? a : b;
}

inline u64 g2(u64 n, u64 m, u64 k) {
	u64 ans = 0, i = 1, last, t1, t2;
	for (; i <= k; i = last + 1) {
		t1 = n / i;
		t2 = m / i;
		last = min(k, min(n / t1, m / t2));
		ans += (s2(last) + mod - s2(i - 1)) % mod * t1 % mod * t2 % mod;
		if (ans >= mod) ans -= mod;
	}
	return ans;
}

int main() {
	u64 n, m, ans, t1, t2;
	scanf("%llu%llu", &n, &m);
	if (n < m) n ^= m ^= n ^= m;
	t1 = (n * n % mod + mod - g1(n, n)) % mod * (m * m % mod + mod - g1(m, m)) % mod;
	t2 = m * m % mod * n % mod + mod - g1(m, n) * m % mod + mod - g1(m, m) * n % mod + mod + g2(n, m, m);
	t2 %= mod;
	ans = t1 + mod - t2;
	if (ans >= mod) ans -= mod;
	printf("%llu\n", ans);
	return 0;
}
