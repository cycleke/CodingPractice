#include <cstdio>
unsigned long long a[500001];
int main() {
	unsigned int n, m, i, ct;
	unsigned long long ans = 0LL, _t;
	scanf("%u%u", &n, &m);
	for (i = 0; i < n; ++i) {
		scanf("%llu", &_t);
		ans ^= _t;
		a[i] = ans;
	}
	ans = 0;
	for (_t = 1LL << 60; _t; _t >>= 1) {
		for (i = ct = 0; i < n; ++i)
			if ((~a[i]) && (~a[i] & _t)) ++ct;
		if (ct >= m && (~a[n - 1] & _t))
			for (i = 0; i < n; ++i) {
				if ((~a[i]) && (a[i] & _t)) a[i] = -1;
			}
		else
			ans ^= _t;
	}
	printf("%llu\n", ans);
	return 0;
}
