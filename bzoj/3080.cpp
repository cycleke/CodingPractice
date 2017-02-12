#include <cmath>
#include <cstdio>
#include <algorithm>
struct edge {
	int u, v, w;
	bool operator < (const edge &a) const {
		return w < a.w;
	}
}e[1001];
struct nedge {
	int u, v;
	double w2, w;
	nedge() {}
	nedge(const edge &a, const double &avg) {
		u = a.u, v = a.v;
		w = a.w - avg;
		w2 = w * w;
	}
	bool operator < (const nedge &a) const {
		return w2 < a.w2;
	}
}ne[1001];
int f[51];
int gf(int u) {
	return (u ^ f[u]) ? f[u] = gf(f[u]) : u;
}
int main() {
	//freopen("t.in", "r", stdin);
	int n, m, i, u, v, sum, _sum, _ = 0, cnt;
	double average, ans, tmp, chk;
	while (scanf("%d%d", &n, &m), n) {
		if (n == 1) {
			printf("Case %d: 0.00\n", ++_);
			continue;
		}
		sum = _sum = 0;
		for (i = 0; i < m; ++i) 
		  scanf("%d%d%d", &e[i].u, &e[i].v, &e[i].w);
		std::sort(e, e + m);
		for (i = 1; i < n; ++i)
		  _sum += e[m - i].w;
		for (i = 1; i < n; ++i)
		  sum += e[i - 1].w;
		ans = 1e22;
		for (;sum <= _sum; ++sum) {
			for (i = 1; i <= n; ++i) f[i] = i;
			average = (double)sum / (n - 1);
			for (i = 0; i < m; ++i) 
			  ne[i]= nedge(e[i], average);
			std::sort(ne, ne + m);
			chk = tmp = 0; cnt = n - 1;
			for (i = 0;; ++i) {
				u = gf(ne[i].u), v = gf(ne[i].v);
				if (u ^ v) {
					tmp += ne[i].w2;
					chk += ne[i].w;
					f[u] = v;
					if (!--cnt) break;
				}
			}
			if (fabs(chk) < 1e-6 && tmp < ans) ans = tmp;
		}
		printf("Case %d: %.2lf\n", ++_, ans / (n - 1));
	}
	return 0;
}
