#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

struct SAM {
	static const int MaxS = 4000 + 5;
	struct node {
		int step;
		node *pre, *ch[26];
		void clear() {
			pre = NULL;
			memset(ch, 0, sizeof ch);
		}
	} node_mset[MaxS], *cnode, *root, *last;
	long long ans;
	inline node *newnode(const int &step) {
		cnode->clear();
		cnode->step = step;
		return cnode++;
	}

	void Init() {
		ans = 0LL;
		cnode = node_mset;
		root = last = newnode(0);
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
				q->pre = np->pre = nq;
				for (; p && p->ch[c] == q; p = p->pre)
					p->ch[c] = nq;
			}
		}
		last = np;
		ans += last->step - last->pre->step;
	}
	
} sam;

char s[2005];
long long ans[10005];

struct ask {
	int l, r, id;
} q[10005];

bool operator < (const ask &a, const ask &b) {
	return (a.l ^ b.l) ? a.l < b.l : a.r < b.r;
}

int main() {
	int _, m;
	scanf("%d", &_);
	while (_--) {
		scanf("%s%d", s + 1, &m);
		for (int i = 1; i <= m; ++i) {
			scanf("%d%d", &q[i].l, &q[i].r);
			q[i].id = i;
		}
		sort(q + 1, q + m + 1);
		for (int i = 1, r; i <= m; ++i) {
			if (q[i].l ^ q[i - 1].l) {
				r = q[i].l - 1;
				sam.Init();
			}
			while (r < q[i].r) sam.Insert(s[++r] - 'a');
			ans[q[i].id] = sam.ans;
		}
		for (int i = 1; i <= m; ++i)
			printf("%lld\n", ans[i]);
	}
	return 0;
}
