#include <cstdio>
#define MaxN 100005
struct edge {
	int t;
	edge *n;
	edge(int t = 0, edge *n = NULL) : t(t), n(n) {}
} me[MaxN << 1], *ce, *g[MaxN];
#define FOR(u) for (edge *it = g[u]; it; it = it->n)
#define adde(a, b) (*ce = edge(b, g[a]), g[a] = ce++)
typedef int arr[MaxN];
arr fa, sz, son, tp, dep, in;
int dfn;
void d1(int u) {
	sz[u] = 1;
	son[u] = tp[u] = 0;
	FOR(u) if (it->t ^ fa[u]) {
		fa[it->t] = u;
		dep[it->t] = dep[u] + 1;
		d1(it->t);
		sz[u] += sz[it->t];
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
struct node {
	int sum, l, r, len;
	bool flip, light;
	node() {}
	node(int sum, int l, int r, int len, bool flip, bool light) :
		sum(sum), l(l), r(r), len(len),
		flip(flip), light(light) {}
}C[MaxN << 2];
#define ls u << 1
#define rs u << 1 | 1
void build(int u, int l, int r) {
	C[u] = node(0, l, r, r - l + 1, false, false);
	if (l ^ r) {
		int mid = (l + r) >> 1;
		build(ls, l, mid);
		build(rs, mid + 1, r);
	}
}
inline void pu(const int &u) {
	C[u].sum = C[ls].sum + C[rs].sum;
}
inline void pd(int u) {
	if (C[u].flip) {
		C[ls].flip ^= true;
		C[ls].sum = C[ls].len - C[ls].sum;
		C[rs].flip ^= true;
		C[rs].sum = C[rs].len - C[rs].sum;
		C[u].flip = false;
	}
	if (C[u].light) {
		C[ls].light ^= true;
		C[rs].light ^= true;
		C[u].light = false;
	}
}
void Flip(int u, const int &x, const int &y) {
	if (x <= C[u].l && C[u].r <= y) {
		C[u].flip ^= true;
		C[u].sum = C[u].len - C[u].sum;
	} else {
		int mid = (C[u].l + C[u].r) >> 1;
		pd(u);
		if (x <= mid) Flip(ls, x, y);
		if (y >  mid) Flip(rs, x, y);
		pu(u);
	}
}
void Light(int u, const int &x, const int &y) {
	if (x <= C[u].l && C[u].r <= y)
		C[u].light ^= true;
	else {
		int mid = (C[u].l + C[u].r) >> 1;
		pd(u);
		if (x <= mid) Light(ls, x, y);
		if (y >  mid) Light(rs, x, y);
	}
}
int askflip(int u, const int &x, const int &y) {
	if (x <= C[u].l && C[u].r <= y)
		return C[u].sum;
	int mid = (C[u].l + C[u].r) >> 1, ret = 0;
	pd(u);
	if (x <= mid) ret += askflip(ls, x, y);
	if (y >  mid) ret += askflip(rs, x, y);
	return ret;
}
bool asklight(int u, const int &pos) {
	if (C[u].l >= C[u].r)
		return C[u].light;
	int mid = (C[u].l + C[u].r) >> 1;
	pd(u);
	if (pos <= mid)
		return asklight(ls, pos);
	else
		return asklight(rs, pos);
}
#define swp(a, b) (a ^= b ^= a ^= b)
void Flip(int u, int v) {
	while (tp[u] ^ tp[v]) {
		if (dep[tp[u]] < dep[tp[v]])
			swp(u, v);
		Flip(1, in[tp[u]], in[u]);
		u = fa[tp[u]];
	}
	if (dep[u] < dep[v])
		swp(u, v);
	if (u ^ v)
		Flip(1, in[son[v]], in[u]);
}
void Light(int u, int v) {
	while (tp[u] ^ tp[v]) {
		if (dep[tp[u]] < dep[tp[v]])
			swp(u, v);
		Light(1, in[tp[u]], in[u]);
		if (son[u]) Flip(1, in[son[u]], in[son[u]]);
		Flip(1, in[tp[u]], in[tp[u]]);
		u = fa[tp[u]];
	}
	if (dep[u] < dep[v])
		swp(u, v);
	Light(1, in[v], in[u]);
	if (fa[v]) Flip(1, in[v], in[v]);
	if (son[u]) Flip(1, in[son[u]], in[son[u]]);
}
int ask(int u, int v) {
	static int r;
	for (r = 0; tp[u] ^ tp[v]; u = fa[tp[u]]) {
		if (dep[tp[u]] < dep[tp[v]])
			swp(u, v);
		if (u ^ tp[u])
			r += askflip(1, in[son[tp[u]]], in[u]);
		r += askflip(1, in[tp[u]], in[tp[u]]) ^ asklight(1, in[fa[tp[u]]]);
	}
	if (dep[u] < dep[v])
		swp(u, v);
	if (u ^ v)
		r += askflip(1, in[son[v]], in[u]);
	return r;
}
int main() {
	//freopen("t.in", "r", stdin);
	int _, n, q, i, u, v;
	scanf("%d", &_);
	while (_--) {
		ce = me;
		scanf("%d", &n);
		for (i = 1; i <= n; ++i) g[i] = NULL;
		for (i = 1; i <  n; ++i) {
			scanf("%d%d", &u, &v);
			adde(u, v);
			adde(v, u);
		}
		dfn = 0;
		d1(1);
		d2(1, 1);
		build(1, 1, n);
		scanf("%d", &q);
		while (q--) {
			scanf("%d%d%d", &i, &u, &v);
			if (i < 2) Flip(u, v);
			else if (i < 3) Light(u, v);
			else printf("%d\n", ask(u, v));
		}
	}
	return 0;
}
