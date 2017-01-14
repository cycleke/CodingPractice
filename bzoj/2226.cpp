#include <cstdio>
#define N 1000003
int main() {
	static int n, __, i, j, k;
	static long long ans[N], phi[N];
	for (i = 2; i < N; ++i)
		if (!phi[i]) for (j = i; j < N; j += i) {
				if (!phi[j]) phi[j] = j;
				phi[j] = phi[j] / i * (i - 1);
			}
	ans[1] = 1LL;
	for (i = 2; i < N; ++i)
		ans[i] = ((long long)i * i * phi[i] >> 1) + i;
	for (i = 2; ; ++i) {
		j = i * i;
		if (j > N) break;
		ans[j] += (long long)j * i * phi[i] >> 1;
		for (j += i, k = i + 1; j < N; j += i, ++k)
			ans[j] += ((long long)j * phi[i] * i >> 1) + ((long long)j * phi[k] * k >> 1);
	}
	scanf("%d", &__);
	while (__--) scanf("%d", &n), printf("%lld\n", ans[n]);
	return 0;
}
