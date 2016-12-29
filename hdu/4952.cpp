#include <cstdio>

int main() {
	long long x, k, i, t; int ca = 0;
	while (scanf("%lld%lld", &x, &k) ^ EOF) {
		if (!x && !k) break;
		for (i = 2; i <= k; ++i)
		  if (x % i) {
			  t = x / i + 1;
			  (t > i) ? (x = t * i) : (x = t * k, i = k + 1);
		  }
		printf("Case #%d: %lld\n", ++ca, x);
	}
	return 0;
}
