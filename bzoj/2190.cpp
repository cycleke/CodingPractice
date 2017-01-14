#include <cstdio>
const int N = 40003;
int main() {
	static unsigned int n, i, j, fac[N], phi[N];
	static unsigned long long ans;
	scanf("%u", &n);
	for (i = 2; i < n; ++i)
		if (!fac[i]) for (j = i; j < n; j += i)
			fac[j] = i;
	phi[1] = 1;
	for (i = 2; i < n; ++i)
		if (fac[i] ^ fac[j = i / fac[i]])
			phi[i] = phi[j] * (fac[i] - 1);
		else phi[i] = phi[j] * fac[i];
	for (i = 1; i < n; ++i)
		ans += phi[i];
	ans = ans * 2 + 1;
	printf("%llu\n", ans);
	return 0;
}
