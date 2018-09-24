#include <cstdio>
#include <cstdlib>
#include <algorithm>
const int maxn(100005);
#define _(i, n) for (register int i = 1; i <= n; ++i)
int n, m, p, a[maxn][105], b[105], c[105][105], r[maxn];

inline int calc(int i) {
	int s = 0;
	if (p == 2)
		_(j, m) s ^= b[j] & a[i][j], b[j] ^= a[i][j];
	else
		_(j, m) _(k, m) {
			s += c[j][k] * a[i][j] * a[i][k];
			c[j][k] += a[i][j] * a[i][k];
		}
	return s % p;
}

inline void check(int i, int j) {
	int s = 0;
	_(k, m) s += a[i][k] * a[j][k];
	if (s % p == 0) {
		if (i > j) printf("%d %d\n", j, i);
		else printf("%d %d\n", i, j);
		exit(0);
	}
}

int main() {
	scanf("%d%d%d", &n, &m, &p);
	_(i, n) _(j, m) scanf("%d", a[i] + j), a[i][j] %= p;
	_(i, n) r[i] = i;
	srand(19260817);
	std::random_shuffle(r + 1,r + n + 1);
	_(i, n) if (calc(r[i]) != (i - 1) % p)
		_(j, n) check(r[i], r[j]);
	puts("-1 -1");
	return 0;
}
