#include <cstdio>
#include <algorithm>
typedef unsigned long long ull;
int n, mid, ed;
ull m, a[45], c1[1 << 20 | 1], c2[1 << 20 | 1], *it, *e1, *e2, ans;
inline void dfs(int i, ull sum) {
	if (sum > m) return;
	if (i >= ed) {
		*it++ = sum;
		return;
	}
	dfs(i + 1, sum);
	dfs(i + 1, sum + a[i]);
}
int main() {
	scanf("%d%llu", &n, &m);
	for (register int i = 0; i < n; ++i) scanf("%llu", a + i);
	mid = n >> 1;
	it = c1, ed = mid, dfs(0, 0), e1 = it;
	it = c2, ed = n, dfs(mid, 0), e2 = it;
	std::sort(c1, e1);
	for (it = c2; it < e2; ++it) ans += std::upper_bound(c1, e1, m - *it) - c1;
	printf("%llu\n", ans);
	return 0;
}
