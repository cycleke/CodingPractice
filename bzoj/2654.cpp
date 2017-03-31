#include <cstdio>
#include <cstring>
#include <algorithm>

const int maxn(50005), maxm(100003);

struct edge {
	int u, v, w, color;
	inline edge modify(const int &delta) const {
		if (color)
			return *this;
		else
			return (edge) {u, v, w + delta, color};
	}
} e[maxm], xe[maxm];
int n, m, need, ans, f[maxn];

inline bool operator < (const edge &a, const edge &b) {
	return (a.w ^ b.w) ? a.w < b.w : a.color < b.color;
}

inline int gf(int u) {
	while (f[u] ^ u) u = f[u] = f[f[u]];
	return u;
}

inline bool check(int delta) {
	for (register int i = 0; i < m; ++i)
		xe[i] = e[i].modify(delta);
	for (register int i = 0; i < n; ++i)
		f[i] = i;
	int cnt = 0, sum = 0, u, v, _n = n - 1;
	std::sort(xe, xe + m);
	for (register int i = 0; i < m; ++i) {
		u = gf(xe[i].u), v = gf(xe[i].v);
		if (u ^ v) {
			f[u] = v;
			sum += xe[i].w;
			if (!xe[i].color) ++cnt;
			if (!--_n) break;
		}
	}
	if (cnt < need)
		return false;
	ans = sum - delta * need;
	if (cnt > need)
		return true;
	printf("%d\n", ans);
	exit(0);
}

int main() {

	//freopen("2654.in", "r", stdin);

	scanf("%d%d%d", &n, &m, &need);

	for (register int i = 0; i < m; ++i)
		scanf("%d%d%d%d", &e[i].u, &e[i].v, &e[i].w, &e[i].color);

	for (int l = -100, r = 100, mid; l <= r; )
		if (check(mid = (l + r) >> 1))
			l = mid + 1;
		else
			r = mid - 1;
	printf("%d\n", ans);

	return 0;
}
