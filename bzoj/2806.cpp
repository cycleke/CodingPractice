#include <cmath>
#include <cstdio>
#include <cstring>

const int MaxS = 1100013;

struct node {
	int step;
	node *pre, *ch[3];
} node_mest[MaxS * 2], *cnode = node_mest, *root, *last;

inline node *newnode(const int &step) {
	cnode->step = step;
	return cnode++;
}

inline void Insert(const int &c) {
	node *p = last, *np = newnode(p->step + 1);
	last = np;
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
			memcpy(nq->ch, q->ch, sizeof nq->ch);
			nq->pre = q->pre;
			q->pre = np->pre = nq;
			for (; p && p->ch[c] == q; p = p->pre)
				p->ch[c] = nq;
		}
	}
}

int dp[MaxS], f[MaxS], g[MaxS], q[MaxS];
char s[MaxS];

inline void predp(const int &n) {
	node *u = root;
	int match = 0, idx;
	for (int i = 1; i <= n; ++i) {
		idx = s[i] - 48;
		if (u->ch[idx]) {
			u = u->ch[idx];
			++match;
		} else {
			while (u && !u->ch[idx]) u = u->pre;
			if (u) match = u->step + 1, u = u->ch[idx];
			else u = root, match = 0;
		}
		dp[i] = match;
	}
}

inline int check(int x, const int &n) {
	int *l = q, *r = q, t;
	for (int i = 1; i <= n; ++i) {
		if ((t = i - x) >= 0) {
			while (l < r && g[r[-1]] < g[t]) --r;
			*r++ = t;
		}
		while (l < r && *l < i - dp[i]) ++l;
		f[i] = f[i - 1];
		if (l < r && f[i] < g[*l] + i)
			f[i] = g[*l] + i;
		g[i] = f[i] - i;
	}
	return f[n];
}

int main() {
	int n, m, len, need, l, r, mid;
	scanf("%d%d", &n, &m);
	last = root = newnode(0);
	while (m--) {
		scanf("%s", s);
		for (char *i = s; *i; ++i)
			Insert(*i - 48);
		if (m) Insert(2);
	}
	while (n--) {
		scanf("%s", s + 1);
		len = strlen(s + 1);
		need = (int)(ceil((double)len * 0.9));
		predp(len);
		if (check(1, len) < need) {
			puts("0");
			continue;
		}
		for (l = 2, r = len; l <= r; )
			if (mid = (l + r) >> 1,check(mid, len) >= need)
				l = mid + 1;
			else
				r = mid - 1;
		printf("%d\n", r);
	}
	return 0;
}
