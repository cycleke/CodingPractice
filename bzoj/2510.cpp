#include <cstdio>
#include <cstring>
typedef double mat[1001];
mat a, b, q;
int n;
#define mmo(a) ((a) < n ? (a) : (a - n))
inline void mul(mat &a, mat &b) {
	static mat c;
	static int i, j;
	memset(c, 0, n << 3);
	for (i = 0; i < n; ++i)
		for (j = 0; j < n; ++j)
			c[mmo(i + j)] += a[i] * b[j];
	memcpy(a, c, n << 3);
}
int main() {
	int m, k;
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 0, x; i < n; ++i) {
		scanf("%d", &x);
		b[i] = x;
	}
	q[1] = 1.0 / m;
	*q = 1 - q[1];
	for (*a = 1; k; k >>= 1) {
		if (k & 1)
			mul(a, q);
		if (k >> 1)
			mul(q, q);
		else
			mul(b, a);
	}
	for (int i = 0; i < n; ++i)
		printf("%.3lf\n", b[i]);
	return 0;
}
