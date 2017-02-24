#include <cstdio>
#include <cstring>

struct SAM {
	static const int MaxS = 90000 * 2 + 15;
	struct node {
		int step, cnt;
		node *pre, *ch[26];
		void clear() {
			cnt = 0;
			pre = NULL;
			memset(ch, 0, sizeof ch);
		}
	} node_mset[MaxS], *order[MaxS], *cnode, *last, *root;
	int cnt[MaxS], size;
	
	inline node *newnode(const int &step) {
		++size;
		cnode->clear();
		cnode->step = step;
		return cnode++;
	}

	void Init() {
		size = 0;
		cnode = node_mset;
		last = root = newnode(0);
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
				np->pre = q->pre = nq;
				for (; p && p->ch[c] == q; p = p->pre)
					p->ch[c] = nq;
			}
		}
		last = np;
	}

	void toposort() {
		for (int i = 0; i < size; ++i) cnt[i] = 0;
		for (node *it = node_mset; it < cnode; ++it) ++cnt[it->step];
		for (int i = 1; i < size; ++i) cnt[i] += cnt[i - 1];
		for (node *it = node_mset; it < cnode; ++it) order[--cnt[it->step]] = it;
	}

	void calc() {
		int i, j;
		node *u, *p;
		for (i = size - 1; ~i; --i) {
			u = order[i];
			for (j = 0; j < 26; ++j)
				if (u->ch[j]) {
					p = u->ch[j];
					u->cnt += p->cnt + 1;
				}
		}
	}

	void getans(int k, char *s) {
		char *i = s;
		node *u = root;
		while (k) {
			for (int j = 0; j < 26; ++j) {
				if (!u->ch[j]) continue;
				if (u->ch[j]->cnt + 1 < k) {
					k -= u->ch[j]->cnt + 1;
					continue;
				}
				--k;
				*i++ = j + 'a';
				u = u->ch[j];
				break;
			}
		}
		*i = 0;
	}
	
}sam;


char s[90005];

int main() {

	sam.Init();
	scanf("%s", s);
	for (char *i = s; *i; ++i)
		sam.Insert(*i - 'a');
	sam.toposort();
	sam.calc();
	
	int m, k;
	scanf("%d", &m);
	while (m--) {
		scanf("%d", &k);
		sam.getans(k, s);
		puts(s);
	}
	
	return 0;
}
