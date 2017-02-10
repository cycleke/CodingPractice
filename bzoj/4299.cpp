#include <cstdio>
#define N 100005
#define rep(i, l, r) for (register int i = l; i <= r; ++i)
struct node {
	int ls, rs, sum;
}C[N * 33];
int rt[N], cnd, a[N];

void ins(int x, int &y, int l, int r, const int &v) {
	C[y = ++cnd] = C[x];
	C[y].sum += v;
	if (!(l ^ r)) return;
	if (v <= (l + r >> 1))
	  ins(C[x].ls, C[y].ls, l, (l + r >> 1), v);
	else
	  ins(C[x].rs, C[y].rs, (l + r >> 1) + 1, r, v);
}

int quy(int x, int y, int l, int r, const int &v) {
	if (l > v || !(C[x].sum ^ C[y].sum)) return 0;
	if (r <= v) return C[y].sum - C[x].sum;
	int m = l + r >> 1, ret;
	ret = quy(C[x].ls, C[y].ls, l, m, v);
	if (v >= m) ret += quy(C[x].rs, C[y].rs, m + 1, r, v);
	return ret;
}

int main() {
	int n, l, r, x, y, mx = -1;
	scanf("%d", &n );
	rep(i, 1, n) if (scanf("%d", a + i), mx < a[i]) mx = a[i];
	rep(i, 1, n) ins(rt[i - 1], rt[i], 1, mx, a[i]);
	scanf("%d", &n);
	while (n--) {
		scanf("%d%d", &l, &r);
		for (x = 1;; x = y + 1)
		  if ((y = quy(rt[l - 1], rt[r], 1, mx, x)) < x)
			break;
		printf("%d\n", x);
	}
}
