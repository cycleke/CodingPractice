#pragma GCC optimize("O3")

#include <cstdio>
#include <cstring>

const int N = 300007, M = 600007;

struct edge;
struct node;
struct state;

struct edge {
	node *to;
	edge *next;
} edge_pool[M], *cedge(edge_pool);

struct node {
	bool vis;
	int l, r;
	edge *head;
	node *fa, *ch[26];
} node_pool[N], *last, *cnode(node_pool);

struct state {
	node *x, *y;
	int v;
} state_pool[N], *top(state_pool);

char s[N];
int c[26], rk[N], hi[N], sa[N], sacnt;

void insert(int c, int pos) {
	node *p = last, *np = cnode++;
	last = np;
	np->l = p->l + 1;
	np->r = pos;
	for (; p != NULL && p->ch[c] == NULL; p = p->fa)
		p->ch[c] = np;
	if (p == NULL)
		np->fa = node_pool;
	else {
		node *q = p->ch[c];
		if (p->l + 1 == q->l)
			np->fa = q;
		else {
			node *nq = cnode++;
			nq->l = p->l + 1;
			memcpy(nq->ch, q->ch, sizeof(q->ch));
			nq->fa = q->fa;
			np->fa = q->fa = nq;
			for (; p != NULL && p->ch[c] == q; p = p->fa)
				p->ch[c] = nq;
		}
	}
}

void dfs(node *u) {
	if (u->r != 0)
		sa[++sacnt] = u->r;
	for (edge *it = u->head; it != NULL; it = it->next)
		dfs(it->to);
}

int read_string() {
	int n = fread(s + 1, 1, N - 1, stdin);
	while (s[n] < 'a' || s[n] > 'z')
		--n;
	return n;
}

int main() {

	int n = read_string();

	last = cnode++;
	last->vis = true;
	for (int i = n; i > 0; --i)
		insert(s[i] - 'a', i);
	for (node *i = node_pool; i <= cnode; ++i)
		if (i->r != 0 && !i->vis) {
			int pos = n;
			node *j = i;
			while (j != NULL && !j->vis) {
				pos = pos - j->l + (j->fa != NULL ? j->fa->l : 0) + 1;
				*top++ = (state){j->fa, j, s[pos] - 'a'};
				j->vis = true;
				j = j->fa;
				--pos;
			}
		}

	for (state *i = state_pool; i < top; ++i)
		++c[i->v];
	for (int i = 0; i < 26; ++i)
		c[i] += c[i - 1];
	for (state *i = top - 1; i >= state_pool; --i)
		rk[c[i->v]--] = i - state_pool + 1;
	for (int i = top - state_pool; i; --i) {
		state x = state_pool[rk[i] - 1];
		*cedge = (edge) {x.y, x.x->head};
		x.x->head = cedge++;
	}
	dfs(node_pool);
	for (int i = 1; i <= n; ++i)
		printf("%d%c", sa[i], "\n "[i < n]);
	for (int i = 1; i <= n; ++i)
		rk[sa[i]] = i;
	for (int i = 1; i <= n; ++i) {
		int f = hi[rk[i - 1]] >= 1 ? (hi[rk[i - 1]] - 1) : 0;
		for (int j = sa[rk[i] - 1]; s[i + f] == s[j + f]; ++f);
		hi[rk[i]] = f;
	}
	for (int i = 2; i <= n; ++i)
		printf("%d ", hi[i]);

	return 0;
}
