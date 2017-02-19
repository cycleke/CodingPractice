#include <bits/stdc++.h>
using namespace std;
#define N 50003
typedef int arr[N];
arr in, ou, d, dq;
struct edge {
	int t;
	edge *n;
} me[N << 1], *ce, *g[N];
#define adde(a, b) (*ce = (edge){b, g[a]}, g[a] = ce++)
int dfn;
void dfs(int u, int fa) {
	dq[in[u] = ++dfn] = u;
	for (edge *it = g[u]; it; it = it->n)
	  if (it->t ^ fa) {
		  d[it->t] = d[u] + 1;
		  dfs(it->t, u);
	  }
	ou[u] = dfn;
}
struct node {
	int l, r, len, d;
	long long ly1, ly2, sum;
	bool noneed() const {
		return !ly1 && !ly2;
	}
}C[N << 2];
#define ls u << 1
#define rs u << 1 | 1
//SegMent_Tree
void pu(const int &u) {
	C[u].sum = C[ls].sum + C[rs].sum;
}
void pd(const int &u) {
	if (C[u].noneed()) return;
	static long long l1, l2;
	l1 = C[u].ly1, l2 = C[u].ly2;
	C[ls].ly1 += l1; C[ls].sum += l1 * C[ls].len;
	C[rs].ly1 += l1; C[rs].sum += l1 * C[rs].len;
	C[ls].ly2 += l2; C[ls].sum += l2 * C[ls].d;
	C[rs].ly2 += l2; C[rs].sum += l2 * C[rs].d;
	C[u].ly1 = C[u].ly2 = 0LL;
}
void build(int u, int l, int r) {
	C[u] = (node){l, r, r - l + 1, 0, 0LL, 0LL, 0LL};
	if (l >= r)
	  C[u].d = d[dq[l]];
	else {
		int mid = (l + r) >> 1;
		build(ls, l, mid);
		build(rs, mid + 1, r);
		C[u].d = C[ls].d + C[rs].d;
	}
}
void upd1(int u, const int &x, const int &y, const int &delta) {
	if (x <= C[u].l && C[u].r <= y) {
		C[u].ly1 += delta;
		C[u].sum += delta * C[u].len;
	} else {
		int mid = (C[u].l + C[u].r) >> 1;
		pd(u);
		if (x <= mid) upd1(ls, x, y, delta);
		if (mid <  y) upd1(rs, x, y, delta);
		pu(u);
	}
}
void upd2(int u, const int &x, const int &y, const int &delta) {
	if (x <= C[u].l && C[u].r <= y) {
		C[u].ly2 += delta;
		C[u].sum += delta * C[u].d;
	} else {
		int mid = (C[u].l + C[u].r) >> 1;
		pd(u);
		if (x <= mid) upd2(ls, x, y, delta);
		if (mid <  y) upd2(rs, x, y, delta);
		pu(u);
	}
}
long long query(int u, const int &x, const int &y) {
	if (x <= C[u].l && C[u].r <= y) 
	  return C[u].sum;
	int mid = (C[u].l + C[u].r) >> 1;
	long long ret = 0;
	pd(u);
	if (x <= mid) ret += query(ls, x, y);
	if (mid <  y) ret += query(rs, x, y);
	return ret;
}
int main() {
	int _, n, q;
	char ops[3];
	scanf("%d", &_);
	d[1] = 1;
	for (int __ = 1; __ <= _; ++__) {
		printf("Case #%d:\n", __);
		scanf("%d%d", &n, &q);
		memset(g, 0, sizeof g);
		ce = me;
		for (int i = 2, u; i <= n; ++i) {
			scanf("%d", &u);
			adde(u, i);
			adde(i, u);
		}
		dfn = 0;
		dfs(1, 0);
		build(1, 1, n);
		for (int x, y; q; --q) {
			scanf("%s%d", ops, &x);
			if (*ops == 'Q')
			  printf("%lld\n", query(1, in[x], ou[x]));
			else {
				scanf("%d", &y);
				upd1(1, in[x], ou[x], y - d[x]);
				upd2(1, in[x], ou[x], 1);
			}
		}
	}
	return 0;
}
