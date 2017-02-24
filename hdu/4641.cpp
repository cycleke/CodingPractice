#include <cstdio>
#include <cstring>

struct SAM {
	static const int MaxN = 250010;
	struct node {
		int step, cnt;
		node *pre, *ch[26];
		void clear() {
			cnt = 0;
			pre = NULL;
			memset(ch, 0, sizeof ch);
		}
	} node_mset[MaxN * 2], *cnode, *root, *last;
	
	int K;
	long long ans;
	
	inline node *newnode(const int &step) {
		cnode->clear();
		cnode->step = step;
		return cnode++;
	}
	void Init(const int &K) {
		this->K = K;
		ans = 0LL;
		cnode = node_mset;
		root = last = newnode(0);
	}

	void update() {
		for (node *p = last; p && p->cnt < K; p = p->pre) {
			if (++p->cnt >= K && p->pre)
				ans += p->step - p->pre->step;
		}
	}
	
	void Insert(const int &c) {
		node *p = last, *np = newnode(p->step + 1);
		
		for (; p && !p->ch[c]; p = p->pre)
			p->ch[c] = np;
		if (!p)
			np->pre = root;
		else {
			node *q = p->ch[c];
			if (p->step + 1 == q->step)
				np->pre = q;
			else {
				node *nq = newnode(p->step + 1);
				memcpy(nq->ch, q->ch, sizeof q->ch);
				nq->pre = q->pre;
				nq->cnt = q->cnt;
				q->pre = np->pre = nq;
				for (; p && p->ch[c] == q; p = p->pre)
					p->ch[c] = nq;
			}
		}
		last = np;
		update();
	}
	
}sam;

char s[50003];

int main() {
	int n, m, k, t;
	while (scanf("%d%d%d", &n, &m, &k) == 3) {
		scanf("%s", s);
		sam.Init(k);
		for (char *i = s; *i; ++i)
			sam.Insert(*i - 'a');
		while (m--) {
			scanf("%d", &t);
			if (t & 1) {
				scanf("%s", s);
				sam.Insert(*s - 'a');
			} else
				printf("%lld\n", sam.ans);
		}
	}
	return 0;
}
