#include <cstdio>
const int mo = 1e9 + 7, N = 100051;
int f[N];
int pw(int a, int b) {
	static int r;
	for (r = 1; b; b >>= 1, a = (long long)a * a % mo)
		if (b & 1) r = (long long)r * a % mo;
	return r;
}
int main() {
	int n, k, a, b, l, r, L, R, i, j;
	scanf("%d%d%d%d", &n, &k, &a, &b);
	l = a / k, r = b / k;
	if (a % k) ++l;
	if (l <= r) for (i = b - a; i; --i) {
		L = l / i, R = r / i;
		if (l % i) ++L;
		f[i] = pw(R - L + 1, n) - (R - L + 1) + mo;
		while (f[i] >= mo) f[i] -= mo;
		for (j = i << 1; j <= b - a; j += i)
			for(f[i] += mo - f[j]; f[i] >= mo; f[i] -= mo);
	}
	if (l == 1) ++f[1] >= mo ? f[1] -= mo : 1;
	printf("%d\n", f[1]);
	return 0;
}
