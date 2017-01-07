#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;

#define fi first
#define se second
#define func(X,Y) a * X * X + b * X - Y
const double eps = 1e-10;
const int MS = (1 << 18) + 1;
pair < double, double > pig[21];
int __, n, m, dp[MS], i, j, t, k, pos[21], mark[MS], _vis, sta[399], cs, en, num[MS];
double a, b, X1, X2, Y1, Y2;
void cmin(int&a, const int&b) {
	if (b < a) a = b;
}
int Count(int i) {
	int cnt = 0;
	while (i)
		++cnt, i = i & (i - 1);
	return cnt;
}
int main() {
	scanf("%d", &__);
	for (i = 0; i < 21; ++i) pos[i] = 1 << i;
	for (i = 0; i < MS; ++i) num[i] = Count(i);
	while(__--) {
		++_vis;
		cs = 0;
		scanf("%d%d", &n, &m);
		for (i = 0; i < n; ++i)
			scanf("%lf%lf", &pig[i].fi, &pig[i].se);
		for (i = 0; i < n; ++i)
			for (j = i; j < n; ++j) 
				if (fabs(pig[i].fi - pig[j].fi) > eps) {
					X1 = pig[i].fi, X2 = pig[j].fi;
					Y1 = pig[i].se, Y2 = pig[j].se;
					a = (X2 * Y1 - X1 * Y2) / (X1 * X2 * (X1 - X2));
					if (a < -eps) {
						b = (Y1 - a * X1 * X1) / X1;
						t = 0;
						for (k = 0; k < n; ++k)
							if (fabs(func(pig[k].fi, pig[k].se)) < eps) t |= pos[k];
						if (mark[t] ^ _vis) {
							sta[cs++] = t;
							mark[t] = _vis;
						}
					}
				}
		/*printf("%d\n", cs);
		for (i = 0; i < cs; ++i)
			printf("%d\n", sta[i]);
		//puts("");*/
		en = 1 << n;
		for (i = 0; i < en; ++i)
			dp[i] = num[i];
		for (i = 0; i < cs; ++i)
			for (j = 0; j ^ en; ++j)
				cmin(dp[j|sta[i]], dp[j] + 1);
		/*for (i = 0; i < en; ++i)
			printf("%d\n", dp[i]);*/
		printf("%d\n", dp[en - 1]);
	}
	return 0;
}
