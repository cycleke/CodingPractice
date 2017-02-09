#include <bits/stdc++.h>
using namespace std;
#define V 1003
#define N 100003
#define MaxS 10360
int C[N], p[17][N], a[N];
int main() {
	int n, m, v, i, j, x, lg, lim, opt, l, r, t;
	scanf("%d%d%d", &n, &m, &v);
	for (lim = 0; (1 << lim) <= v; ++lim);
	for (lg = 0; (1 << lg) <= m; ++lg);
	for (i = 1; i <= n; ++i)
		scanf("%d", a + i);
	for (i = 0; i < v; ++i)
		p[0][i] = (long long)i * i * i % v;
	for (i = 1; i < lg; ++i)
		for (j = 0; j < v; ++j)
			p[i][j] = p[i - 1][p[i - 1][j]];
	while (m--) {
		scanf("%d%d%d", &opt, &l, &r);
		if (opt & 1) {
			if (r - l >= lim) puts("Yuno");
			else {
				bitset<MaxS>s(1U);
				for (i = l; i <= r; ++i) {
					x = a[i], t = 0;
					for (j = i; j; j ^= j & -j)
						t += C[j];
					for (j = 0; j < lg; ++j)
						if (t >> j & 1) x = p[j][x];
					++x;
					if ((s & s << x).any()) {
						puts("Yuno");
						goto ANS;
					}
					s |= s << x;
				}
				puts("Yuki");
			ANS:;
				}
		} else {
			for (i = l; i <= n; i += i & -i) ++C[i];
			for (i = r + 1; i <= n; i += i & -i) --C[i];
		}
	}
	return 0;
}
