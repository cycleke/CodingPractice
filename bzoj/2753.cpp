#include <cstdio>
#include <algorithm>

const int MaxN = 100003, MaxM = 1000000 * 2 + 1;

bool mark[MaxN];
int h[MaxN], f[MaxN], que[MaxN];

struct eg {
	int to;
	eg *nxt;
} eg_mset[MaxM], *g[MaxN], *ceg = eg_mset;

void add_eg(int u, int v) {
	*ceg = (eg) {v, g[u]};
	g[u] = ceg++;
}

struct edge {
	int u, v, w;
	bool operator < (const edge &a) const {
		return (h[v] ^ h[a.v]) ? h[v] > h[a.v] : w < a.w;
	}
} e[MaxM >> 1];

inline int gf(int u) {
	static int r, t;
	for (r = u; f[r] ^ r; r = f[r]);
	while (u ^ r) t = f[u], f[u] = r, u = t;
	return r;
}

int main() {
	eg *it;
	long long sum = 0LL;
	int n, m, u, v, w, i, cnt = 0, *l = que, *r = que;
	scanf("%d%d", &n, &m);
	for (i = 1; i <= n; ++i) {
		scanf("%d", h + i);
		f[i] = i;
	}
	for (i = 0; i <  m; ++i) {
		scanf("%d%d%d", &u, &v, &w);
		if (h[u] < h[v]) std::swap(u, v);
		if (h[u] ^ h[v]) add_eg(u, v);
		else add_eg(u, v), add_eg(v, u);
		e[i] = (edge){u, v, w};
	}
	mark[1] = true;
	for (*r++ = 1; l < r;) {
		u = *l++;
		++cnt;
		for (it = g[u]; it; it = it->nxt)
			if (!mark[it->to]) {
				*r++ = it->to;
				mark[it->to] = true;
			}
	}
	std::sort(e, e + m);
	for (i = 0; i < m; ++i)
		if (mark[e[i].u] && mark[e[i].v]) {
			u = gf(e[i].u);
			v = gf(e[i].v);
			if (u == v)
				continue;
			f[u] = v;
			sum += e[i].w;
		}
	printf("%d %lld\n", cnt, sum);
	return 0;
}
