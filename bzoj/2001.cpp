#include <cstdio>
#include <algorithm>
const int MaxN(20007), MaxM(50007), MaxL(16), inf(0x7fffffff), MaxQ(MaxM);
struct edge {
	int u, v, w, id;
	edge() {}
	edge(int u, int v, int w, int id) :
		u(u), v(v), w(w), id(id) {}
} e[MaxL][MaxM], d[MaxM], t[MaxM];
bool operator < (const edge &a, const edge &b) {
	return a.w < b.w;
}
struct ask {
	int k, d;
} quer[MaxQ];
int f[MaxN], size[MaxN], weight[MaxM], idx[MaxM];
long long ans[MaxQ];
inline int gf(int u) {
	while (f[u] ^ u) u = f[u] = f[f[u]];
	return u;
	//return u == f[u] ? u : f[u] = gf(f[u]);
}
inline void merge(int u, int v) {
	u = gf(u), v = gf(v);
	if (size[u] < size[v]) std::swap(u, v);
	f[v] = u, size[u] += size[v];
}
inline void reset(const int &n, const edge *e) {
	for (register int i = 0; i < n; ++i) {
		f[e[i].u] = e[i].u;
		f[e[i].v] = e[i].v;
		size[e[i].u] = size[e[i].v] = 1;
	}
}
inline long long contraction(int &n) { /// delete the necessary edges
	static int tmp;
	static long long ret;
	tmp = 0;
	std::sort(d, d + n);
	for (register int i = 0; i < n; ++i)
		if (gf(d[i].u) != gf(d[i].v)) {
			merge(d[i].u, d[i].v);
			t[tmp++] = d[i];
		}
	reset(tmp, t);
	ret = 0LL;
	for (register int i = 0; i < tmp; ++i)
		if (t[i].w != -inf && gf(t[i].u) != gf(t[i].v)) {
			merge(t[i].u, t[i].v);
			ret += t[i].w;
		}
	tmp = 0;
	for (register int i = 0; i < n; ++i)
		if (gf(d[i].u) != gf(d[i].v)) {
			t[tmp] = edge(gf(d[i].u), gf(d[i].v), d[i].w, d[i].id);
			idx[d[i].id] = tmp++;
		}
	reset(n, d);
	n = tmp;
	for (register int i = 0; i < n; ++i)
		d[i] = t[i];
	return ret;
}
inline void redoction(int &n) { /// delete the unnecessary edges
	static int tmp;
	tmp = 0;
	std::sort(d, d + n);
	for (register int i = 0; i < n; ++i)
		if (gf(d[i].u) != gf(d[i].v)) {
			merge(d[i].u, d[i].v);
			t[tmp] = d[i];
			idx[d[i].id] = tmp++;
		} else if (d[i].w == inf) {
			t[tmp] = d[i];
			idx[d[i].id] = tmp++;
		}
	reset(n, d);
	n = tmp;
	for (register int i = 0; i < n; ++i)
		d[i] = t[i];
}
inline void divide(int step, int n, int l, int r, long long v) {
	if (l == r) weight[quer[l].k] = quer[l].d;
	for (register int i = 0; i < n; ++i) {
		e[step][i].w = weight[e[step][i].id];
		d[i] = e[step][i];
		idx[d[i].id] = i;
	}
	if (l == r) {
		long long &x = ans[l] = v;
		std::sort(d, d + n);
		for (register int i = 0; i < n; ++i)
			if (gf(d[i].u) != gf(d[i].v)) {
				merge(d[i].u, d[i].v);
				x += d[i].w;
			}
		return reset(n, d);
	}
	for (register int i = l; i <= r; ++i)
		d[idx[quer[i].k]].w = -inf;
	v += contraction(n);
	for (register int i = l; i <= r; ++i)
		d[idx[quer[i].k]].w = inf;
	redoction(n);
	/// smaller the graph
	for (register int i = 0; i < n; ++i)
		e[step + 1][i] = d[i];
	int mid = (l + r) >> 1;
	divide(step + 1, n, l, mid, v);
	divide(step + 1, n, mid + 1, r, v);
}
int main() {
	int n, m, q, u, v, w;
	scanf("%d%d%d", &n, &m, &q);
	for (register int i = 1; i <= n; ++i)
		f[i] = i, size[i] = 1;
	for (register int i = 0; i < m; ++i) {
		scanf("%d%d%d", &u, &v, &w);
		e[0][i] = edge(u, v, w, i);
		weight[i] = w;
	}
	for (register int i = 0; i < q; ++i) {
		scanf("%d%d", &quer[i].k, &quer[i].d);
		--quer[i].k;
	}
	divide(0, m, 0, q - 1, 0);
	for (register int i = 0; i < q; ++i)
		printf("%lld\n", ans[i]);
	return 0;
}
