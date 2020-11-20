#include <bits/stdc++.h>
using namespace std;

const int N = 5005, M = 5e5 + 5;
const double eps = 1e-5;
double L, R, mid, tmp;
int ans[M], fa[N], tot, cnt, n, m, k;
int x[M], y[M], w[M], r[M];

bool cmp(int a, int b) {
	return (w[a] + (x[a] == 1) * mid) < (w[b] + (x[b] == 1) * mid);
}
int find(int a) { return (fa[a] ^ a) ? (fa[a] = find(fa[a])) : a; }

void work(bool flag) {
	tot = cnt = 0;
	for (int i = 1; i <= n; ++i) fa[i] = i;
	sort(r + 1, r + m + 1, cmp);
	for (int i = 1; i <= m; ++i) {
		int p = r[i];
		int fx = find(x[p]), fy = find(y[p]);
		if ((fx ^ fy) && (cnt + (x[p] == 1) <= k || flag)) {
			fa[fx] = fy; ans[tot++] = p;
			if (x[p] == 1) ++cnt;
		}
	}
}

int main() {
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 1; i <= m; ++i) {
		scanf("%d%d%d", x + i, y + i, w + i);
		if (x[i] > y[i]) swap(x[i], y[i]);
		cnt += (x[i] == 1);
		r[i] = i;
	}
	if (cnt < k || (n > 1 && !k)) return puts("-1"), 0;
	mid = 0.; work(1); 
	if (tot + 1 < n) return puts("-1"), 0;
	L = -1e5, R = 1e5;
	while (L + eps < R && cnt != k) {
		mid = (L + R) / 2.; work(1);
		if (cnt < k) R = mid;
		else L = mid;
	}
	if (cnt ^ k) mid = (L + R) / 2.; work(0);
	printf("%d\n", tot);
	for (int i = 0; i < tot - 1; ++i) printf("%d ", ans[i]);
	if (tot) printf("%d\n", ans[tot-1]);
	return 0;
}
