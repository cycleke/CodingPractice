#include <cstdio>
#include <cstring>
#include <algorithm>
#define N 100003
#define MS 2000003
#define wlp while
#define rep(i, l, r) for (register int i = l; i <= r; ++i)
template<class integer>
inline void gi(integer &a) {
	static char c;
	wlp (c = getchar(), c < '0'); a = c - '0';
	wlp (c = getchar(), '-' < c) a = (a << 3) + (a << 1) + c - '0';
}
int n, m, dfn, in[N], ou[N], dq[N];

struct segnode {
	int sum;
	segnode *ls, *rs;
} segnodeset[MS], *csegnode = segnodeset, *rt[N];
void ins(segnode *x, segnode *(&y), int l, int r, const int &p) {
	*(y = ++csegnode) = *x;
	++y->sum;
	if (l ^ r) {
		int mid = l + r >> 1;
		if (p <= mid) 
		  ins(x->ls, y->ls, l, mid, p);
		else
		  ins(x->rs, y->rs, mid + 1, r, p);
	}
}
inline int quy(const int &u, int k) {
	static int l, r, mid, tmp;
	static segnode *x, *y;
	x = rt[in[u] - 1], y = rt[ou[u]];
	for (l = 1, r = n; l ^ r;) {
		mid = l + r >> 1;
		tmp = y->ls->sum - x->ls->sum;
		if (k <= tmp) {
			r = mid;
			x = x->ls;
			y = y->ls;
		} else {
			l = mid + 1;
			k -= tmp;
			x = x->rs;
			y = y->rs;
		}
	}
	return l;
}

struct node {
	int rt, fa;
	long long l, r;
}a[N];

inline int binsea(const long long &x, const int &R) {
	static int l, r, mid;
	for (l = 1, r = R + 1; l + 1 < r;)
	  if (a[mid = l + r >> 1].l <= x)
		l = mid;
	  else 
		r = mid;
	return l;
}

struct Graph {
	struct edge {int t, v; edge *n;} me[N<<1|1], *ce, *g[N];
	int sz[N], fa[N], son[N], tp[N];
	long long d[N];
	Graph() {
		ce = me;
	}
	inline void adde(const int &a, const int &b, const int &c) {
		*ce = (edge) {b, c, g[a]}; g[a] = ce++;
	}
	void d1(int u) {
		sz[u] = 1;
		for (edge *it = g[u]; it; it = it->n)
		  if (it->t ^ fa[u]) {
			  d[it->t] = d[u] + it->v;
			  fa[it->t] = u;
			  d1(it->t);
			  if (sz[son[u]] < sz[it->t])
				son[u] = it->t;
			  sz[u] += sz[it->t];
		  }
	}
	void d2(int u, int anc) {
		dq[in[u] = ++dfn] = u;
		tp[u] = anc;
		if (son[u]) d2(son[u], anc);
		for (edge *it = g[u]; it; it = it->n)
		  if (!tp[it->t]) d2(it->t, it->t);
		ou[u] = dfn;
	}
	void d3(int u, int anc) {
		tp[u] = anc;
		if (son[u]) d3(son[u], anc);
		for (edge *it = g[u]; it; it = it->n)
		  if (!tp[it->t]) d3(it->t, it->t);
	}
	inline int lca(int u, int v) const {
		wlp (tp[u] ^ tp[v]) d[tp[u]] < d[tp[v]] ? v = fa[tp[v]] : u = fa[tp[u]];
		return d[u] < d[v] ? u : v;
	}
	inline int Gtp(int u, const int &upper) const {
		static int t;
		for (; tp[u] ^ tp[upper]; u = fa[tp[u]])
		  t = tp[u];
		return (u ^ upper) ? son[upper] : t;
	}
	inline void build_segment_tree() const {
		*csegnode = (segnode) {0, csegnode, csegnode};
		rt[0] = csegnode;
		rep(i, 1, n) ins(rt[i - 1], rt[i], 1, n, dq[i]);
	}
	inline long long dist(const int &u, const int &v) const {
		return d[u] + d[v] - (d[lca(u, v)] << 1);
	}
}G1, G2;

int main() {
	int _, c, u, v;
	long long x, y, ans;
	gi(n), gi(m), gi(_);
	rep(i, 2, n) {
		gi(u), gi(v);
		G1.adde(u, v, 1);
		G1.adde(v, u, 1);
	}
	G1.d1(1);
	G1.d2(1, 1);
	G1.build_segment_tree();
	a[1] = (node) {1, 0, 1LL, (long long)n};
	rep(i, 1, m) {
		gi(u), gi(y);
		a[i + 1] = (node) {u, 0, a[i].r + 1LL, a[i].r + G1.sz[u]};
		c = binsea(y, i);
		a[i + 1].fa = v = quy(a[c].rt, y - a[c].l + 1);
		G2.adde(c, i + 1, G1.d[v] - G1.d[a[c].rt] + 1);
	}
	G2.d1(1);
	G2.d3(1, 1);
	++m;
	wlp (_--) {
		gi(x), gi(y);
		u = binsea(x, m);
		v = binsea(y, m);
		c = G2.lca(u, v);
		x = quy(a[u].rt, x - a[u].l + 1);
		y = quy(a[v].rt, y - a[v].l + 1);
		if (u ^ v) {
			if (u == c) {
				std::swap(u, v);
				std::swap(x, y);
			}
			if (v == c) {
				v = G2.Gtp(u, c);
				ans = G1.d[x] - G1.d[a[u].rt] + G2.d[u] - G2.d[v];
				x = a[v].fa;
				ans += G1.dist((int)x, (int)y) + 1;
			} else {
				ans = G1.d[x] - G1.d[a[u].rt] + G1.d[y] - G1.d[a[v].rt] + G2.dist(u, v);
				u = G2.Gtp(u, c);
				v = G2.Gtp(v, c);
				ans -= (G1.d[G1.lca(a[u].fa, a[v].fa)] - G1.d[a[c].rt]) << 1;
			}
			printf("%lld\n", ans);
		} else printf("%lld\n", G1.dist((int)x, (int)y));
	}
	return 0;
}
