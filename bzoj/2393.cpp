#include <cstdio>
#include <algorithm>
using namespace std;

const int MaxN = 2001;
typedef long long i64;
i64 a[MaxN], b[MaxN], ans, l, r;
int n, m;
bool vis[MaxN];
i64 gcd(i64 a, i64 b) {
	for (static i64 t; b; t = b, b = a % b, a = t);
	return a;
}

void pre(i64 x) {
	if (x > r) return;
	a[++m] = x;
	pre((x << 3) + (x << 1) + 2);
	pre((x << 3) + (x << 1) + 9);
}

void dfs(int x, int y, i64 z) {
	if (x > n) {
		if (y & 1)
		  ans += r / z - (l - 1) / z;
		else if (y)
		  ans -= r / z - (l - 1) / z;
		return;
	}
	dfs(x + 1, y, z);
	i64 t = b[x] / gcd(b[x], z) * z;
	if (t <= r)
	  dfs(x + 1, y + 1, t);
}

int main() {
	scanf("%lld%lld", &l, &r);
	pre(2), pre(9);
	std::sort(a + 1, a + m + 1);
	for (int i = 1; i <= m; ++i)
	  if (!vis[i]) {
		  b[++n] = a[i];
		  //printf("%lld\n", a[i]);
		  for (int j = i + 1; j <= m; ++j)
			if (a[j] % a[i] == 0)
			  vis[j] = true;
	  }
	//printf("%d %d\n", n, m);
	for (int i = 1, j = n; i < j; ++i, --j)
	  std::swap(b[i], b[j]);
	dfs(1, 0 ,1);
	printf("%lld\n", ans);
	return 0;
}
