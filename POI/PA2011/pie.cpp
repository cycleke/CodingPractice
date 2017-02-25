#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>

const int MaxN = 1050010;

bool v[MaxN], vis[MaxN * 2];
int a[66], p[MaxN], tot;
long long b[66], q[MaxN * 2], t, lim;

inline long long limitedpow(long long a, int b) {
	static long long r;
	for (r = 1; b; --b, r *= a)
		if (a > lim / r) return lim + 1;
	return r;
}

inline long long fastpow(long long a, int b) {
	static long long r;
	for (r = 1; b; b >>= 1, a *= a)
		if (b & 1) r *= a;
	return r;
}

inline void sieve(const long long &n) {
	int i, j, t;
	for (tot = 0, i = 2; i <= n; ++i) {
		if (!v[i])
			p[tot++] = i;
		for (j = 0; (t = i * p[j]) <= n; ++j) {
			v[t] = true;
			if (i % p[j] == 0) break;
		}
	}
}

inline void check(const int &x) {
	for (long long i = std::max(t / x * x, 2LL * x); i <= lim; i += x)
		if (i >= t) vis[i - t] = true;
}
	
int main() {
	int i, j, k, cnt = 0, m = 0;
	long long n, o;
	scanf("%lld%d", &n, &k);
	for (t = std::max((long long)sqrt(n) - 10, 2LL); t * t <= n; ++t);
	lim = t + std::max(k, 10) * 21;
	sieve((long long)sqrt(lim) + 5);
	for (i = 0; i < tot; ++i)
		check(p[i]);
	for (o = t; o <= lim && cnt < k; ++o)
		if (!vis[o - t]) q[++cnt] = o * o;
	lim = q[cnt];
	for (i = 3; (1LL << i) <= lim; a[++m] = i++);
	for (o = 2; (o + 1) * (o + 1) * (o + 1) <= lim; ++o);
	b[1] = o;
	for (i = 2; i <= m; ++i)
		for (b[i] = b[i - 1]; limitedpow(b[i], a[i]) > lim; --b[i]);

	sieve(std::max(b[1], (long long)a[m]));

	for (i = 1; i <= m; ++i)
		if (!v[a[i]]) {
			for (j = 0; j < tot && fastpow(p[j], a[i]) <= n; ++j);
			for (; j < tot && p[j] <= b[i]; ++j)
				q[++cnt] = fastpow(p[j], a[i]);
		}
	std::sort(q + 1, q + cnt + 1);
	printf("%lld\n", q[k]);
	return 0;
}
