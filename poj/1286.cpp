#include <cstdio>

inline long long qp(long long a, int b) {
	static long long r;
	for (r = 1; b; b >>= 1, a *= a)
		if (b & 1) r *= a;
	return r;
}

inline int gcd(int a, int b) {
	for (static int t; b; t = a % b, a = b, b = t);
	return a;
}

inline long long solve(int n, int m) {
	static long long ret;
	if (n == 0)
		return 0LL;
	ret = 0;
	for (register int i = 0; i < n; ++i)
		ret+= qp(m, gcd(n, i));
	if (n & 1)
		ret += n * qp(m, (n >> 1) + 1);
	else
		ret += n / 2 * (qp(m, n >> 1) * (1 + m));
	return ret / 2 / n;
}

int main() {
	int n;
	while (scanf("%d", &n) != EOF && (~n))
		printf("%lld\n", solve(n, 3));
	return 0;
}
