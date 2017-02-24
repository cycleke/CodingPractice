#include <queue>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

struct SAM {
	static const int MaxS = 800000 + 5;
	struct node {
		int step, sz1, sz2, d;
		node *pre, *ch[26];
		void clear() {
			pre = NULL;
			sz1 = sz2 = d = 0;
			memset(ch, 0, sizeof ch);
		}
	} node_mset[MaxS], *cnode, *root, *last;
	long long ans;
	queue<node*> q;
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
		
	}

	void calc() {
		for (node *i = node_mset; i < cnode; ++i)
			if (i->pre)
				++(i->pre->d);
		
		for (node *i = node_mset; i < cnode; ++i)
			if (!i->d) q.push(i);
		while (!q.empty()) {
			node *u = q.front();
			q.pop();
			if (u->pre) {
				u->pre->sz1 += u->sz1;
				u->pre->sz2 += u->sz2;
				if (!--(u->pre->d))
					q.push(u->pre);
			}
		}
		long long t;
		for (node *i = node_mset; i < cnode; ++i) {
			t = i->step;
			if (i->pre)
				t -= i->pre->step;
			ans += t * i->sz1 * i->sz2;
		}
	}
	
} sam;

char s[200005];

int main() {
	sam.Init();
	
	scanf("%s", s);
	for (char *i = s; *i; ++i) {
		sam.Insert(*i - 'a');
		++sam.last->sz1;
	}
	scanf("%s", s);
	sam.last = sam.root;
	for (char *i = s; *i; ++i) {
		sam.Insert(*i - 'a');
		++sam.last->sz2;
	}
	sam.calc();
	printf("%lld\n", sam.ans);
	return 0;
}
