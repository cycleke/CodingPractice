#include <cstdio>
#include <cstring>

const int MaxN = 50005, mod = 201314;

struct SegNode {
	int sum, lazy;
	SegNode *ls, *rs;
} SegNode_Mset[MaxN * 150], *root[MaxN], *cSegNode = SegNode_Mset;

inline void modify(SegNode *a, SegNode * &b, int l, int r, const int &x, const int &y) {
	*(b = ++cSegNode) = *a;
	if (x <= l && r <= y)
		return (void)(b->sum += r - l + 1, ++b->lazy);
	int mid = (l + r) >> 1;
	if (x <= mid) modify(a->ls, b->ls, l, mid, x, y);
	if (y >  mid) modify(a->rs, b->rs, mid + 1, r, x, y);
	b->sum = b->ls->sum + b->rs->sum + b->lazy * (r - l + 1);
}

inline int query(SegNode *a, SegNode *b, int l, int r, const int &x, const int &y) {
	static int _x = 0, _y = 0;
	if (x <= l && r <= y)
		return b->sum - a->sum + (_y - _x) * (r - l + 1);
	int ret = 0, mid = (l + r) >> 1;
	_x += a->lazy, _y += b->lazy;
	if (x <= mid) ret += query(a->ls, b->ls, l, mid, x, y);
	if (y >  mid) ret += query(a->rs, b->rs, mid + 1, r, x, y);
	_x -= a->lazy, _y -= b->lazy;
	return ret;
}

struct edge {
	int to;
	edge *nxt;
} edge_mset[MaxN], *cedge = edge_mset, *g[MaxN];

int in[MaxN], fa[MaxN], top[MaxN], dfn, son[MaxN], size[MaxN];

inline void d1(int u) {
	int v;
	size[u] = 1;
	for (edge *it = g[u]; it; it = it->nxt) {
		v = it->to;
		d1(v);
		if (size[v] > size[son[u]]) son[u] = v;
		size[u] += size[v];
	}
}

inline void d2(int u, int anc) {
	top[u] = anc;
	in[u] = ++dfn;
	if (son[u]) d2(son[u], anc);
	for (edge *it = g[u]; it; it = it->nxt)
		if (!in[it->to]) d2(it->to, it->to);
}

inline void update(int u) {
	int id = u;
	while (u) {
		modify(root[id], root[id], 1, dfn, in[top[u]], in[u]);
		u = fa[top[u]];
	}
}

inline int sum(int u, int l, int r) {
	static int ret;
	ret = 0;
	while (u) {
		//printf("%d\n", query(root[0], root[l - 1], 1, dfn, in[top[u]], in[u]));
		//printf("%d\n", query(root[0], root[r    ], 1, dfn, in[top[u]], in[u]));
		ret += query(root[l - 1], root[r], 1, dfn, in[top[u]], in[u]);
		ret %= mod;
		u = fa[top[u]];
	}
	return ret;
}

int main() {
	int n, q, x, l, r;
	scanf("%d%d", &n, &q);
	for (register int i = 2; i <= n; ++i) {
		scanf("%d", &x);
		fa[i] = ++x;
		*cedge = (edge) {i, g[x]};
		g[x] = cedge++;
	}
	d1(1);
	d2(1, 1);
	*cSegNode = (SegNode) {0, 0, cSegNode, cSegNode};
	root[0] = cSegNode;
	for (register int i = 1; i <= n; ++i) {
		root[i] = root[i - 1];
		update(i);
		//printf("%d\n", root[i]->sum);
	}
	while (q--) {
		scanf("%d%d%d", &l, &r, &x);
		printf("%d\n", sum(x + 1, l + 1, r + 1));
	}
	return 0;
}
