#include <cstdio>
#include <cstring>

const int MaxN = 500003;

struct node {
	int step, size, curtensize;
	node *pre, *ch[26];
} node_mset[MaxN << 1], *cnode = node_mset, *root, *last, *order[MaxN << 1];

inline node *newnode(const int &step, int s = 0) {
	cnode->step = step;
	cnode->size = cnode->curtensize = s;
	return cnode++;
}

inline void Insert(const int &c) {
	node *p = last, *np = newnode(p->step + 1, 1);
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
	last = np;
}

int cnt[MaxN << 1];

inline void toposort() {
	int mxstep = 0;
	for (node *i = node_mset; i < cnode; ++i) {
		if (i->step > mxstep)
			mxstep = i->step;
		++cnt[i->step];
	}
	++mxstep;
	for (int i = 1; i < mxstep; ++i) cnt[i] += cnt[i - 1];
	for (node *i = node_mset; i < cnode; ++i) {
		order[--cnt[i->step]] = i;
		//printf("%d ", i->step);
	}
	//puts("");
}

inline long long calc() {
	toposort();
	int size = cnode - node_mset;
	for (int i = size - 1; ~i; --i)
		if (order[i]->pre) order[i]->pre->size += order[i]->size;
	long long ret = 0;
	for (node *i = node_mset; i < cnode; ++i)
		if (i->pre) {
			ret += (long long)i->pre->curtensize * i->pre->step * i->size;
			i->pre->curtensize += i->size;
		}
	return ret;
}

char s[MaxN];

int main() {
	scanf("%s", s);
	int n = strlen(s);
	long long ans = (long long)(n - 1) * ((long long)n * (n + 1) >> 1);
	last = root = newnode(0);
	for (int i = n - 1; ~i; --i) 
		Insert(s[i] - 'a');
	//printf("%lld\n", ans);
	printf("%lld\n", ans - 2 * calc());
	return 0;
}
