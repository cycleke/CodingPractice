#include <cstdio>
#define N 100005
inline void gi(int &a) {
	static char c;
	while (c = getchar(), c < '0'); a = c - '0';
	while (c = getchar(), '-' < c) a = (a << 3) + (a << 1) + c - '0';
}
struct edge {int t, v; edge *n;} me[N<<1|1], *G[N], *ce = me;
#define adde(a, b, c) (*ce = (edge){b, c, G[a]}, G[a] = ce++)
#define FOR(a, b) for (edge *a = G[b]; a; a = a->n)
int dep[N], dis[N], sz[N], rt, mxrt, mxdep, size, n;
long long ans;
int f[2][N<<1|1], g[2][N<<1|1], cnt[N<<1|1];
bool vis[N];

void grt(int u, int fa) {
	int mx = 0, v; sz[u] = 1;
	FOR(it, u) if (!vis[v = it->t] && (v ^ fa)) {
		grt(v, u);
		if (mx < sz[v]) mx = sz[v];
		sz[u] += sz[v];
	}
	if (mx < size - sz[u]) mx = size - sz[u];
	if (mx < mxrt) mxrt = mx, rt = u;
}

inline long long xmul(const int &a, const int &b) {
	return (long long)f[1][a] * g[1][b] + (long long)f[1][a] * g[0][b] + (long long)f[0][a] * g[1][b];
}

void dfs(int u, int fa) {
	if (mxdep < dep[u]) mxdep = dep[u];
	++g[(bool)cnt[dis[u]]++][dis[u]];
	sz[u] = 1;
	FOR(it, u) if (!vis[it->t] && (it->t ^ fa)) {
		dep[it->t] = dep[u] + 1;
		dis[it->t] = dis[u] + it->v;
		dfs(it->t, u);
		sz[u] += sz[it->t];
	}
	--cnt[dis[u]];
}

void work(int u) {
	mxrt = size = sz[u];
	grt(u, 0);
	u = rt;
	vis[u] = 1;
	f[0][n] = 1;
	int v, mx = 0, i;
	FOR(it, u) if (!vis[v = it->t]) {
		dep[v] = mxdep = 1;
		dis[v] = n + it->v;
		dfs(v, u);
		if (mx < mxdep) mx = mxdep;
		ans += (long long)(f[0][n] - 1LL) * g[0][n];
		for (i = -mxdep; i <= mxdep; ++i)
		  ans += xmul(n + i, n - i);
		for (i = -mxdep; i <= mxdep; ++i) {
		  f[0][n + i] += g[0][n + i];
		  f[1][n + i] += g[1][n + i];
		  g[0][n + i] = g[1][n + i] = 0;
		}
	}
	for (i = -mx; i <= mx; ++i)
		f[0][n + i] = f[1][n + i] = 0;
	FOR(it, u) if (!vis[v = it->t]) work(v);
}

int main() {
	//freopen("t.in", "r", stdin);
	gi(n);
	for (int i = 1, u, v, x; i < n; ++i) {
		gi(u), gi(v), gi(x);
		if (!x) x = -1;
		adde(u, v, x);
		adde(v, u, x);
	}
	sz[1] = n;
	work(1);
	printf("%lld\n", ans);
	return 0;
}
