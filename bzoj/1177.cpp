#include <cstdio>

inline int max(const int &a, const int &b, const int &c) {
	static int t;
	t = (a < b) ? b : a;
	return t < c ? c : t;
}

inline void cmax(int &a, const int &b) {
	if (a < b) a = b;
}

typedef int mat[1505][1505];

mat a, b, c, d, s;

#define R(i, l, r) for (register int i = l, i##end = r; i <= i##end; ++i)
#define F(i, l, r) for (register int i = r, i##end = l; i >= i##end; --i)

int main() {
	int n, m, k, x, ans = 0;
	scanf("%d%d%d", &n, &m, &k);
	R(i, 1, n) R(j, 1, m) {
		scanf("%d", &x);
		s[i][j] = s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1] + x;
	}

	F(i, k, n) F(j, k, m) s[i][j] -= s[i - k][j] + s[i][j - k] - s[i - k][j - k];
	
	R(i, k, n) R(j, k, m) a[i][j] = max(s[i][j], a[i - 1][j], a[i][j - 1]);
	R(i, k, n) F(j, k, m) b[i][j] = max(s[i][j], b[i - 1][j], b[i][j + 1]);
	F(i, k, n) R(j, k, m) c[i][j] = max(s[i][j], c[i + 1][j], c[i][j - 1]);
	F(i, k, n) F(j, k, m) d[i][j] = max(s[i][j], d[i + 1][j], d[i][j + 1]);

	R(i, k, n - k) R(j, k, m - k) cmax(ans, a[i][j] + b[i][j + k] + c[i + k][m]);
	R(i, k, n - k) R(j, k + k, m) cmax(ans, b[i][j] + d[i + k][j] + a[n][j - k]);
	R(i, k + k, n) R(j, k, m - k) cmax(ans, c[i][j] + d[i][j + k] + a[i - k][m]);
	R(i, k + k, n) R(j, k + k, m) cmax(ans, a[i][j] + c[i + k][j] + d[k][j + k]);
	
	R(i, k, n) R(j, k + k, m - k) cmax(ans, s[i][j] + a[n][j - k] + b[n][j + k]);
	R(i, k + k, n - k) R(j, k, m) cmax(ans, s[i][j] + a[i - k][m] + c[i + k][m]);
	
	printf("%d\n", ans);
	
	return 0;
}
