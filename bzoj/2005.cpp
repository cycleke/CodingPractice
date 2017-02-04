#include <cstdio>
int main() {
	unsigned int n, m;
	register unsigned int i, j;
	register unsigned long long ans = 0;
	unsigned long long f[100003];
	scanf("%u%u", &n, &m);
	if (m < n) n ^= m ^= n ^= m;
	for (i = n; i; --i) {
		f[i] = (long long)(n / i) * (m / i);
		for (j = i << 1; j <= n; j += i)
			f[i] -= f[j];
		ans += f[i] * ((i << 1) - 1);
	}
	printf("%llu\n", ans);
	return 0;
}
