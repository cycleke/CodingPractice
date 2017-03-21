#include <cstdio>
const int MaxN = 2e5 + 7;
long long f[MaxN][20], g[MaxN][20];
int a[MaxN], b[MaxN], d[MaxN], l[MaxN];
struct FI {
	char b[5<<19], *s;
	FI() : s(b) {
		b[fread(b, 1, 5 << 19, stdin)] = 0;
	}
	inline void gi(int &a) {
		a = 0;
		while (*s < 48) ++s;
		while (32 < *s) a = (a << 3) + (a << 1) + *s++ - 48;
	}
} io;
inline long long min(const long long &a, const long long &b) {
	return a < b ? a : b;
}
int main() {
	int n;
	io.gi(n);
	for (register int i = 1; i <= n; ++i) io.gi(a[i]);
	l[1] = 1;
	for (register int i = 2; i <= n; ++i) {
		io.gi(b[i]);
		l[i] = l[i >> 1] + 1;
		d[i] = d[i >> 1] + b[i];
	}
	for (register int x = n, y, lc, rc, i; x; --x)
		for (i = 0; i < l[x]; ++i) {
			lc = x << 1;
			rc = lc ^ 1;
			y = (x >> (l[x] - i - 1)) ^ 1;
			if (lc > n)
				f[x][i] = (long long)a[y] * (d[x] + d[y] - (d[y >> 1] << 1));
			else if (rc > n)
				f[x][i] = (long long)a[lc] * b[lc] + f[lc][i];
			else
				f[x][i] = min((long long)a[lc] * b[lc] + f[lc][l[x]] + f[rc][i], (long long)a[rc] * b[rc] + f[rc][l[x]] + f[lc][i]);
		}
	for (register int x = n, y, lc, rc, i; x; --x)
		for (i = 0; i <= l[x]; ++i) {
			lc = x << 1;
			rc = lc ^ 1;
			y = x >> (l[x] - i);
			if (lc > n)
				g[x][i] = (long long)a[y] * (d[x] - d[y]);
			else if (rc > n)
				g[x][i] = (long long)a[lc] * b[lc] + g[lc][i];
			else
				g[x][i] = min((long long)a[lc] * b[lc] + f[lc][l[lc] - 1] + g[rc][i], (long long)a[rc] * b[rc] + f[rc][l[rc] - 1] + g[lc][i]);
		}
	long long ans = g[1][0];
	for (register int i = 2; i <= n; ++i) {
		long long res = g[i][l[i] - 1];
		for (register int tmp = i, y, z; tmp ^ 1; tmp >>= 1) {
			y = tmp ^ 1;
			z = tmp >> 1;
			if (y > n)
				res += (long long)a[z >> 1] * b[z];
			else
				res += (long long)a[y] * b[y] + g[y][l[z] - 1];
		}
		if (res < ans) ans = res;
	}
	printf("%lld\n", ans);
	return 0;
}
