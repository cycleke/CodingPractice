#include <cstdio>
#define ull unsigned long long
int main() {
	unsigned int n, k;
	ull ans = 0;
	scanf("%u%u", &n, &k);
	if (n > k) ans = (ull)(n - k) * k, n = k;
	for (unsigned int i = 1, r, t; i <= n; i = r + 1) {
		t = k / i;
		r = k / t;
		if (r > n) r = n;
		ans += (ull)(r - i + 1) * k - (ull)(r - i + 1) * (i + r) / 2 * t;
	}
	printf("%llu\n", ans);
	return 0;
}
