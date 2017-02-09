#include <cstdio>
#define N 60005
#define OP 230002
int n, mx, ans[N], s[N], tr[160001];
struct opt{int x, y, k, id;char c;}q[OP], t[OP];
#define rep(i, l, r) for (i = l; i <= r; ++i)
#define add(x, y) (q[++_opt] = (opt){x + y, x - y, 0, 0, 0}, (mx < (x + y) ? mx = (x + y) : 1))
inline void plus(int x) {
	for (; x <= mx; x += x & -x)
		++tr[x];
}
inline int gsum(int x) {
	static int r;
	if (x < 0) return 0;
	if (x > mx) x = mx;
	for (r = 0; x; x ^= x & -x)
		r += tr[x];
	return r;
}
inline void clr(int x) {
	for (; x <= mx; x += x & -x)
		tr[x] = 0;
}

void cdq(int l, int r) {
	if (l >= r) return;
	int m = l + r >> 1, i1 = l, i2 = m + 1, ti = l;
	cdq(l, m), cdq(m + 1, r);
	for (; i2 <= r; t[ti++] = q[i2++]) {
		for (; i1 <= m && q[i1].y <= q[i2].y; t[ti++] = q[i1++])
			if (!q[i1].c) plus(q[i1].x);
		if (q[i2].c) {
			if (q[i2].c & 1)
				ans[q[i2].id] += gsum(q[i2].x + q[i2].k) - gsum(q[i2].x - q[i2].k - 1);
			else
				ans[q[i2].id] += gsum(q[i2].x - q[i2].k - 1) - gsum(q[i2].x + q[i2].k);
		}
	}
	for (; i1 <= m; t[ti++] = q[i1++]);
	rep(i1, l, m) if (!q[i1].c) clr(q[i1].x);
	rep(i1, l, r) q[i1] = t[i1];
}
int main() {
	freopen("t.in", "r", stdin);
	int i, m, a, b, idx = 0, _opt = 0, x, y;
	char ts[11];
	scanf("%d%d", &n, &m);
	rep(i, 1, n) {
		scanf("%d", s + i);
		add(i, s[i]);
	}
	while (m--) {
		scanf("%s%d%d", ts, &a, &b);
		if (*ts == 'Q') {
			x = a + s[a], y = a - s[a], ++idx;
			q[++_opt] = (opt){x, y + b, b, idx, 1};
			q[++_opt] = (opt){x, y - b - 1, b, idx, 1};
		} else {
			s[a] = b;
			add(a, b);
		}
	}
	cdq(1, _opt);
	rep(i, 1, idx) printf("%d\n", ans[i]);
	return 0;
}
