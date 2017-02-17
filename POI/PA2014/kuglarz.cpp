#include <cstdio>
#include <algorithm>
struct edge {
	int u, v, w;
	bool operator < (const edge &a) const {
		return w < a.w;
	}
}e[2000 * 2000];

int f[2003];
inline int gf(int u) {
	static int r, t;
	for (r = u; f[r] ^ r; r = f[r]);
	while (u ^ r) {
		t = f[u];
		f[u] = r;
		u = t;
	}
	return r;
}

int main() {
	int n, i, j, u, v, m;
	edge *eit = e;
	scanf("%d", &n);
	for (i = 1; i <= n; ++i) {
		f[i] = i;
		for (j = i; j <= n; ++j) {
		  scanf("%d", &u);
		  *eit++ = (edge) {i - 1, j, u};
		}
	}
	std::sort(e, eit);
	long long ans = 0;
	m = n;
	for (edge *it = e; it < eit; ++it) {
		u = gf(it->u), v = gf(it->v);
		if (u ^ v) {
			ans += it->w;
			f[u] = v;
			if (!--m)
			  break;
		}
	}
	printf("%lld\n", ans);
	return 0;
}
