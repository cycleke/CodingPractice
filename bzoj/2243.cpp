#include <cstdio>
#include <cstring>

#define N 100005
struct edge {
	int t;
	edge *n;
	edge(int t = 0, edge *n = NULL) :
		t(t), n(n) {}
} me[N << 1], *g[N], *ce = me;
#define FOR(u) for (edge *it = g[u]; it; it = it->n)
#define adde(a, b) (*ce = edge(b, g[a]), g[a] = ce++)

typedef int arr[N];
arr tp, fa, son, sz, dep, in, color, _color;
int dfn;
void d1(int u) {
	sz[u] = 1;
	FOR(u) if (it->t ^ fa[u]) {
		fa[it->t] = u;
		dep[it->t] = dep[u] + 1;
		d1(it->t);
		if (sz[son[u]] < sz[it->t])
			son[u] = it->t;
		sz[u] += sz[it->t];
	}
}
void d2(int u, int anc) {
	tp[u] = anc;
	in[u] = ++dfn;
	if (son[u]) d2(son[u], anc);
	FOR(u) if (!tp[it->t])
		d2(it->t, it->t);
}

struct node {
	int l, r, lc, rc, sum, lyc;
	node(int l = 0, int r = 0, int lc = 0, int rc = 0, int sum = 0, int lyc = -1):
		l(l), r(r), lc(lc), rc(rc), sum(sum), lyc(lyc) {}
	bool inrange(const int &x, const int &y) const {
		return x <= l && r <= y;
	}
}C[N << 2];
#define ls u << 1
#define rs u << 1 | 1

inline void pu(int u) {
	C[u].sum = C[ls].sum + C[rs].sum - (C[ls].rc == C[rs].lc);
	C[u].lc = C[ls].lc, C[u].rc = C[rs].rc;
}

inline void pd(int u) {
	if (~C[u].lyc) {
		int &c = C[u].lyc;
		C[ls].lc = C[ls].rc = C[ls].lyc = c;
		C[rs].lc = C[rs].rc = C[rs].lyc = c;
		C[ls].sum = C[rs].sum = 1;
		c = -1;
	}
}

void build(int u, int l, int r) {
	if (l ^ r) {
		C[u] = node(l, r);
		int mid = (l + r) >> 1;
		build(ls, l, mid);
		build(rs, mid + 1, r);
		pu(u);
	} else
		C[u] = node(l, r, _color[l], _color[l], 1);
}

void upd(int u, const int &x, const int &y, const int &c) {
	if (C[u].inrange(x, y)) {
		C[u].lc = C[u].rc = C[u].lyc = c;
		C[u].sum = 1;
		return;
	}
	int mid = (C[u].l + C[u].r) >> 1;
	pd(u);
	if (x <= mid) upd(ls, x, y, c);
	if (y >  mid) upd(rs, x, y, c);
	pu(u);
}
int query(int u, const int &x, const int &y, int &lc, int &rc) {
	if (C[u].inrange(x, y) || (~C[u].lyc)) {
		lc = C[u].lc;
		rc = C[u].rc;
		return C[u].sum;
	}
	int mid = (C[u].l + C[u].r) >> 1;
	pd(u);
	if (y <= mid) return query(ls, x, y, lc, rc);
	if (x >  mid) return query(rs, x, y, lc, rc);
	int lrc, rlc, sum;
	sum = query(ls, x, y, lc, lrc) + query(rs, x, y, rlc, rc);
	return sum - (lrc == rlc);
}

void modify(int u, int v, const int &c) {
	while (tp[u] ^ tp[v]) {
		if (dep[tp[u]] < dep[tp[v]])
			u ^= v ^= u ^= v;
		upd(1, in[tp[u]], in[u], c);
		u = fa[tp[u]];
	}
	if (dep[u] < dep[v])
		u ^= v ^= u ^= v;
	upd(1, in[v], in[u], c);
}
#define swp(a, b) a ^= b ^= a ^= b
int ask(int u, int v) {
	int sum = 0, ulc = -1, urc = -2, vlc = -3, vrc = -4, lc, rc;
	//query(1, in[v], in[v], vlc, vrc);
	//query(1, in[u], in[u], ulc, urc);
	
	while (tp[u] ^ tp[v]) 
		if (dep[tp[u]] < dep[tp[v]]) {
			sum = sum + query(1, in[tp[v]], in[v], lc, rc);
			if (vlc == rc) --sum;
			vlc = lc;
			v = fa[tp[v]];
		} else {
			sum += query(1, in[tp[u]], in[u], lc, rc);
			if (ulc == rc) --sum;
			ulc = lc;
			u = fa[tp[u]];
		}
	if (dep[u] < dep[v]) {
		swp(u, v);
		swp(ulc, vlc);
		swp(urc, vrc);
	}
	sum += query(1, in[v], in[u], lc, rc);
	if (rc == ulc) --sum;
	if (lc == vlc) --sum;
	return sum;
}

int main() {
	//freopen("t.in", "r", stdin);
	int n, m;
	char ops[3];
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i)
		scanf("%d", color + i);
	for (int i = 1, u, v; i < n; ++i) {
		scanf("%d%d", &u, &v);
		adde(u, v);
		adde(v, u);
	}
	d1(1);
	d2(1, 1);
	for (int i = 1; i <= n; ++i)
		_color[in[i]] = color[i];
	build(1, 1, n);
	for (int u, v, c; m; --m) {
		scanf("%s%d%d", ops, &u, &v);
		if (*ops == 'C') {
			scanf("%d", &c);
			modify(u, v, c);
		} else
			printf("%d\n", ask(u, v));
	}
	return 0;
}















