#include <cstdio>
#define N 1000001
struct edge {int t; edge *n;} me[N<<1|1], *g[N], *ce = me;
#define adde(a, b) (*ce = (edge){b, g[a]}, g[a] = ce++)
int sz[N];
long long dp[N];

void d1(int u, int f) {
	dp[u] = sz[u] = 1;
	for (edge *it = g[u]; it; it = it->n)
		if (it->t ^ f) {
			d1(it->t, u);
			sz[u] += sz[it->t];
			dp[u] += dp[it->t] + sz[it->t];
		}
}

void d2(int u, int f) {
	for (edge *it = g[u]; it; it = it->n)
		if (it->t ^ f) {
			dp[it->t] = dp[u] + sz[1] - (sz[it->t] << 1);
			d2(it->t, u);
		}
}

int main() {
	int n, x, y, i;
	scanf("%d", &n);
	for (i = 1; i < n; ++i) {
		scanf("%d%d", &x, &y);
		adde(x, y), adde(y, x);
	}
	d1(1, 0); d2(1, 0);
	for (i = x = 1; i <= n; ++i)
		if (dp[x] < dp[i]) x = i;
	printf("%d\n", x);
	return 0;
}
