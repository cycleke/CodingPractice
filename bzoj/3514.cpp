#include <cstdio>

const int Max = 200007, inf = 0x3f3f3f3f;

struct FastInput {
	char b[5<<21], *s;
	FastInput() : s(b) {
		b[fread(b, 1, 5 << 21, stdin)] = 0;
	}
	inline void gi(int &a) {
		while (*s < 48) ++s;
		a = *s++ - 48;
		while (47 < *s) a = (a << 3) + (a << 1) + *s++ - 48;
	}
} io;

struct LCT {
	struct node {
		int val;
		bool rev;
		node *fa, *ch[2], *mi;
	} node_mset[Max << 1], *nil;
	void Init(const int &n) {
		nil = node_mset;
		*nil = (node){inf, false, nil, {nil, nil}, nil};
		for (int i = 1; i <= n; ++i)
			node_mset[i] = *nil;
	}
	inline node* num(const int &x)  {
		return node_mset + x;
	}
	inline bool isrt(node *u) const {
		return (u->fa->ch[0] != u) && (u->fa->ch[1] != u);
	}
	inline bool which(node *u) const {
		return u->fa->ch[1] == u;
	}
	inline void maintain(node *u) {
		u->mi = u;
		if(u->ch[0]->mi->val < u->mi->val)
			u->mi = u->ch[0]->mi;
		if(u->ch[1]->mi->val < u->mi->val)
			u->mi = u->ch[1]->mi;
	}
	inline void rot(node *u) {
		node *f = u->fa;
		int d = which(u);
		if ((f->ch[d] = u->ch[d ^ 1]) != nil)
			f->ch[d]->fa = f;
		u->ch[d ^ 1] = f;
		u->fa = f->fa;
		if (!isrt(f))
			f->fa->ch[which(f)] = u;
		f->fa = u;
		maintain(f);
	}
	inline void swap(node * &x, node * &y) {
		static node *t;
		t = x, x = y, y = t;
	}
	inline void pd(node *u) {
		if (!isrt(u)) pd(u->fa);
		if (u->rev) {
			u->ch[0]->rev ^= true;
			u->ch[1]->rev ^= true;
			swap(u->ch[0], u->ch[1]);
			u->rev = false;
		}
	}
	inline void splay(node *u) {
		pd(u);
		for (node *f; !isrt(u); rot(u))
			if (!isrt(f = u->fa)) rot(which(f) == which(u) ? f : u);
		maintain(u);
	}
	inline void access(node *x) {
		for (node *y = nil; x != nil; x = x->fa)
			splay(x), x->ch[1] = y, maintain(y = x);
	}
	inline void mrt(node *u) {
		access(u);
		splay(u);
		u->rev ^= 1;
	}
	inline void link(node *u, node *v) {
		mrt(u);
		u->fa = v;
		access(u);
	}
	inline void cut(node *v) {
		splay(v);
		v->ch[0]->fa = v->fa;
		v->ch[1]->fa = nil;
		v->fa = v->ch[0] = v->ch[1] = nil;
		v->mi = v;
	}
	inline void add_edge(int u, int v, int w) {
		node *_u = num(u), *_v = num(v), *_w = num(w);
		link(_u, _w);
		link(_v, _w);
	}
	inline int query(int u, int v) {
		node *_u = num(u), *_v = num(v);
		mrt(_u);
		access(_v), splay(_v);
		return _v->mi->val;
	}
} tree;

struct SegMentTree {
	struct node {
		int sum;
		node *ls, *rs;
	} node_mset[Max * 20], *root[Max], *cnode;
	SegMentTree() : cnode(node_mset) {
		*root = node_mset;
		**root = (node) {0, *root, *root};
	}
	inline void insert(node *x, node * &y, int l, int r, const int &p) {
		*(y = ++cnode) = *x;
		++y->sum;
		if (l == r) return;
		int mid = (l + r) >> 1;
		if (p <= mid) insert(x->ls, y->ls, l, mid, p);
		else insert(x->rs, y->rs, mid + 1, r, p);
	}

	inline int query(node *x, node *y, int l, int r, const int &p) {
		if (r <= p)
			return y->sum - x->sum;
		int mid = (l + r) >> 1;
		if (p <= mid)
			return query(x->ls, y->ls, l, mid, p);
		else
			return query(x->rs, y->rs, mid + 1, r, p) + y->ls->sum - x->ls->sum;
	}

	inline void insert(int x, int n, int p) {
		insert(root[x - 1], root[x], 0, n, p);
	}

	inline int query(int l, int r, int n) {
		return query(root[l - 1], root[r], 0, n, l - 1);
	}
	
} seg;

int f[Max];

inline int gf(int u) {
	while (u ^ f[u]) u = f[u] = f[f[u]];
	return u;
}

int main() {
	
	int n, m, k, type, lastans = 0, x, y;
	
	io.gi(n), io.gi(m), io.gi(k), io.gi(type);

	tree.Init(n + m);

	for (register int i = 1; i <= n; ++i) f[i] = i;
	
	for (register int i = 1; i <= m; ++i) {
		io.gi(x), io.gi(y);
		if (x == y)
			seg.insert(i, m, i);
		else {
			if (gf(x) == gf(y)) {
				static int t;
				t = tree.query(x, y);
				tree.cut(tree.num(t + n));
				seg.insert(i, m, t);
			} else {
				seg.insert(i, m, 0);
				f[gf(x)] = gf(y);
			}
			tree.num(i + n)->val = i;
			tree.add_edge(x, y, i + n);
		}
	}

	while (k--) {
		io.gi(x), io.gi(y);
		if (type) x ^= lastans, y ^= lastans;
		lastans = n - seg.query(x, y, m);
		printf("%d\n", lastans);
	}
	
	return 0;
}
