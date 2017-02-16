#include <bits/stdc++.h>

#define MaxL 17
#define MaxN 100005
#define MaxS 6000005
#define inf 0x7fffffff
#define alpha 0.9
#define BUFSIZE 1<<17
typedef int arrN[MaxN];

char buffer[BUFSIZE], *s, *e, c;
char nextchar() {
	if (s == e)
		e = (s = buffer) + fread(buffer, 1, BUFSIZE, stdin);
	return (s >= e) ? EOF : *(s++);
}
void getusint(int &a) {
	while (c = nextchar(), c < '0');
	a = c - '0';
	while (c = nextchar(), '-' < c)
		a = (a << 3) + (a << 1) + c - '0';
}

struct Graph {
	struct edge {
		int t, w;
		edge *n;
	} me[MaxN << 1], *g[MaxN], *ce;
	arrN fa[MaxL], dis, dep;
	Graph() {
		ce = me;
	}
	void adde(int u, int v, int w) {
		*ce = (edge) {v, w, g[u]};
		g[u] = ce++;
	}
	void add_child(int u, int f, int w) {
		adde(u, f, w);
		adde(f, u, w);
		fa[0][u] = f;
		dis[u] = dis[f] + w;
		dep[u] = dep[f] + 1;
		for (int i = 1; i < MaxL; ++i)
			if (!(fa[i][u] = fa[i - 1][fa[i - 1][u]])) break;
	}
	int lca(int u, int v) {
		if (dep[u] < dep[v])
			std::swap(u, v);
		int delta = dep[u] - dep[v];
		for (int i = 0; delta; ++i, delta >>= 1)
			if (delta & 1) u = fa[i][u];
		if (u == v)
			return u;
		for (int i = MaxL - 1; ~i; --i)
			if(fa[i][u] ^ fa[i][v]) {
				u = fa[i][u];
				v = fa[i][v];
			}
		return fa[0][u];
	}
	int disc(int u, int v) {
		return dis[u] + dis[v] - (dis[lca(u, v)] << 1);
	}
} G;

struct AVL_node {
	int val, size;
	AVL_node *l, *r;
} AVL_mset[MaxS], *AVL_stk[MaxS], *AVL_it, **AVL_top, *AVL_nil;

AVL_node *new_AVL_node() {
	if (AVL_stk < AVL_top) {
		static AVL_node *n;
		n = *--AVL_top;
		if (n->l != AVL_nil)
			*AVL_top++ = n->l;
		if (n->r != AVL_nil)
			*AVL_top++ = n->r;
		return n;
	} else
		return AVL_it++;
}

void AVL_insert(AVL_node * (&n), const int &v) {
	if (n == AVL_nil) {
		n = new_AVL_node();
		*n = (AVL_node) {v, 1, AVL_nil, AVL_nil};
	} else {
		++n->size;
		if (v < n->val) {
			AVL_insert(n->l, v);
			if (n->l->size > n->r->size + 3) {
				AVL_node *q = n->l;
				n->l = q->r;
				q->r = n;
				q->size = n->size;
				n->size = n->l->size + n->r->size + 1;
				n = q;
			}
		} else {
			AVL_insert(n->r, v);
			if (n->l->size + 3 < n->r->size) {
				AVL_node *q = n->r;
				n->r = q->l;
				q->l = n;
				q->size = n->size;
				n->size = n->l->size + n->r->size + 1;
				n = q;
			}
		}
	}
}

int AVL_rank(AVL_node *u, const int &v) {
	static int ans;
	for (ans = 0; u != AVL_nil;)
		if (v < u->val)
			u = u->l;
		else {
			ans += u->l->size + 1;
			u = u->r;
		}
	return ans;
}

struct scape_node {
	int size, top;
	scape_node *fa;
	AVL_node *info, *parentinfo;
} scape_mset[MaxN], *scape_nil;
arrN R, dep, mark, que, fa, size, max_size, dis, recored;
int _mark, recored_num;
long long lastans;

int *bfs(int u) {
	int *l = que, *r = que, v;
	fa[u] = 0;
	*r++ = u;
	while (l < r) {
		u = *l++;
		size[u] = max_size[u] = 0;
		for (Graph::edge *it = G.g[u]; it; it = it->n) 
			if (mark[v = it->t] == _mark && (v ^ fa[u])) {
				fa[v] = u;
				*r++ = v;
			}
	}
	return r;
}

scape_node *divide(int r, scape_node *f, int _dep) {
	int *end = bfs(r), *i, u, v, root, root_size = inf;
	for (i = end; que < i;) {
		u = *--i;
		++size[u];
		size[fa[u]] += size[u];
		if (max_size[fa[u]] < size[u])
			max_size[fa[u]] = size[u];
	}
	for (i = que; i < end; ++i) {
		u = *i;
		if (max_size[u] < size[r] - size[u])
			max_size[u] = size[r] - size[u];
		if (max_size[u] < root_size)
			root_size = max_size[root =u];
	}
	dis[r] = 0;
	for (i = que; i < end; ++i) {
		u = *i;
		for (Graph::edge *it = G.g[u]; it; it = it->n)
			if (mark[v = it->t] == _mark && (fa[u] ^ v))
				dis[v] = dis[u] + it->w;
	}
	end = bfs(root);
	mark[root] = 0;
	dep[root] = _dep;
	scape_node *n = scape_mset + root;
	n->fa = f, n->top = r, n->size = end - que;
	for (i = que; i < end; ++i)
		AVL_insert(n->parentinfo, dis[*i] - R[*i]);
	AVL_insert(n->info, -R[root]);
	for (Graph::edge *it = G.g[root]; it; it = it->n)
		if (mark[v = it->t] == _mark) {
			scape_node *son = divide(v, n, _dep + 1);
			AVL_node *z;
			int *l = que, *r = que;
			*r++ = son->parentinfo - AVL_mset;
			while (l < r) {
				z = AVL_mset + *l++;
				AVL_insert(n->info, z->val + it->w);
				if (z->l != AVL_nil)
					*r++ = z->l - AVL_mset;
				if (z->r != AVL_nil)
					*r++ = z->r - AVL_mset;
			}
		}

	return n;
}

void scape_rebuild(scape_node *n) {
	int *l = que, *r = que, id = n - scape_mset, u, v, d;
	*r++ = id;
	mark[id] = ++_mark;
	while (l < r) {
		u = *l++;
		*AVL_top++ = scape_mset[u].info;
		*AVL_top++ = scape_mset[u].parentinfo;
		scape_mset[u].info = AVL_nil;
		scape_mset[u].parentinfo = AVL_nil;
		for (Graph::edge *it = G.g[u]; it; it = it->n)
			if ((mark[v = it->t] ^ _mark) && dep[id] < dep[v])
				mark[*r++ = v] = _mark;
	}
	d = dep[n - scape_mset];
	divide(n->top, n->fa, d);
}

void scape_insert(int n, int fa, int dist, int r) {
	R[n] = r;
	G.add_child(n, fa, dist);

	dep[n] = dep[fa] + 1;

	scape_node *z = scape_mset + n;
	*z = *scape_nil;
	z->size = 1;
	z->top = n;
	z->fa = scape_mset + fa;
	AVL_insert(z->info, -r);
	AVL_insert(z->parentinfo, -r);

	scape_node *unbalance;
	double unbalance_alpha = 0.0;
	for (scape_node *pre = z, *now = z->fa; now != scape_nil; pre = now, now = now->fa) {
		++now->size;
		if ((double)pre->size / now->size > unbalance_alpha) {
			unbalance = now;
			unbalance_alpha = (double)pre->size / now->size;
		}

		int id = now - scape_mset;
		int d = G.disc(id, n);
		AVL_insert(now->info, d - r);
		
		int _d = G.disc(now->top, n);
		AVL_insert(now->parentinfo, _d - r);
		lastans += AVL_rank(now->info, r - d);

		_d = G.disc(pre->top, id);
		lastans -= AVL_rank(pre->parentinfo, r - d - _d);
	}

	if (unbalance_alpha > alpha)
		scape_rebuild(unbalance);
}

void Init() {
	AVL_it = AVL_mset;
	AVL_top = AVL_stk;
	AVL_nil = new_AVL_node();
	*AVL_nil = (AVL_node){0, 0, AVL_nil, AVL_nil};

	scape_nil = scape_mset;
	*scape_nil = (scape_node) {0, 0, scape_nil, AVL_nil, AVL_nil};
}

int main() {

#ifndef ONLINE_JUDGE
	freopen("ex_flower.in", "r", stdin);
	freopen("ex_flower.out", "w", stdout);
#endif

	int n, i, a, b, r;
	getusint(n);
	getusint(n);
	Init();
	for (i = 1; i <= n; ++i) {
		getusint(a);
		getusint(b);
		getusint(r);
		a ^= lastans % 1000000000;
		scape_insert(i, a, b, r);
		printf("%lld\n", lastans);
		//printf("%d\n", i);
	}

#ifndef ONLINE_JUDGE
	fprintf(stderr, "Time = %.3lf\n", (double)clock() / CLOCKS_PER_SEC);
#endif

	return 0;
}
