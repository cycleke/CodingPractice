#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MaxS = 600000 * 2 + 13;

struct LCT {
	struct node {
		int val, add;
		node *fa, *ch[2];
		void modify(const int &x) {
			val += x;
			add += x;
		}
	} node_mset[MaxS], *cnode, *null;
	LCT() {
		cnode = node_mset;
		null = cnode++;
		*null = (node){0, 0, null, {null, null}};
	}
	inline node *newnode() {
		*cnode = (node){0, 0, null, {null, null}};
		return cnode++;
	}
	inline bool isrt(node *u) const {
		return (u->fa->ch[0] != u) && (u->fa->ch[1] != u);
	}
	inline bool which(node *u) const {
		return u->fa->ch[1] == u;
	}
	void pd(node *u) {
		if (!isrt(u))
			pd(u->fa);
		if (u->add) {
			u->ch[0]->modify(u->add);
			u->ch[1]->modify(u->add);
			u->add = 0;
		}
	}
	inline void rot(node *u) {
		node *f = u->fa;
		int d = which(u);
		f->ch[d] = u->ch[d ^ 1];
		f->ch[d]->fa = f;
		u->ch[d ^ 1] = f;
		u->fa = f->fa;
		if (!isrt(f))
			f->fa->ch[which(f)] = u;
		f->fa = u;
	}
	inline void splay(node *u) {
		pd(u);
		for (node *f; !isrt(u); rot(u))
			if (!isrt(f = u->fa)) rot(which(u) == which(f) ? f : u);
	}
	inline void access(node *x) {
		for (node *y = null; x != null; x = x->fa) {
			splay(x);
			x->ch[1] = y;
			y = x;
		}
	}
	inline void cut(node *u) {
		access(u);
		splay(u);
		u->ch[0]->fa = null;
		u->ch[0] = null;
	}
	inline void link(node *u, node *v) {
		cut(u);
		u->fa = v;
	}
} tree;

struct SAM {
	struct node {
		int step;
		node *pre, *ch[26];
		LCT::node *idx;
		void clear() {
			pre = NULL;
			memset(ch, 0, sizeof ch);
		}
	} node_mset[MaxS], *cnode, *root, *last;
	SAM() {
		cnode = node_mset;
		cnode->clear();
		cnode->step = 0;
		cnode->idx = tree.newnode();
		root = last = cnode++;
	}
	inline node *newnode(const int &step) {
		cnode->clear();
		cnode->step = step;
		cnode->idx = tree.newnode();
		return cnode++;
	}
	inline void Insert(const int &c) {
		node *p = last, *np = newnode(p->step + 1);
		for (; p && !p->ch[c]; p = p->pre)
			p->ch[c] = np;
		if (!p) {
			np->pre = root;
			tree.link(np->idx, root->idx);
		} else {
			node *q = p->ch[c];
			if (q->step == p->step + 1) {
				np->pre = q;
				tree.link(np->idx, q->idx);
			} else {
				node *nq = newnode(p->step + 1);
				memcpy(nq->ch, q->ch, sizeof q->ch);
				nq->pre = q->pre;
				tree.link(nq->idx, q->pre->idx);
				q->pre = np->pre = nq;
				tree.link(q->idx, nq->idx);
				tree.link(np->idx, nq->idx);
				tree.pd(q->idx);
				nq->idx->val = q->idx->val;
				for (; p && p->ch[c] == q; p = p->pre)
					p->ch[c] = nq;
			}
		}
		last = np;
		tree.access(np->idx);
		tree.splay(np->idx);
		np->idx->modify(1);
	}
	inline void Insert(const char *s) {
		//puts(s);
		for (const char *i = s; *i; ++i)
			/*putchar(*i),*/ this->Insert(*i - 'A');
	}
	inline int Query(const char *s) {
		for (node *p = root; p; p = p->ch[*(s++) - 'A'])
			if (!*s) {
				tree.pd(p->idx);
				return p->idx->val;
			}
		return 0;
	}
} sam;

char s[3000005], ops[23];

inline void Decode(char *s, int mask) {
	static int n, i;
	n = strlen(s);
	for (i = 0; i < n; ++i) {
		mask = (mask * 131 + i) % n;
		swap(s[i], s[mask]);
	}
}

int main() {
	//freopen("2555.in", "r", stdin);
	int Q, mask = 0, ans;
	scanf("%d", &Q);
	scanf("%s", s);
	sam.Insert(s);
	while (Q--) {
		scanf("%s%s", ops, s);
		Decode(s, mask);
		if (*ops == 'Q') {
			ans = sam.Query(s);
			mask ^= ans;
			printf("%d\n", ans);
		} else {
			sam.Insert(s);
		}
	}
	return 0;
}
