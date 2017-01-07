#include <cstdio>
#include <cstring>
const int N = 50010, mo = 1e9 + 7;
int fac[N], phi[N], sum[N];
void init() {
	int i, j;
	for (i = 2; i ^ N; ++i)
		if (!fac[i]) {
			for (j = i; j < N; j += i)
						 fac[j] = i;
		}
	phi[1] = 1;
	for (i = 2; i ^ N; ++i) {
		if (fac[i] ^ fac[i / fac[i]])
			phi[i] = phi[i / fac[i]] * (fac[i] - 1);
		else
			phi[i] = phi[i / fac[i]] * fac[i];
		//printf("%d %d\n", i, phi[i]);
	}
	sum[0] = 0;
	for (i = 1; i ^ N; ++i) {
		sum[i] = sum[i-1] + phi[i];
		if (sum[i] >= mo)
			sum[i] -= mo;
	}
}
int min(const int&a,const int&b) {
	return a < b ? a : b;
}
int f(int n, int m) {
	static int ans, i, r;
	for (i = 1, ans = 0; i <= n && i <= m; i = r + 1) {
		r = min(n / (n / i), m / (m / i));
		ans += (long long)(mo + sum[r] - sum[i - 1]) * (n / i) % mo* (m / i) % mo;
		if (ans >= mo)
			ans -= mo;
	}
	return ans;
}
int main() {
//	freopen("t.in", "r", stdin);
	init();
	int a, b, c, d, __, ans;
	scanf("%d%*d%*d", &__);
	while (__--) {
		scanf("%d%d%d%d", &a, &b, &c, &d);
		--a;
		--b;
		ans = ((long long)f(a, b) + f(c, d) - f(a, d) - f(c, b) + mo + mo) % mo;
		printf("%d\n", ans);
	}
	return 0;
}
