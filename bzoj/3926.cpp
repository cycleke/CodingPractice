#include <cstdio>
#include <cstring>

const int MaxN = 1e5 + 13;

struct node {
	int step;
	node *pre, *ch[10];
}node_mset[MaxN * 40], *cnode = node_mset, *root;

inline node *newnode(const int &step) {
	cnode->step = step;
	return cnode++;
}

inline node *Insert(const int &c, node *last) {
	node *p = last, *np = newnode(p->step + 1);
	for (; p && !p->ch[c]; p = p->pre)
		p->ch[c] = np;
	if (!p)
		np->pre = root;
	else {
		node *q = p->ch[c];
		if (q->step == p->step + 1)
			np->pre = q;
		else {
			node *nq = newnode(p->step + 1);
			memcpy(nq->ch, q->ch, sizeof q->ch);
			nq->pre = q->pre;
			q->pre = np->pre = nq;
			for (; p && p->ch[c] == q; p = p->pre)
				p->ch[c] = nq;
		}
	}
	return np;
}

struct edge {
	int to;
	edge *nxt;
} edge_mset[MaxN << 1], *g[MaxN], *cedge = edge_mset;

inline void add_edge(int u, int v) {
	*cedge = (edge) {v, g[u]};
	g[u] = cedge++;
}

int col[MaxN];

void dfs(int u, int fa, node *last) {
	last = Insert(col[u], last);
	for (edge *it = g[u]; it; it = it->nxt)
		if (it->to ^ fa) dfs(it->to, u, last);
}

int main() {
	int n, c;
	scanf("%d%d", &n, &c);
	for (int i = 0; i < n; ++i) scanf("%d", col + i);
	for (int i = 1, u, v; i < n; ++i) {
		scanf("%d%d", &u, &v);
		--u, --v;
		add_edge(u, v);
		add_edge(v, u);
	}
	root = newnode(0);
	for (int i = 0; i < n; ++i)
		if (!g[i]->nxt) dfs(i, -1, root);
	long long ans = 0;
	for (node *i = node_mset; i < cnode; ++i)
		ans += i->step - (i->pre ? i->pre->step : 0);
	printf("%lld\n", ans);
	return 0;
}
