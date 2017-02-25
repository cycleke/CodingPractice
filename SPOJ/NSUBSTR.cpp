#include <cstdio>
#include <cstring>

inline void cmax(int &a, const int &b) {
	if (a < b) a = b;
}

struct SAM {
	static const int MaxS = 250000 * 2 + 13;
	struct node {
		int step, r;
		node *pre, *ch[26];
		void clear() {
			r = 0;
			pre = NULL;
			memset(ch, 0, sizeof ch);
		}
	} node_mest[MaxS], *order[MaxS], *root, *last, *cnode;
	int cnt[MaxS], dp[MaxS], size;

	inline node *newnode(const int &step) {
		++size;
		cnode->clear();
		cnode->step = step;
		return cnode++;
	}
	
	void Init() {
		size = 0;
		cnode = node_mest;
		root = last = newnode(0);
	}

	void Insert(const int &c) {
		node *p = last, *np = newnode(p->step + 1);
		last = np;
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
	}
	
	void toposort() {
		for (int i = 0; i <= size; ++i) cnt[i] = 0;
		for (node *i = node_mest; i < cnode; ++i) ++cnt[i->step];
		for (int i = 1; i <= size; ++i) cnt[i] += cnt[i - 1];
		for (node *i = node_mest; i < cnode; ++i) order[--cnt[i->step]] = i;
	}

	void match(const char *s) {
		node *u = root;
		for (const char *i = s; *i; ++i) {
			u = u->ch[*i - 'a'];
			++u->r;
		}
		for (int i = size - 1; ~i; --i)
			if (order[i]->pre) order[i]->pre->r += order[i]->r;
		for (node *i = node_mest; i < cnode; ++i)
			cmax(dp[i->step], i->r);
		for (int i = size; i; --i)
			cmax(dp[i], dp[i + 1]);
	}


	void printans(const int &n) {
		for (int i = 1; i <= n; ++i)
			printf("%d\n", dp[i]);
	}
	
}sam;

char s[250005];

int main() {
	scanf("%s", s);
	sam.Init();
	for (char *i = s; *i; ++i)
		sam.Insert(*i - 'a');
	sam.toposort();
	sam.match(s);
	int n = strlen(s);
	sam.printans(n);
	return 0;
}
