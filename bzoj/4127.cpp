#include <cstdio>
#define N 100003
inline int imx(const int &a, const int &b) {
	if (a >= 0)
	  return b;
	if (b >= 0)
	  return a;
	return a < b ? b : a;
}
typedef int seg[N<<2|1];
typedef long long seg64[N<<2|1];
seg mx, c, len;
seg64 sum, delta;
#define ls u << 1
#define rs u << 1 | 1

inline void pu(const int &u) {
	mx[u] = imx(mx[ls], mx[rs]);
	c[u] = c[ls] + c[rs];
	sum[u] = sum[ls] + sum[rs];
}

inline void pd(const int &u) {
	if (!delta[u]) return;
	sum[ls] += (len[ls] - 2LL * c[ls]) * delta[u];
	sum[rs] += (len[rs] - 2LL * c[rs]) * delta[u];
	delta[ls] += delta[u];
	delta[rs] += delta[u];
	mx[ls] += delta[u];
	mx[rs] += delta[u];
	delta[u] = 0;
}

void upd(int u, int l, int r, const int &x, const int &y, const int &add) {
	if (x <= l && r <= y) {
		if (l >= r) {
			if (mx[u] + add < 0) {
				mx[u] += add;
				sum[u] = -mx[u];
				c[u] = 1;
			} else if (c[u]){
				sum[u] = mx[u] + add;
				mx[u] = 0;
				c[u] = 0;
			} else 
				sum[u] += add;
			return;
		} else if (!c[u] || mx[u] + add < 0) {
			pd(u);
			sum[u] += (len[u] - 2LL * c[u]) * add;
			delta[u] += add;
			mx[u] += add;
			//pu(u);
			return;
		}
	}
	int m = l + r >> 1;
	pd(u);
	if (x <= m) upd(ls, l, m, x, y, add);
	if (y >  m) upd(rs, m + 1, r, x, y, add);
	pu(u);
}

void quy(int u, int l, int r, const int &x, const int &y, long long &v) {
	if (x <= l && r <= y) return (void)(v += sum[u]);
	int m = l + r >> 1;
	pd(u);
	if (x <= m) quy(ls, l, m, x, y, v);
	if (y >  m) quy(rs, m + 1, r, x, y, v);
}

int dfn;
typedef int tree[N];
tree tp, fa, son, sz, dep, val, dq, in;
struct edge {int t; edge *n;} me[N<<1|1], *ce = me, *g[N];
#define adde(a, b) (*ce = (edge){b, g[a]}, g[a] = ce++)
#define FOR(a, b) for (edge *a = g[b]; a; a = a->n)
void d1(int u) {
	sz[u] = 1;
	FOR(it, u) if (!sz[it->t]) {
		fa[it->t] = u;
		dep[it->t] = dep[u] + 1;
		d1(it->t);
		sz[u] += sz[it->t];
		if (sz[it->t] > sz[son[u]]) son[u] = it->t;
	}
}
void d2(int u, int anc) {
	tp[u] = anc;
	dq[in[u] = ++dfn] = u;
	if (son[u]) d2(son[u], anc);
	FOR(it, u) if (!tp[it->t]) d2(it->t, it->t);
}

void build(int u, int l, int r) {
	if (l ^ r) {
		int m = l + r >> 1;
		build(ls, l, m);
		build(rs, m + 1, r);
		pu(u);
		len[u] = r - l + 1;
	} else {
		mx[u] = val[dq[l]];
		len[u] = 1;
		if (mx[u] < 0) {
			c[u] = 1;
			sum[u] = -mx[u];
		} else {
			c[u] = 0;
			sum[u] = mx[u];
			mx[u] = 0;
		}
	}
}

void modify(int u, int v, const int &d) {
	while (tp[u] ^ tp[v]) {
		if (dep[tp[u]] < dep[tp[v]])
		  u ^= v ^= u ^= v;
		upd(1, 1, dfn, in[tp[u]], in[u], d);
		u = fa[tp[u]];
	}
	if (dep[u] < dep[v])
	  u ^= v ^= u ^= v;
	upd(1, 1, dfn, in[v], in[u], d);
}
long long ask(int u, int v) {
	static long long ret;
	for (ret = 0; tp[u] ^ tp[v]; ) {
		if (dep[tp[u]] < dep[tp[v]])
		  u ^= v ^= u ^= v;
		quy(1, 1, dfn, in[tp[u]], in[u], ret);
		u = fa[tp[u]];
	}
	if (dep[u] < dep[v])
	  u ^= v ^= u ^= v;
	quy(1, 1, dfn, in[v], in[u], ret);
	return ret;
}


int main() {
	//freopen("abs.in", "r", stdin);
	int n, m, i, u, v, d;
	scanf("%d%d", &n, &m);
	for (i = 1; i <= n; ++i)
	  scanf("%d", val + i);
	for (i = 1; i < n; ++i) {
		scanf("%d%d", &u, &v);
		adde(u, v);
		adde(v, u);
	}
	d1(1); d2(1, 1);
	build(1, 1, dfn);
	while (m--) {
		scanf("%d%d%d", &i, &u, &v);
		if (i & 1) {
			scanf("%d", &d);
			modify(u, v, d);
		} else
		  printf("%lld\n", ask(u, v));
	}
	return 0;
}
