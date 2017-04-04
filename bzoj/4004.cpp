#include <cmath>
#include <cstdio>
#include <algorithm>

const int maxn(505);

int n, m, r[maxn], w[maxn];
long double a[maxn][maxn], b[maxn][maxn];

inline bool check(const int &x) {
	static bool v[maxn];
	for (register int i = 0; i < m; ++i)
		if (fabs(a[x][i]) > 1e-6) {
			if (v[i]) {
				long double k = a[x][i] / b[i][i];
				for (register int j = 0; j < m; ++j)
					a[x][j] -= k * b[i][j];
			} else {
				v[i] = true;
				for (register int j = 0; j < m; ++j)
					b[i][j] = a[x][j];
				return true;
			}
		}
		return false;
}

inline bool cmp(const int &i, const int &j) {
	return w[i] < w[j];
}

int main() {
	scanf("%d%d", &n, &m);
	for (register int i = 0; i < n; ++i) {
		r[i] = i;
		for (register int j = 0; j < m; ++j)
			scanf("%Lf", a[i] + j);
	}

	for (register int i = 0; i < n; ++i) scanf("%d", w + i);

	std::sort(r, r + n, cmp);

	int a1 = 0, a2 = 0;

	for (register int i = 0; i < n; ++i)
		if (check(r[i])) ++a1, a2 += w[r[i]];
	printf("%d %d\n", a1, a2);
	return 0;
}
