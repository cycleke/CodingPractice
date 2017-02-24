#include <cstdio>
#include <cstring>

void cmax(int &a, const int &b) {
	if (a < b) a = b;
}
void cmin(int &a, const int &b) {
	if (b < a) a = b;
}
inline int min(const int &a, const int &b) {
	return a < b ? a : b;
}
inline int max(const int &a, const int &b) {
	return a < b ? b : a;
}

#define rep(i, l, r) for (int i = l; i < r; ++i)
#define rtp(a, i, l, r) for (a i = l; i < r; ++i)

const int MaxN = 200005;

struct node {
	int step;
	int amx, cmx;
	node *pre, *ch[26];
}node_mset[MaxN], *cnode = node_mset, *order[MaxN], *root, *last;

int cnt[MaxN], size;

node *newnode() {
	++size;
	cnode->amx = 0x3f3f3f3f;
	cnode->step = cnode->cmx = 0;
	cnode->pre = NULL;
	memset(cnode->ch, 0, sizeof cnode->ch);
	return cnode++;
}

char s[MaxN];

inline void Insert(int c) {
	node *np = newnode(), *p = last;
	np->step = p->step + 1;
	for (; p && !p->ch[c]; p = p->pre)
		p->ch[c] = np;
	if (!p)
		np->pre = root;
	else {
		node *q = p->ch[c];
		if (p->step + 1 == q->step)
			np->pre = q;
		else {
			node *nq = newnode();
			memcpy(nq->ch, q->ch, sizeof nq->ch);
			nq->step = p->step + 1;
			nq->pre = q->pre;
			q->pre = np->pre = nq;
			for (; p && p->ch[c] == q; p = p->pre)
				p->ch[c] = nq;
		}
	}
	last = np;
}

inline void Sort() {
	rep(i, 0, size) cnt[i] = 0;
	rtp(node*, i, node_mset, cnode) ++cnt[i->step];
	rep(i, 1, size) cnt[i] += cnt[i - 1];
	rtp(node*, i, node_mset, cnode) order[--cnt[i->step]] = i;
}

inline void Add_Match(const char *s) {
	node *u = root;
	int c, match = 0;
	rtp(node*, i, node_mset, cnode) i->cmx = 0;
	for (const char *i = s; *i; ++i) {
		c = *i - 'a';
		if (u->ch[c]) {
			++match;
			u = u->ch[c];
		} else {
			for (; u && !u->ch[c]; u = u->pre);
			if (!u)
				match = 0, u = root;
			else
				match = u->step + 1, u = u->ch[c];
		}
		cmax(u->cmx, match);
	}
	for (int i = size - 1; ~i; --i) {
		u = order[i];
		cmin(u->amx, u->cmx);
		if (u->pre)
			cmax(u->pre->cmx, min(u->pre->step, u->cmx));
	}
}

inline int Cal() {
	int ret = 0;
	rtp(node*, i, node_mset, cnode)
		cmax(ret, i->amx);
	return ret;
}

int main() {
	root = last = newnode();
	scanf("%s", s);
	for (char *it = s; *it; ++it)
		Insert(*it - 'a');
	Sort();
	while (scanf("%s", s) == 1)
		Add_Match(s);
	printf("%d\n", Cal());
	return 0;
}
