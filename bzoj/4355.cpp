#include <cstdio>
#include <cstring>
#include <algorithm>

const int maxn(3e5 + 7);
const long long inf(1LL << 60);
typedef std::pair<long long, long long> pll;

struct node {
	int l, r, cnt, tot;
	long long mi, sec;
	pll tag;
	node *ls, *rs;
} node_mset[maxn * 2], *cnode = node_mset, *root;

inline pll operator + (const pll &a, const pll &b) {
	return pll(std::max(a.first + b.first, -inf), std::max(a.second + b.first, b.second));
}

inline void pushup(node *u) {
	u->cnt = u->ls->cnt + u->rs->cnt;
	if (u->ls->mi < u->rs->mi) {
		u->mi = u->ls->mi;
		u->tot = u->ls->tot;
		u->sec = std::min(u->ls->sec, u->rs->mi);
	} else if (u->ls->mi > u->rs->mi) {
		u->mi = u->rs->mi;
		u->tot = u->rs->tot;
		u->sec = std::min(u->rs->sec, u->ls->mi);
	} else {
		u->mi = u->ls->mi;
		u->tot = u->ls->tot + u->rs->tot;
		u->sec = std::min(u->ls->sec, u->rs->sec);
	}
}

void build(node * &u, int l, int r) {
	u = cnode++;
	u->l = l, u->r = r;
	u->tag = pll(0, -inf);
	if (l ^ r) {
		int mid = (l + r) >> 1;
		build(u->ls, l, mid);
		build(u->rs, mid + 1, r);
		pushup(u);
	} else {
		scanf("%lld", &u->mi);
		u->sec = inf;
		if (!u->mi) u->cnt = 1;
		u->tot = 1;
	}
}

void pushdown(node *u);
void cover(node *u, const pll &tag);

void pushdown(node *u) {
	if (u->tag == pll(0, -inf))
		return;
	u->ls->tag = u->ls->tag + u->tag;
	u->rs->tag = u->rs->tag + u->tag;
	cover(u->ls, u->tag);
	cover(u->rs, u->tag);
	u->tag = pll(0, -inf);
}

void cover(node *u, const pll &tag) {
	static long long a, b;
	a = std::max(std::max(u->mi + tag.first, tag.second), 0LL);
	b = std::max(std::max(u->sec + tag.first, tag.second), 0LL);
	if (u->sec == inf) b = inf;
	else if (inf < b) b = inf;
	if (a >= b) {
		pushdown(u);
		pushup(u);
	} else {
		u->mi = a;
		u->sec = b;
		u->cnt = a ? 0 : u->tot;
	}
}

void modify(node *u, const int &x, const int &y, const pll &tag) {
	if (x <= u->l && u->r <= y) {
		u->tag = u->tag + tag;
		cover(u, tag);
		return;
	}
	int mid = (u->l + u->r) >> 1;
	pushdown(u);
	if (x <= mid) modify(u->ls, x, y, tag);
	if (y  > mid) modify(u->rs, x, y, tag);
	pushup(u);
}

int query(node *u, const int &x, const int &y) {
	if (x <= u->l && u->r <= y)
		return u->cnt;
	int mid = (u->l + u->r) >> 1, ret = 0;
	pushdown(u);
	if (x <= mid) ret += query(u->ls, x, y);
	if (y  > mid) ret += query(u->rs, x, y);
	return ret;
}

int main() {
	freopen("4355.in", "r", stdin);
	int n, m, opt, u, v, c;
	scanf("%d%d", &n, &m);
	build(root, 1, n);
	while (m--) {
		scanf("%d%d%d", &opt, &u, &v);
		if (opt ^ 3) scanf("%d", &c);
		if (opt == 1)
			modify(root, u, v, pll(-inf, c));
		else if (opt == 2)
			modify(root, u, v, pll(c, 0));
		else
			printf("%d\n", query(root, u, v));
	}
	return 0;
}
