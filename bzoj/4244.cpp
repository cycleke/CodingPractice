#include <cstdio>
#include <cstring>
#define rep(a, l, r) for (a = l; a <= r; ++a)
long long f[3003][3003];
inline void cmin(long long &a, const long long &b) {
	if (b < a) a = b;
}
inline long long min(const long long &a, const long long &b) {
	return a < b ? a : b;
}
int main() {
	int n, t, u, v, d, e;
	register int i, j;
	scanf("%d%d", &n, &t);
	memset(f, 63, sizeof f);
	f[0][0] = 0;
	rep(i, 1, n) {
		scanf("%d%d%d%d", &u, &v, &d, &e);
		rep(j, 0, n) f[i - 1][j] += j * t << 1;
		rep(j, 0, n) {
			if (j) f[i][j] = min(min(f[i - 1][j - 1], f[i][j - 1]) + v + d, f[i - 1][j] + d + e);
			if (j < n) cmin(f[i][j], f[i - 1][j + 1] + u + e);
			cmin(f[i][j], f[i - 1][j] + u + v);
		}
		for (j = n - 1; ~j; --j) cmin(f[i][j], f[i][j + 1] + u + e);
	}
	printf("%lld\n", f[n][0] + (n + 1) * t);
	return 0;
}
