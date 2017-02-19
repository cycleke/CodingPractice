#include <cstdio>
#include <cstring>
#include <algorithm>
#define N 100003

struct node {
	int l, r;
	int mx, add, _mx, _add;
bool inrange(const int &x, const int &y) {
		return x <= l && r <= y;
	}
}C[N << 2 | 1];

#define ls u << 1
#define rs u << 1 | 1

void Build(int u, int l, int r) {
	C[u] = (node) {l, r, 0, 0, 0, 0};
	if (l ^ r) {
		Build(ls, l, (l + r) >> 1);
		Build(rs, ((l + r) >> 1) + 1, r);
	}
}

int max(const int &a, const int &b) {
	return a < b ? b : a;
}

void cmax(int &a, const int &b) {
	if (a < b) a = b;
}

void pu(int u) {
	C[u].mx = max(C[ls].mx, C[rs].mx);
	C[u]._mx = max(C[ls]._mx, C[rs]._mx);
}

void pd(int u) {
	if (C[u]._add) {
		cmax(C[ls]._add, C[ls].add + C[u]._add);
		cmax(C[rs]._add, C[rs].add + C[u]._add);

		cmax(C[ls]._mx, C[ls].mx + C[u]._add);
		cmax(C[rs]._mx, C[rs].mx + C[u]._add);

		C[u]._add = 0;
	}
	if (C[u].add) {
		C[ls].mx += C[u].add;
		C[rs].mx += C[u].add;

		C[ls].add += C[u].add;
		C[rs].add += C[u].add;

		C[u].add = 0;
	}
}

void modify(int u, const int &x, const int &y, const int &v) {
	if (C[u].inrange(x, y)) {
		cmax(C[u]._mx, C[u].mx += v);
		cmax(C[u]._add, C[u].add += v);
		return;
	}
	int m = (C[u].l + C[u].r) >> 1;
	pd(u);
	if (x <= m)
	  modify(ls, x, y, v);
	if (m < y)
	  modify(rs, x, y, v);
	pu(u);
}

int query(int u, const int &x, const int &y) {
	if (C[u].inrange(x, y))
	  return C[u]._mx;
	int m = (C[u].l + C[u].r) >> 1;
	pd(u);
	if (y <= m)
	  return query(ls, x, y);
	if (m < x)
	  return query(rs, x, y);
	return max(query(ls, x, y), query(rs, x, y));
}

int pos[N * 2 + 13], a[N], ans[N];

struct ask {
	int l, r, id;
	bool operator < (const ask &a) const {
		return r < a.r;
	}
}q[N];

int main() {
	int n, q, l, r;
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) 
	  scanf("%d", a + i);
	Build(1, 1, n);
	scanf("%d", &q);
	for (int i = 0; i < q; ++i) {
		scanf("%d%d", &l, &r);
		::q[i] = (ask) {l, r, i};
	}
	std::sort(::q, ::q + q);
	for (int i = 1, j = 0; i <= n && j < q; ++i) {
		modify(1, pos[a[i] + N] + 1, i, a[i]);
		pos[a[i] + N] = i;
		while (j < q && ::q[j].r <= i) {
			ans[::q[j].id] = query(1, ::q[j].l, ::q[j].r);
			++j;
		}
	}
	for (int i = 0; i < q; ++i)
	  printf("%d\n", ans[i]);
}
