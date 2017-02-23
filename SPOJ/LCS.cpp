#include <cstdio>
#include <cstring>

const int MaxN = 250005;

struct node {
	int len;
	node *ch[26], *pre;
} node_mset[MaxN * 2 + 11], *cnode = node_mset, *root, *last;

char s[MaxN];

void Insert(int w) {
	node *np = cnode++, *p = last;
	np->len = p->len + 1;
	for (; p && !p->ch[w]; p = p->pre)
	  p->ch[w] = np;
	if (!p) 
	  np->pre = root;
	else {
		node *q = p->ch[w];
		if (p->len + 1 == q->len)
		  np->pre = q;
		else {
			node *nq = cnode++;
			memcpy(nq->ch, q->ch, sizeof nq->ch);
			nq->len = p->len + 1;
			nq->pre = q->pre;
			q->pre = np->pre = nq;
			for (; p && p->ch[w] == q; p = p->pre)
				p->ch[w] = nq;
		}
	}
	last = np;
}

int main() {
	int ans = 0, len = 0, idx;
	last = root = cnode++;
	node *u = root;
	scanf("%s", s);
	for (char *it = s; *it; ++it)
		Insert(*it - 'a');
	scanf("%s", s);
	for (char *it = s; *it; ++it) {
		idx = *it - 'a';
		if (u->ch[idx]) {
			++len;
			u = u->ch[idx];
		} else {
			while (u && !u->ch[idx])
				u = u->pre;
			if (!u)
				u = root, len = 0;
			else
				len = u->len + 1, u = u->ch[idx];
		}
		if (ans < len)
			ans = len;
	}
	printf("%d\n", ans);
	return 0;
}
