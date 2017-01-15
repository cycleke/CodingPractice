#include <cmath>
#include <cstdio>
inline int gi() {
	static int a; static char c;
	while ((c = getchar()) < '0'); a = c - '0';
	while ('-' < (c = getchar())) a = (a << 3) + (a << 1) + c - '0';
	return a;
}
const int N = 1003, M = 10003;
const double inf = 1e9, eps = 1e-9;
int n, m;
double a[M][N], b[M], c[N], v;
void pivot(int l, int e) {
	static int i, j;
	b[l] /= a[l][e];
	for (j = 1; j <= n; ++j) if (j ^ e) a[l][j] /= a[l][e];
	a[l][e] = 1 / a[l][e];
	for (i = 1; i <= m; ++i)
		if ((i ^ l) && fabs(a[i][e]) > 0) {
			b[i] -= a[i][e] * b[l];
			for (j = 1; j <= n; ++j) if (j ^ e) a[i][j] -= a[i][e] * a[l][j];
			a[i][e] = -a[i][e] * a[l][e];
		}
	v += c[e] * b[l];
	for (j = 1; j <= n; ++j) if (j ^ e) c[j] -= c[e] * a[l][j];
	c[e] = -c[e] * a[l][e];
}
double simplex() {
	int e, l, i;
	double mn;
	while (true) {
		for (e = 1; e <= n; ++e) if(c[e] > eps) break;
		if (e > n) return v;
		for (i = 1, mn = inf; i <= m; ++i)
			if (a[i][e] > eps && mn > b[i] / a[i][e]) mn = b[i] / a[i][e], l = i;
		if (mn == inf) return inf;
		pivot(l, e);
	}
}

int main() {
	int i, j, s, t;
	n = gi(), m = gi();
	for (i = 1; i <= n; ++i) c[i] = gi();
	for (i = 1; i <= m; ++i) {
		s = gi(), t = gi();
		for (j = s; j <= t; ++j) a[i][j] = 1;
		b[i] = gi();
	}
	printf("%d", (int)(simplex() + 0.5));
	return 0;
}
