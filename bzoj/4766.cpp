#include <cstdio>

typedef unsigned long long ull;
ull n, m, p;

inline ull add(ull a, ull b) {
	a += b;
	return a < p ? a : (a - p);
}

inline ull mul(ull a, ull b) {
	static ull r;
	for (r = 0; b; b >>= 1, a = add(a, a))
		if (b & 1) r = add(a, r);
	return r;
}

inline ull pw(ull a, ull b) {
	static ull r;
	for (r = 1; b; b >>= 1, a = mul(a, a))
		if (b & 1) r = mul(a, r);
	return r;
}

int main() {
	scanf("%llu%llu%llu", &n, &m, &p);
	printf("%llu\n", mul(pw(n % p, m - 1), pw(m % p, n - 1)));
	return 0;
}
