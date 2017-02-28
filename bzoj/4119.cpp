#include <cstdio>
#include <cstring>
const long long llf = 1LL << 60;
const int MaxS = 600003, MaxN = 300003, inf = 0x3fffffff;
typedef int _[MaxN];
typedef long long __[MaxN];
struct node {
	int step, mx, mi, size;
	long long a1, a2;
	node *pre, *c[26];
} node_mset[MaxS], *cnode = node_mset, *root, *last, *order[MaxS];
inline node *newnode(const int &step, int mx = -inf, int mi = inf, int size = 0) {
	cnode->mx = mx;
	cnode->mi = mi;
	cnode->size = size;
	cnode->step = step;
	cnode->a2 = -llf;
	return cnode++;
}
_ a, cnt;
__ ans1, ans2;
inline void Insert(const int &c, const int &val) {
	node *p = last, *np = newnode(p->step + 1, val, val, 1);
	for (last = np; p && !p->c[c]; p = p->pre)
		p->c[c] = np;
	if (!p)
		np->pre = root;
	else {
		node *q = p->c[c];
		if (q->step == p->step + 1)
			np->pre = q;
		else {
			node *nq = newnode(p->step + 1);
			memcpy(nq->c, q->c, sizeof q->c);
			nq->pre = q->pre;
			q->pre = np->pre = nq;
			for (; p && p->c[c] == q; p = p->pre)
				p->c[c] = nq;
		}
	}
}
char s[MaxN];
template<class T>
inline void cmin(T &a, const T &b) {
	if (b < a) a = b;
}
template<class T>
inline void cmax(T &a, const T &b) {
	if (a < b) a = b;
}
int main() {
	//freopen("t.in", "r", stdin);
	int n, mxstep = 0;
	scanf("%d%s", &n, s);
	last = root = newnode(0);
	for (int i = 0; i < n; ++i) {
		scanf("%d", a + i);
		ans2[i] = -llf;
	}
	for (int i = n - 1; ~i; --i) Insert(s[i] - 'a', a[i]);
	for (node *i = node_mset; i < cnode; ++i) {
		if (i->step > mxstep)
			mxstep = i->step;
		++cnt[i->step];
	}
	++mxstep;
	for (int i = 1; i < mxstep; ++i) cnt[i] += cnt[i - 1];
	for (node *i = node_mset; i < cnode; ++i) order[--cnt[i->step]] = i;
	node *u, *f;
	for (int i = cnode - node_mset - 1; ~i; --i)
		if (f = (u = order[i])->pre) {
			f->a1 += (long long)f->size * u->size;
			f->size += u->size;
			if (f->mx ^ -inf) cmax(f->a2, (long long)f->mx * u->mx);
			if (f->mi ^  inf) cmax(f->a2, (long long)f->mi * u->mi);
			cmax(f->mx, u->mx);
			cmin(f->mi, u->mi);
		}
	for (node *i = node_mset; i < cnode; ++i) {
		ans1[i->step] += i->a1;
		cmax(ans2[i->step], i->a2);
	}
	for (int i = n - 2; ~i; --i)
		if (ans1[i + 1]) {
			ans1[i] += ans1[i + 1];
			cmax(ans2[i], ans2[i + 1]);
		}
	for (int i = 0; i < n; ++i)
		printf("%lld %lld\n", ans1[i], ans1[i] ? ans2[i] : 0LL);
	return 0;
}
