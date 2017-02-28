#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int BUF = 1<<16|127;
inline char gc() {
    static char b[BUF], *s = b, *e = b;
    if (s == e) e = (s = b) + fread(b, 1, BUF, stdin);
    return (s == e) ? EOF : *s++;
}
 
inline void gi(int &a) {
    static char c;
    while (c = gc(), c < '0'); a = c - '0';
    while (c = gc(), '-' < c) a = (a << 3) + (a << 1) + c - '0';
}

const int MaxN = 50005, MaxM = 100003;

struct edge {
	int u, v, a, b;
} e[MaxM];

bool operator < (const edge &a, const edge &b) {
	return a.a < b.a;
}

int f[MaxN];
int gf(int u) {
	return (f[u] ^ u) ? f[u] = gf(f[u]) : u;
}
struct LCT {
	struct node {
		int val;
		bool rev;
		node *fa, *ch[2], *mx;
	} node_mset[MaxN + MaxM], *nil;
	void Init(const int &n) {
		nil = node_mset;
		*nil = (node) {0, false, nil, {nil, nil}, nil};
		for (int i = 1; i <= n; ++i) node_mset[i] = *nil;
	}
	inline node *num(const int &x) {
		return node_mset + x;
	}
	inline bool isrt(node *u) {
		return (u->fa->ch[0] != u) && (u->fa->ch[1] != u);
	}
	inline bool which(node *u) {
		return u->fa->ch[1] == u;
	}
	void maintain(node *u) {
		u->mx = u;
		if (u->ch[0]->mx->val > u->mx->val)
			u->mx = u->ch[0]->mx;
		if (u->ch[1]->mx->val > u->mx->val)
			u->mx = u->ch[1]->mx;
	}
	void rot(node *u) {
		node *f = u->fa;
		int d = which(u);
		if ((f->ch[d] = u->ch[d ^ 1]) != nil)
			f->ch[d]->fa = f;
		u->ch[d ^ 1] = f;
		u->fa = f->fa;
		if (!isrt(f)) f->fa->ch[which(f)] = u;
		f->fa = u;
		maintain(f);
	}
	void pd(node *u) {
		if (!isrt(u)) pd(u->fa);
		if (u->rev) {
			u->ch[0]->rev ^= true;
			u->ch[1]->rev ^= true;
			swap(u->ch[0], u->ch[1]);
			u->rev = false;
		}
	}
	void splay(node *u) {
		pd(u);
		for (node *f; !isrt(u); rot(u))
			if (!isrt(f = u->fa)) rot(which(u) == which(f) ? f : u);
		maintain(u);
	}
	void access(node *x) {
		for (node *y = nil; x != nil; x = x->fa)
			splay(x), x->ch[1] = y, maintain(y = x);
	}
	void mrt(node *u) {
		access(u);
		splay(u);
		u->rev ^= 1;
	}
	void link(node *u, node *v) {
		mrt(u);
		u->fa = v;
		access(u);
	}
	void cut(node *u) {
		splay(u);
		u->ch[0]->fa = u->fa;
		u->ch[1]->fa = nil;
		u->fa = u->ch[0] = u->ch[1] = nil;
		u->mx = u;
	}
	void add_edge(int u, int v, int w) {
		node *_u = num(u), *_v = num(v), *_w = num(w);
		if (gf(u) == gf(v)) {
			mrt(_u);
			access(_v);
			splay(_v);
			if (_v->mx->val < _w->val)
				return;
			cut(_v->mx);
			maintain(_v);
		} else
			f[gf(u)] = gf(v);
		link(_u, _w);
		link(_v, _w);  
	}
	int query(int u, int v) {
		node *_u = num(u), *_v = num(v);
		mrt(_u);
		access(_v);
		splay(_v);
		return _v->mx->val;
	}
} tree;

int main() {
	//freopen("t.in", "r", stdin);
	int n, m, i, ans = 0x3f3f3f3f, idx;
	scanf("%d%d", &n, &m);
	for (i = 0; i < m; ++i) gi(e[i].u), gi(e[i].v), gi(e[i].a), gi(e[i].b);
	sort(e, e + m);
	tree.Init(n + m);
	for (idx = 1; idx <= n; ++idx) f[idx] = idx;
	for (i = 0; i < m; ++i, ++idx) {
		tree.num(idx)->val = e[i].b;
		tree.add_edge(e[i].u, e[i].v, idx);
		//printf("%d %d %d %d\n", e[i].u, e[i].v, e[i].a, e[i].b);
		if (gf(1) == gf(n)) {
			ans = min(ans, e[i].a + tree.query(1, n));
			//printf("%d %d\n", i, tree.query(1, n));
		}
	}
	printf("%d\n", ans < 0x3f3f3f3f ? ans : -1);
	return 0;
}
