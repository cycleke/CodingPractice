#include <cstdio>

const int maxn(5e4 + 7);

inline int min(const int &a, const int &b) {
	return a < b ? a : b;
}

inline int gi() {
	static int a;
	static char c;
	do c = getchar_unlocked(); while (c < 48);
	a = c - 48;
	while (47 < (c = getchar_unlocked()))
		a = (a << 3) + (a << 1) + c - 48;
	return a;
}

struct node {
	int val, s0, s1, dep, mindep;
	node *ch[2], *fa;
	inline void maintain() {
		s0 = ch[0]->s0 ^ ch[1]->s0;
		s1 = ch[0]->s1 ^ ch[1]->s1;
		if (dep & 1)
			s1 ^= val;
		else
			s0 ^= val;
		mindep = min(dep, ch[0]->mindep, ch[1]->mindep);
	}
	inline bool which() const {
		return this == fa->ch[1];
	}
} *f[maxn], *nil, *root;

inline node *newnode(int dep = 0, int val = 0) {
	static node node_mset[maxn], *cnode = node_mset;
	*cnode = (node) {val, 0, 0, dep, dep, {nil, nil}, nil};
	return cnode++;
}

inline void rot(node *u) {
	static int d;
	static node *f;
	f = u->fa;
	d = u->which();
	if ((f->ch[d] = u->ch[d ^ 1]) != nil)
		f->ch[d]->fa = f;
	if ((u->fa = f->fa) != nil)
		u->fa->ch[f->which()] = u;
	u->ch[d ^ 1] = f;
	f->fa = u;
	f->maintain();
}

inline void splay(node *u, node *tag) {
	for (static node *f; u->fa != tag; rot(u))
		if ((f = u->fa)->fa != tag) rot(u->which() == f->which() ? f : u);
	u->maintain();
}

inline node *find_node(node *x, int y) {
	while (true) {
		if (x->ch[0] != nil && x->ch[0]->mindep <= y)
			x = x->ch[0];
		else if (x->dep <= y)
			return x;
		else
			x = x->ch[1];
	}
}

struct edge {
	int to;
	edge *nxt;
} *g[maxn];

inline void add_edge(int u, int v) {
	static edge edge_mset[maxn * 2], *cedge = edge_mset;
	*cedge = (edge) {v, g[u]};
	g[u] = cedge++;
}

int dep[maxn], dq[maxn], dfn;

void dfs(int u) {
	
}
