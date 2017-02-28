#include <cstdio>
#include <cstring>

const int MaxN = 1e5 + 13;
typedef int arr[MaxN];

arr a, b, opt, L, R;

#define ls u << 1
#define rs u << 1 | 1
#define Range const int &x, const int &y
#define VarMid int mid = (C[u].l + C[u].r) >> 1

struct node {
	int l, r, len, sum, lazy;
	bool inrange(Range);
} C[MaxN << 2];

bool node :: inrange(Range) {
	return x <= l && r <= y;
}

inline void pd(const int &u)  {
	if (~C[u].lazy) {
		C[ls].sum = C[u].lazy ? C[ls].len : 0;
		C[rs].sum = C[u].lazy ? C[rs].len : 0;
		C[ls].lazy = C[rs].lazy = C[u].lazy;
		C[u].lazy = -1;
	}
}

inline void pu(const int &u) {
	C[u].sum = C[ls].sum + C[rs].sum;
}

void build(int u, int l, int r) {
	C[u] = (node) {l, r, r - l + 1, 0, -1};
	if (l ^ r) {
		int mid = (l + r) >> 1;
		build(ls, l, mid);
		build(rs, mid + 1, r);
	}
}

void rebuild(int u) {
	C[u].lazy = -1;
	if (C[u].l ^ C[u].r) {
		rebuild(ls);
		rebuild(rs);
		pu(u);
	} else C[u].sum = b[C[u].l];
}

void modify(int u, Range, const int &v) {
	if (C[u].inrange(x, y))
		return (void)(C[u].lazy = v, C[u].sum = v ? C[u].len : 0);
	VarMid; pd(u);
	if (x <= mid) modify(ls, x, y, v);
	if (y >  mid) modify(rs, x, y, v);
	pu(u);
}

int query(int u, Range) {
	if (C[u].inrange(x, y))
		return C[u].sum;
	VarMid, ret = 0; pd(u);
	if (x <= mid) ret = query(ls, x, y);
	if (y > mid) ret += query(rs, x, y);
	return ret;
}

int main() {
	//freopen("t.in", "r", stdin);
	int n, m, i, l, r, mid, t, q;
	scanf("%d%d", &n, &m);
	for (i = 1; i <= n; ++i) scanf("%d", a + i);
	build(1, 1, n);
	for (i = 0; i < m; ++i) scanf("%d%d%d", opt + i, L + i, R + i);
	scanf("%d", &q);
	for (l = 1, r = n; l <= r; ) {
		mid = (l + r) >> 1;
		for (i = 1; i <= n; ++i) b[i] = (a[i] >= mid);
		rebuild(1);
		for (i = 0; i < m; ++i) {
			t = query(1, L[i], R[i]);
			if (t)
				opt[i] ? modify(1, L[i], L[i] + t - 1, 1) : modify(1, R[i] - t + 1, R[i], 1);
			if (R[i] - L[i] + 1 - t)
				opt[i] ? modify(1, L[i] + t, R[i], 0) : modify(1, L[i], R[i] - t, 0);
			//printf("%d ", t);
		}
		//printf("%d %d\n",mid, query(1, q, q));
		if (query(1, q, q)) l = mid + 1;
		else r = mid - 1;
	}
	printf("%d\n", l - 1);
	return 0;
}
