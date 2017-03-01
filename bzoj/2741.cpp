#include <cstdio>

const int MaxN = 12002, MaxS =  MaxN * 32;
struct node {
	int last;
	node *c[2];
} node_mset[MaxS], *cnode = node_mset, *root[MaxN];

void Insert(node *x, const int &p, const int &val) {
	node *y = root[p] = ++cnode;
	y->last = p;
	for (int i = 1 << 30, j; i; i >>= 1) {
		j = (val & i) ? 1 : 0;
		y->c[j ^ 1] = x->c[j ^ 1];
		y->c[j] = ++cnode;
		x = x->c[j];
		y = y->c[j];
		y->last = p;
	}
}

int Query(int l, int r, const int &val) {
	node *x = root[r];
	int ans = 0;
	for (int i = 1 << 30, j; i; i >>= 1) {
		j = (val & i) ? 0 : 1;
		if (x->c[j]->last >= l)
		  ans ^= i;
		else
		  j ^= 1;
		x = x->c[j];
	}
	return ans;
}

int a[MaxN], pre[125][MaxN];

inline int max(const int &a, const int &b) {
	return a < b ? b : a;
}

inline void cmax(int &a, const int &b) {
	if (a < b) a = b;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("t.in", "r", stdin);
#endif
	int n, m, blo, cnt, lastans = 0, x, y, bg;
	scanf("%d%d", &n, &m);
	for (blo = 1; blo * blo <= n; ++blo);
	cnt = n / blo + (n % blo != 0);
	*cnode = (node) { -1 , {cnode, cnode}};
	Insert(cnode, 0, 0);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", a + i);
		a[i] ^= a[i - 1];
		Insert(root[i - 1], i, a[i]);
	}
	for (int i = 0; i < cnt; ++i)
	  for (int j = i * blo + 1, st = i * blo; j <= n; ++j)
		pre[i][j] = max(pre[i][j - 1], Query(st, j - 1, a[j]));

	while (m--) {
		scanf("%d%d", &x, &y);
		x = (x + lastans % n) % n + 1;
		y = (y + lastans % n) % n + 1;
		if (x > y) x ^= y ^= x ^= y;
		--x;
		bg = x / blo + (x % blo != 0);
		if (bg * blo < y) {
			lastans = pre[bg][y];
			bg = bg * blo;
		} else {
			bg = y;
			lastans = 0;
		}
		for (int i = x; i <= bg; ++i)
		  cmax(lastans, Query(x, y, a[i]));
		printf("%d\n", lastans);
	}

	return 0;
}
