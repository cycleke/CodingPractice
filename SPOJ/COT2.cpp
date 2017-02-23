#include <cstdio>
#include <cstring>
#include <algorithm>

const int MaxN = 43210, MaxM = 100012;

#define wlp while

struct edge {
	int to;
	edge *nxt;
} edge_mest[MaxN << 1], *cedge, *g[MaxN];

#define eachedge(u) for (edge *it = g[u]; it; it = it->nxt)

inline void add_edge(int a, int b) {
	*cedge = (edge) {b, g[a]};
	g[a] = cedge++;
}

bool mark[MaxN];
typedef int arr[MaxN];
int dfn, dq[MaxN << 1], now, ans[MaxM];
arr top, fa, son, sz, dep, in, ou, cnt, w, ha;

void d1(int u) {
	sz[u] = 1;
	eachedge(u)
		if (it->to ^ fa[u]) {
			fa[it->to] = u;
			dep[it->to] = dep[u] + 1;
			d1(it->to);
			if (sz[son[u]] < sz[it->to])
				son[u] = it->to;
			son[u] = it->to;
		}
}
void d2(int u, int anc) {
	top[u] = anc;
	dq[in[u] = ++dfn] = u;
	if (son[u]) d2(son[u], anc);
	eachedge(u) if (!top[it->to])
		d2(it->to, it->to);
	dq[ou[u] = ++dfn] = u;
}
inline int Lca(int u, int v) {
	wlp (top[u] ^ top[v])
		dep[top[u]] < dep[top[v]] ? v = fa[top[v]] : u = fa[top[u]];
	return dep[u] < dep[v] ? u : v;
}

struct ask {
	int l, r, _l, id, lca;
}q[MaxM];

bool operator < (const ask &a, const ask &b) {
	return (a._l ^ b._l) ? a._l < b._l : a.r < b.r;
}

inline void rev(int u) {
	if (mark[u]) {
		--cnt[w[u]];
		if (!cnt[w[u]]) --now;
	} else {
		if (!cnt[w[u]]) ++now;
		++cnt[w[u]];
	}
	mark[u] ^= 1;
}

int main() {
	//freopen("tt.in", "r", stdin);
	int n, m, *end, i, l, r, _l, _r, u, v, z;
	wlp (scanf("%d%d", &n, &m) != EOF) {
		end = ha;
		for (i = 1; i <= n; ++i) {
			scanf("%d", end);
			w[i] = *end++;
			g[i] = NULL;
			cnt[i] = mark[i] = son[i] = top[i] = 0;
		}
		std::sort(ha, end);
		end = std::unique(ha, end);
		for (i = 1; i <= n; ++i)
			w[i] = std::lower_bound(ha, end, w[i]) - ha;
		
		cedge = edge_mest;
		for (i = 1; i < n; ++i) {
			scanf("%d%d", &u, &v);
			add_edge(u, v);
			add_edge(v, u);
		}

		dfn = 0;
		d1(1);
		d2(1, 1);
		
		for (l = 1; l * l <= n * 2; ++l);
		
		for (i = 0; i < m; ++i) {
			scanf("%d%d", &u, &v);
			z = Lca(u, v);
			if (in[u] > in[v])
				std::swap(u, v);
			if (z ^ u)
				q[i] = (ask){ou[u], in[v], ou[u] / l, i, z};
			else
				q[i] = (ask){in[u], in[v], in[u] / l, i, 0};
		}
		
		std::sort(q, q + m);
		
		l = 1, r = 0, now = 0;
		for (i = 0; i < m; ++i) {
			_l = q[i].l, _r = q[i].r;
			wlp (l < _l) rev(dq[l++]);
			wlp (_l < l) rev(dq[--l]);
			wlp (r < _r) rev(dq[++r]);
			wlp (_r < r) rev(dq[r--]);
			if (q[i].lca) rev(q[i].lca);
			ans[q[i].id] = now;
			if (q[i].lca) rev(q[i].lca);
		}
		
		for (i = 0; i < m; ++i)
			printf("%d\n", ans[i]);
	}
	return 0;
}
