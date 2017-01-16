#include <cstdio>
#define N 63
#define oo 1e22
struct edge{int t; edge *n;}me[N], *ce, *hd[N];
inline void adde(int a, int b) {
	ce->t = b, ce->n = hd[a];
	hd[a] = ce++;
}
int size[N], nxt[N], n, m;
double dp[N][N][N], kk[N], tmp[N][N], C[N], k;
inline void cmax(double &a, double b) {
	if (a < b) a = b;
}
inline void init() {
	static int i, j, k;
	for (i = 0; i <= n; hd[i++] = NULL)
		for (j = 0; j <= n; ++j)
			for (k = 0; k <= n; ++k)
				dp[i][j][k] = -oo;
	ce = me;
}
inline void backpack(int u, int dep) {
	static int s, j, k, v; static edge *it;
	for (j = 0; j <= size[u]; ++j)
		for (k = 0; k <= m; ++k)
			tmp[j][k] = -oo;
	tmp[0][0] = 0.0;
	for (it = hd[u], s = 1; it; it = it->n, ++s) {
		v = it->t;
		for (j = 0; j <= m; ++j)
			for (k = 0; k <= j; ++k)
				cmax(tmp[s][j], tmp[s-1][k] + dp[v][j - k][dep]);
	}
}
void dfs(int u) {
	size[u] = 0;
	for (edge *it = hd[u]; it; it = it->n, ++size[u]) dfs(it->t);
	backpack(u, 2);
	for (int i = 0; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			dp[u][j][i] = tmp[size[u]][j-1] + C[u] * k;
	for (int i = 0; i <= n; ++i) {
		backpack(u, i + 1);
		for (int j = 0; j <= m; ++j)
			cmax(dp[u][j][i], tmp[size[u]][j] + C[u] * kk[i]);
	}
}
int main() {
	int i, j, len; double ans = -oo;
	scanf("%d%d%lf", &n, &m, &k);
	for (i = 1; i <= n; ++i) scanf("%d", nxt + i);
	for (i = 1; i <= n; ++i) scanf("%lf", C + i);
	kk[0] = 1; kk[1] = k;
	for (i = 2; i < N; ++i) kk[i] = kk[i-1] * k;
	for (i = nxt[1], len = 2; i ^ 1; i = nxt[i], ++len) {
		init();
		for (j = 2; j <= n; ++j)
			if (j ^ i) adde(nxt[j], j); else adde(1, j);
		dfs(1);
		cmax(ans, dp[1][m - (nxt[i] != 1)][0] / (1.0 - kk[len]));
	}
	printf("%.2lf\n", ans);
	return 0;
}
