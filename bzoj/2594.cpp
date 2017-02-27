#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define GCSPEED
#ifdef GCSPEED
const int BUF = 1<<16|127;
inline char gc() {
	static char b[BUF], *s = b, *e = b;
	if (s == e) e = (s = b) + fread(b, 1, BUF, stdin);
	return (s == e) ? EOF : *s++;
}
#else
#define gc getchar
#endif
inline void gi(int &a) {
	static char c;
	while (c = gc(), c < '0'); a = c - '0';
	while (c = gc(), '-' < c) a = (a << 3) + (a << 1) + c - '0';
}

const int MaxN = 100003, MaxM = 1000003, MaxQ = 100003;

struct edge {
	bool deleted;
	int u, v, w;
	edge() {}
	edge(int u, int v) :
		deleted(false), u(u), v(v), w(0) {}
} e[MaxM];

bool operator < (const edge &a, const edge &b) {
	return (a.u ^ b.u) ? (a.u < b.u) : (a.v < b.v);
}
struct opt {
	int x, y, k, ans;
} p[MaxQ];

int f[MaxN];
inline int gf(int u) {
	static int r, t;
	for (r = u; f[r] ^ r; r = f[r]);
	while (u ^ r) t = f[u], f[u] = r, u = t;
	return r;
}

inline void uni(int u, int v) {
	f[gf(u)] = gf(v);
}

struct LCT {
	struct node {
		int val;
		bool rev;
		node *fa, *ch[2], *mx;
	} node_mset[MaxN + MaxM], *nil;
	void Init(const int &n) {
		nil = node_mset;
		*nil = (node){0, false, nil, {nil, nil}, nil};
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
		u->mx = u;
		if(u->ch[0]->mx->val > u->mx->val)
			u->mx = u->ch[0]->mx;
		if(u->ch[1]->mx->val > u->mx->val)
			u->mx = u->ch[1]->mx;
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
		v->mx = v;
	}
	inline void add_edge(int u, int v, int w) {
		node *_u = num(u), *_v = num(v), *_w = num(w);
		if (gf(u) == gf(v)) {
			mrt(_u);
			access(_v);
			splay(_v);
			if (_v->mx->val < _w->val) return;
			cut(_v->mx);
			maintain(_v);
		}
		uni(u, v);
		link(_u, _w);
		link(_v, _w);
	}
	inline int query(int u, int v) {
		node *_u = num(u), *_v = num(v);
		mrt(_u);
		access(_v), splay(_v);
		return _v->mx->val;
	}
} tree;

int main() {
#ifndef ONLINE_JUDGE
	freopen("tube_strong.in", "r", stdin);
	freopen("tube_strong.out", "w", stdout);
#endif
	int n, m, q;
	gi(n), gi(m), gi(q);
	for (int i = 0; i < m; ++i) {
		gi(e[i].u), gi(e[i].v), gi(e[i].w);
		if (e[i].u > e[i].v) swap(e[i].u, e[i].v);
	}
	sort(e, e + m);
	for (int i = 0; i < q; ++i) {
		gi(p[i].k), gi(p[i].x), gi(p[i].y);
		if (p[i].x > p[i].y) swap(p[i].x, p[i].y);
		if (p[i].k == 2)
			lower_bound(e, e + m, edge(p[i].x, p[i].y))->deleted = true;
	}
	tree.Init(n + m);
	for (int i = 1; i <= n; ++i) f[i] = i;
	for (int i = 0, idx = n + 1; i < m; ++i, ++idx)
		if (!e[i].deleted) {
			tree.num(idx)->val = e[i].w;
		    tree.add_edge(e[i].u, e[i].v, idx);
		}
	for (int i = q - 1; ~i; --i)
		if (p[i].k == 1) {
			p[i].ans = tree.query(p[i].x, p[i].y);
		} else {
			edge *it = lower_bound(e, e + m, edge(p[i].x, p[i].y));
			tree.num(it - e + n + 1)->val = it->w;
			tree.add_edge(it->u, it->v, it- e + n + 1);
		}
	for (int i = 0; i < q; ++i)
		if (p[i].k == 1) printf("%d\n", p[i].ans);
	return 0;
}
