#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int MaxN = 1203;
const double eps = 1e-12, oo = 1e99;

#define rep(i, l, r) for (int i = l; i <= r; ++i)

double a[MaxN][MaxN];
int n, m, t, L[MaxN], E[MaxN], b[MaxN];

void pivot(int l, int e) {
	swap(L[l], E[e]);
	double k = a[l][e];
	a[l][e] = 1.0;
	rep(i, 0, n) a[l][i] /= k;
	int len = 0;
	rep(i, 0, n) if (fabs(a[l][i]) > eps) b[++len] = i;
	rep(i, 0, m) if ((l ^ i) && fabs(a[i][e]) > eps) {
		k = a[i][e];
		a[i][e] = 0.0;
		rep(j, 1, len) a[i][b[j]] -= k * a[l][b[j]];
	}
}

double simplex() {
	int l, e;
	double mn;
	while (true) {
		for (e = 1; e <= n; ++e)
			if (a[0][e] > eps) break;
		if (e > n)
			return -a[0][0];
		mn = oo;
		rep(i, 1, m)
			if (a[i][e] > eps && a[i][0] / a[i][e] < mn) {
				mn = a[i][0] / a[i][e];
				l = i;
			}
		if (mn == oo)
			return oo;
		pivot(l, e);
	}
}

int main() {
	int k, num, x;
	scanf("%d%d", &n, &k);
	num = n;
	n *= 3;
	rep(i, 1, n) {
		scanf("%d", &x);
		a[0][i] = x;
		++m;
		a[m][i] = 1;
		a[m][0] = 1;
	}
	rep(i, 1, n - num + 1) {
		++m;
		rep(j, i, i + num - 1)
			a[m][j] = 1;
		a[m][0] = k;
	}
	double ans = simplex();
	printf("%.0lf\n", ans);
	return 0;
}
