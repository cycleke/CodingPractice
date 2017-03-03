#include <ctime>
#include <cstdio>
#include <algorithm>
const int MaxN = 10001;
typedef long long i64;
i64 gcd(i64 a, i64 b) {
	for (static i64 t; b; t = b, b = a % b, a = t);
	return a;
}
int  n, m;
bool vis[MaxN];
i64 l, r, ans, a[MaxN], b[MaxN];
void pre(i64 x) {
	if (x > r) return;
	a[++m] = x;
	pre((x << 3) + (x << 1) + 6);
	pre((x << 3) + (x << 1) + 8);
}
void dfs(int x, int y, i64 z) {
	if (x > n) {
		if (y & 1) ans += r / z - (l - 1) / z;
		else if (y) ans -= r / z - (l - 1) / z;
		return;
	}
	dfs(x + 1, y, z);
	i64 t = z / gcd(b[x], z);
	if ((double)b[x] * t <= r)
	  dfs(x + 1, y + 1, b[x] * t);
}
int main() {
	//freopen("t.in", "r", stdin);
	scanf("%lld%lld", &l, &r);
	pre(6), pre(8);
	std::sort(a + 1, a + m + 1);
	for (int i = 1; i <= m; ++i)
	  if (!vis[i]) {
		  b[++n] = a[i];
		  //printf("%lld\n", a[i]);
		  for (int j = i + 1; j <= m; ++j)
			if (a[j] % a[i] == 0)
			  vis[j] = true;
	  }
	for (int i = 1, j = n; i < j; ++i, --j)
	  std::swap(b[i], b[j]);
	//printf("%.3lf\n", (double)clock() / CLOCKS_PER_SEC);
	dfs(1, 0, 1);
	printf("%lld\n", ans);
	return 0;
}
