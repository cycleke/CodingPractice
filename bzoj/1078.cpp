#include <cstdio>
#include <cstring>
#include <algorithm>

typedef int arr[105];
arr ls, rs, fa, ans;
inline void solve() {
	static int root = 0, x, t, *top = ans;
	for (x = root; ~rs[x]; x = ls[x]);
	t = ls[x];
	if ((~t) && ls[t] < 0 && rs[t] < 0)
		x = t;
	*top++ = x;
	if (x == root) root = ls[root];
	t = fa[x];
	if (~t) fa[ls[t] = ls[x]] = t;
	for (; ~t; t = fa[t])
		std::swap(ls[t], rs[t]);
}

int main() {
	int n, x;
	register int i;
	fa[0] = -1;
	memset(ls, -1, sizeof ls);
	memset(rs, -1, sizeof rs);
	scanf("%d", &n);
	for (i = 1; i <= n; ++i) {
		scanf("%d", &x);
		if (x < 100)
			fa[ls[x] = i] = x;
		else
			fa[rs[x - 100] = i] = x - 100;
	}
	for (i = 0; i <= n; ++i)
		solve();
	for (i = n; ~i; --i)
		printf("%d ", ans[i]);
	return 0;
}
