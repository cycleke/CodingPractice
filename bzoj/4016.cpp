#include <queue>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;
const int N = 30010;
typedef pair<int, int>pii;
vector< pii > G[N];
int n, m, mv, cnt, rt, siz, K, frt, s[N], f[2][N], g[2][N], d[N];
bool vis[N];
struct edge{int to, w; edge *nt;} *hd[N], ME[N << 1], *ce = ME;
void adde(int a, int b, int c) {
	ce->to = b;
	ce->nt = hd[a];
	ce->w = c;
	hd[a] = ce++;
}
priority_queue< pii, vector < pii >, greater < pii > >heap;
void dijstra() {
	memset(d, 127, sizeof d);
	heap.push(make_pair(d[1] = 0, 1));
	int u, dis, w, v, i;
	while (!heap.empty()) {
		u = heap.top().second;
		dis = heap.top().first;
		heap.pop();
		if (dis ^ d[u]) continue;
		sort(G[u].begin(), G[u].end());
		for (i = 0; i < G[u].size(); ++i) {
			v = G[u][i].first;
			w = G[u][i].second;
			if (d[v] > dis + w)
				heap.push(make_pair(d[v] = dis + w, v));
		}
	}
}
void build(int u) {
	int v, i;
	vis[u] = true;
	for (i = 0; i < G[u].size(); ++i)
		if (!vis[v = G[u][i].first] && d[v] == d[u] + G[u][i].second) {
			adde(v, u, G[u][i].second);
			adde(u, v, G[u][i].second);
			build(v);
		}
}
void grt(int u,int fa) {
	int mx = 0, v;
	s[u] = 1;
	for (edge*it = hd[u]; it; it = it->nt) {
		v = it->to;
		if (vis[v] || v == fa) continue;
		grt(v, u);
		s[u] += s[v];
		if (s[v] > mx) mx = s[v];
	}
	if (siz - mx > mx) mx = siz - mx;
	if (mx < frt) rt = u, frt = mx;
}
void dfs(int u,int fa, int dep) {
	if (dep > K) return;
	if (d[u] > g[0][dep]) g[0][dep] = d[u], g[1][dep] = 0;
	if (d[u] >= g[0][dep]) ++g[1][dep];
	int v;
	for (edge*it = hd[u]; it; it = it->nt) {
		v = it->to;
		if (vis[v] || v == fa) continue;
		d[v] = d[u] + it->w;
		dfs(v, u, dep + 1);
	}
}
void solve(int u) {
	int v, i, j;
	vis[u] = true;
	f[0][0] = 0;
	f[1][0] = 1;
	for (edge*it = hd[u]; it; it = it->nt)
		if (!vis[it->to]) {
			v = it->to;
			d[v] = it->w;
			dfs(v, u, 1);
			for (j = 1; j <= K; ++j) {
				if (g[0][j] + f[0][K-j] > mv) mv = g[0][j] + f[0][K - j], cnt = 0;
				if (g[0][j] + f[0][K-j] >= mv)  cnt += g[1][j] * f[1][K-j];
			}
			for (j = 1; j <= K; ++j) {
				if (g[0][j] > f[0][j]) f[0][j] = g[0][j], f[1][j] = 0;
				if (g[0][j] >= f[0][j]) f[1][j] += g[1][j];
				g[0][j] = g[1][j] = 0;
			}
		}
	for (i = 0; i <= K; ++i) f[0][i] = f[1][i] = 0;
	for (edge*it = hd[u]; it; it = it->nt)
		if (!vis[it->to]){
			v = it->to;
			frt = siz = s[v];
			rt = 0;
			grt(v, u);
			if (s[v] > K) solve(rt);
		}
}
int main() {
	scanf("%d%d%d", &n, &m, &K);
	--K;
	for (int a, b, c; m; --m) {
		scanf("%d%d%d", &a, &b, &c);
		G[a].push_back(make_pair(b, c));
		G[b].push_back(make_pair(a, c));
	}
	dijstra();
	build(1);
	memset(vis, 0, sizeof vis);
	frt = siz = n;
	rt = 0;
	grt(1, 0);
	solve(rt);
	printf("%d %d\n", mv, cnt);
	return 0;
}
