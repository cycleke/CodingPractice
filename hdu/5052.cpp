#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define N 50003

struct edge {
	int t;
	edge *n;
	edge() {}
	edge(int t, edge *n) :
		t(t), n(n) {}
}me[N << 1], *ce, *g[N];
#define FOR(u) for (edge *it = g[u]; it; it = it->n)
#define adde(a, b) (*ce = edge(b, g[a]), g[a] = ce++)

typedef int arr[N];
arr fa, sz, tp, son, dep, in, a;
int dfn;
void d1(int u) {
	sz[u] = 1;
	son[u] = tp[u] = 0;
	FOR(u) if (it->t ^ fa[u]) {
		fa[it->t] = u;
		dep[it->t] = dep[u] + 1;
		d1(it->t);
		if (sz[son[u]] < sz[it->t])
			son[u] = it->t;
	}
}
void d2(int u, int anc) {
	in[u] = ++dfn;
	tp[u] = anc;
	if (son[u]) d2(son[u], anc);
	FOR(u) if (!tp[it->t]) d2(it->t, it->t);
}

#define ls u << 1
#define rs u << 1 | 1
struct node {
	int l, r, Min, Max, tag, delta1, delta2;
	node() {}
	node(int l, int r, int Min, int Max, int tag, int delta1, int delta2) :
		l(l), r(r), Min(Min), Max(Max), tag(tag), delta1(delta1), delta2(delta2) {}
}C[N << 2];

void pu(int u) {
	C[u].Min = min(C[ls].Min, C[rs].Min);
	C[u].Max = max(C[ls].Max, C[rs].Max);
	C[u].delta1 = max(C[rs].Max - C[ls].Min, max(C[ls].delta1, C[rs].delta1));
	C[u].delta2 = max(C[ls].Max - C[rs].Min, max(C[ls].delta2, C[rs].delta2));
}
void pd(int u) {
	if (C[u].tag) {
		int &t = C[u].tag;
		C[ls].Min += t;
		C[ls].Max += t;
		C[ls].tag += t;
		C[rs].Min += t;
		C[rs].Max += t;
		C[rs].tag += t;
		t = 0;
	}
}
void build(int u, int l, int r) {
	C[u] = node(l, r, 0, 0, 0, 0, 0);
	if (l ^ r) {
		int mid = (l + r) >> 1;
		build(ls, l, mid);
		build(rs, mid + 1, r);
	}
}
void update(int u, const int &x, const int &y, const int &v) {
	if (x <= C[u].l && C[u].r <= y) {
		C[u].tag += v;
		C[u].Min += v;
		C[u].Max += v;
		return;
	}
	int mid = (C[u].l + C[u].r) >> 1;
	pd(u);
	if (x <= mid) update(ls, x, y, v);
	if (y >  mid) update(rs, x, y, v);
	pu(u);
}
int query(int u, const int &x, const int &y, const int &type, int &Max, int &Min) {
	if (x <= C[u].l && C[u].r <= y) {
		Max = C[u].Max;
		Min = C[u].Min;
		return type == 1 ? C[u].delta1 : C[u].delta2;
	}
	int mid = (C[u].l + C[u].r) >> 1;
	pd(u);
	if (y <= mid)
		return query(ls, x, y, type, Max, Min);
	if (x > mid)
		return query(rs, x, y, type, Max, Min);
	int maxl, maxr, minl, minr, ans;
	ans = max(query(ls, x, y, type, maxl, minl), query(rs, x, y, type, maxr, minr));
	Max = max(maxl, maxr), Min = min(minl, minr);
	return type == 1 ? max(ans, maxr - minl) : max(ans, maxl - minr);
}
int ask(int u, int v) {
	int ans = 0, Max = -0x3f3f3f3f, Min = 0x3f3f3f3f, minl = 0x3f3f3f3f, maxr = -0x3f3f3f3f;
	while (tp[u] ^ tp[v])
		if (dep[tp[u]] > dep[tp[v]]) {
			ans = max(ans, query(1, in[tp[u]], in[u], 2, Max, Min));
			ans = max(ans, Max - minl);
			minl = min(minl, Min);
			u = fa[tp[u]];
		} else {
			ans = max(ans, query(1, in[tp[v]], in[v], 1, Max, Min));
			ans = max(ans, maxr - Min);
			maxr = max(maxr, Max);
			v = fa[tp[v]];
		}
	if (dep[u] > dep[v])
		ans = max(ans, query(1, in[v], in[u], 2, Max, Min));
	else
		ans = max(ans, query(1, in[u], in[v], 1, Max, Min));
	ans = max(max(ans, maxr - minl), max(maxr - Min, Max - minl));
	return ans;
}
void modify(int u, int v, const int &w) {
	while (tp[u] ^ tp[v]) {
		if (dep[tp[u]] < dep[tp[v]])
			u ^= v ^= u ^= v;
		update(1, in[tp[u]], in[u], w);
		u = fa[tp[u]];
	}
	if (dep[u] < dep[v])
		u ^= v ^= u ^= v;
	update(1, in[v], in[u], w);
}
int main() {
	int _, n, m;
	scanf("%d", &_);
	while (_--) {
		memset(g, 0, sizeof g);
		ce = me;
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i)
			scanf("%d", a + i);
		for (int i = 1, u, v; i < n; ++i) {
			scanf("%d%d", &u, &v);
			adde(u, v);
			adde(v, u);
		}
		dfn = 0;
		d1(1);
		d2(1, 1);
		build(1, 1, n);
		for (int i = 1; i <= n; ++i)
			update(1, in[i], in[i], a[i]);
		scanf("%d", &m);
	    for (int u, v, w; m; --m) {
			scanf("%d%d%d", &u, &v, &w);
			printf("%d\n", ask(u, v));
			modify(u, v, w);
		}
	}
}
