#include <cstdio>
#include <cstring>

const int maxn(1e5 + 7), INT_MAX(0x7fffffff);

struct edge {
	int to;
	edge *nxt;
} edge_mset[maxn], *g[maxn], *cedge;

inline void add_edge(int u, int v) {
	*cedge = (edge) {v, g[u]};
	g[u] = cedge++;
}

int col[maxn], dep[maxn], n, m;

struct seg {
	int val;
	seg *ls, *rs;
} node_mset[maxn * 100], *cnode, *nil1, *nil2, *rt1[maxn], *rt2[maxn];

void modify(seg *x, seg * &y, int l, int r, const int &pos, const int &val) {
	*(y = cnode++) = *x;
	y->val = val;
	if (l == r) return;
	int mid = (l + r) >> 1;
	if (pos <= mid)
		modify(x->ls, y->ls, l, mid, pos, val);
	else
		modify(x->rs, y->rs, mid + 1, r, pos, val);
}


void _modify(seg *x, seg * &y, int l, int r, const int &pos, const int &val) {
	*(y = cnode++) = *x;
	y->val += val;
	if (l == r) return;
	int mid = (l + r) >> 1;
	if (pos <= mid)
		_modify(x->ls, y->ls, l, mid, pos, val);
	else
		_modify(x->rs, y->rs, mid + 1, r, pos, val);
}

seg *merge1(seg *x, seg *y, int l, int r) {
	if (x == nil1) return y;
	if (y == nil1) return x;
	seg *n = cnode++;
	int mid = (l + r) >> 1;
	n->val = x->val + y->val;
	n->ls = merge1(x->ls, y->ls, l, mid);
	n->rs = merge1(x->rs, y->rs, mid + 1, r);
	return n;
}

inline int max(const int &a, const int &b) {
	return a < b ? b : a;
}

inline int min(const int &a, const int &b) {
	return a < b ? a : b;
}

seg *merge2(seg *x, seg *y, int l, int r, seg * &z) {
	if (x == nil2) return y;
	if (y == nil2) return x;
	seg *n = cnode++;
	if (l == r) {
		n->val = min(x->val, y->val);
		if (max(x->val, y->val) != INT_MAX)
			_modify(z, z, 1, ::n, max(x->val, y->val), -1);
	}
	int mid = (l + r) >> 1;
	n->ls = merge2(x->ls, y->ls, l, mid, z);
	n->rs = merge2(x->rs, y->rs, mid + 1, r, z);
	return n;
}

void dfs(int u) {
	modify(nil1, rt1[u], 1, n, dep[u], 1);
	modify(nil2, rt2[u], 1, n, col[u], dep[u]);

	for (edge *it = g[u]; it; it = it->nxt) {
		dfs(it->to);

		rt1[u] = merge1(rt1[u], rt1[it->to], 1, n);
		rt2[u] = merge2(rt2[u], rt2[it->to], 1, n, rt1[u]);
	}

}

int query(seg*u, int l, int r, const int &x, const int &y) {
	if (x <= l && r <= y)
		return u->val;
	int mid = (l + r) >> 1, ret = 0;
	if (x <= mid) ret += query(u->ls, l, mid, x, y);
	if (y >  mid) ret += query(u->rs, mid + 1, r, x, y);
	return ret;
}

int main() {
	//freopen("tree.in", "r", stdin);
	int o_o, u, lastans, x, d;
	scanf("%d", &o_o);
	while (o_o--) {
		scanf("%d%d", &n, &m);
		for (register int i = 1; i <= n; ++i) {
			scanf("%d", col + i);
			g[i] = NULL;
		}

		cedge = edge_mset;
		dep[1] = 1;
		for (register int i = 2; i <= n; ++i) {
			scanf("%d", &u);
			add_edge(u, i);
			dep[i] = dep[u] + 1;
		}

		cnode = node_mset;
		nil1 = cnode++;
		nil2 = cnode++;

		*nil1 = (seg) {0, nil1, nil1};
		*nil2 = (seg) {INT_MAX, nil2, nil2};

		dfs(1);

		lastans = 0;

		while (m--) {
			scanf("%d%d", &x, &d);
			x ^= lastans, d ^= lastans;
			lastans = query(rt1[x], 1, n, dep[x], dep[x] + d);
			printf("%d\n", lastans);
		}

	}
	return 0;
}
