#include <bits/stdc++.h>
using namespace std;

#define N 100005
#define inf 0x3fffff

struct edge {
	int t, v;
	edge *n;
}me[N << 1], *ce, *g[N];
#define FOR(u) for (edge *it = g[u]; it; it = it->n)
#define adde(a, b, c) (*ce = (edge){b, c, g[a]}, g[a] = ce++)
struct point {
	int x, y, z;
	bool operator < (const point &a) const {
		return (y ^ a.y) ? a.y < y : a.z < z;
	}
}d[N], D[N];

priority_queue<point> heap;

typedef int arr[N];
arr sz, dis, ans, f, id;
bool vis[N], flag[N];
int SZ, rt, cnt;

void dijstra(const int &n) {
	while (!heap.empty())
	  heap.pop();
	for (int i = 1; i <= n; ++i) 
	  if (flag[i]) heap.push((point){i, dis[i] = 0, id[i] = i});
	point p;
	while (!heap.empty()) {
		p = heap.top();
		heap.pop();
		if (vis[p.x])
		  continue;
		vis[p.x] = true;
		FOR(p.x) 
			if (dis[it->t] > dis[p.x] + it->v) 
			  heap.push((point){it->t, dis[it->t] = dis[p.x] + it->v, id[it->t] = p.z});
			else if (dis[it->t] >= dis[p.x] + it->v && id[it->t] > p.z)
			  heap.push((point){it->t, dis[it->t], id[it->t] = p.z});
	}
	for (int i = 1; i <= n; ++i)
	  vis[i] = 0;
}

void grt(int u, int fa) {
	sz[u] = 1;
	f[u] = 0;
	FOR(u) if (!vis[it->t] && (it->t ^ fa)) {
		grt(it->t, u);
		sz[u] += sz[it->t];
		if (sz[it->t] > f[u])
		  f[u] = sz[it->t];
	}
	if (SZ - sz[u] > f[u])
	  f[u] = SZ - sz[u];
	if (f[u] < f[rt]) rt = u;
}

void dfs(int u, int fa, int len) {
	d[cnt++] = (point) {u, len, 0};
	FOR(u) if (!vis[it->t] && (it->t ^ fa))
		dfs(it->t, u, len + it->v);
}

void cal(int u, bool fg, int len) {
	cnt = 0;
	dfs(u, 0, len);
	for (int i = 0; i < cnt; ++i)
	  D[i] = (point) {0, dis[d[i].x] - d[i].y, id[d[i].x]};
	sort(D, D + cnt);
	for (int i = 0, j; i < cnt; ++i) {
		j = lower_bound(D, D + cnt, (point){0, d[i].y, d[i].x}) - D;
		fg ? ans[d[i].x] += j : ans[d[i].x] -= j;
	}
}

void Work(int u, int sz) {
	SZ = sz;
	grt(u, rt = 0);
	u = rt;
	vis[u] = true;
	cal(u, true, 0);
	FOR(u) if (!vis[it->t]) {
		cal(it->t, false, it->v);
		Work(it->t, ::sz[it->t] > ::sz[u] ? sz - ::sz[u] : ::sz[it->t]);
	}
}

int main() {
	int n, u, v, w, i, ans;
	f[0] = inf;
	while (scanf("%d", &n) != EOF) {
		ce = me;
		for (i = 1; i <= n; ++i) {
			g[i] = NULL;
			dis[i] = inf;
			vis[i] = 0;
			::ans[i] = 0;
		}
		for (i = 1; i < n; ++i) {
			scanf("%d%d%d", &u, &v, &w);
			adde(u, v, w);
			adde(v, u, w);
		}
		for (i = 1; i <= n; ++i) {
			scanf("%d", &u);
			flag[i] = u;
		}
		dijstra(n);
		Work(1, n);
		ans = -inf;
		for (i = 1; i <= n; ++i)
		  if (ans < ::ans[i])
			ans = ::ans[i];
		printf("%d\n", ans);
	}
	return 0;
}
