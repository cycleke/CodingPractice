#include <cstdio>

const int maxn(10003), maxk(505);

int tr[maxk][5555], n, k, maxa, a[maxn];

inline void cmax(int &a, const int &b) {
	if (a < b) a = b;
}

inline int query(int x, int y) {
	int ans = 0;
	for (register int i = x; i; i = i & (i - 1))
		for (register int j = y; j; j = j & (j - 1))
			cmax(ans, tr[i][j]);
	return ans;
}

inline void modify(int x, int y, int val) {
	for (register int i = x; i <= k; i += i & -i)
		for (register int j = y; j <= maxa; j += j & -j)
			cmax(tr[i][j], val);
}

int main() {
	int ans(0), t;
	scanf("%d%d", &n, &k);
	++k;
	for (register int i = 1; i <= n; ++i) {
		scanf("%d", a + i);
		cmax(maxa, a[i]);
	}
	maxa += k;
	for (register int i = 1; i <= n; ++i)
		for (register int j = k; j; --j) {
			t = query(j, a[i] + j) + 1;
			cmax(ans, t);
			modify(j, a[i] + j, t);
		}
	printf("%d\n", ans);
	return 0;
}
