#include <queue>
#include <stack>
#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

struct edge {
	int u, v, w;
	edge(int u, int v, int w) :
		u(u), v(v), w(w) {}
};


struct eg {
	int to, w;
	eg(int to, int w) :
		to(to), w(w) {}
};

const int MaxN = 2e5 + 9;
typedef int arr[MaxN];
typedef vector<eg>::iterator veit;
int dfs_clock, scc_cnt;
arr dis, bel, dfn, low, dist, tot, fa[15], dep;

bool mark[MaxN];
vector<eg> g[MaxN], G[MaxN];
stack<edge> s;
queue<int> q;

inline void build_scc(int A, int B) {
	static edge e(0, 0, 0);
	static int k, w;
	++scc_cnt;
	mark[A] = true;
	while ((s.top().u ^ A) && (s.top().v ^ B)) {
		e = s.top();
		s.pop();
		bel[e.u] = scc_cnt;
		tot[scc_cnt] += e.w;
		dist[e.u] = dist[e.v] + e.w;
		q.push(e.u);
	}
	tot[scc_cnt] += s.top().w;
	s.pop();
	if (q.empty())
		G[A].push_back(eg(B, tot[scc_cnt]));
	while (!q.empty()) {
		k = q.front();
		q.pop();
		w = min(dist[k], tot[scc_cnt] - dist[k]);
		G[A].push_back(eg(k, w));
	}
}

void dfs1(int u, int father) {
	dfn[u] = low[u] = ++dfs_clock;
	for (veit it = g[u].begin(); it != g[u].end(); ++it) {
		if (!dfn[it->to]) {
			s.push(edge(u, it->to, it->w));
			dfs1(it->to, u);
			if (dfn[u] <= low[it->to])
				build_scc(u, it->to);
			if (low[it->to] < low[u])
				low[u] = low[it->to];
		} else if ((it->to ^ father) && dfn[it->to] < low[u]) {
			low[u] = dfn[it->to];
			s.push(edge(u, it->to, it->w));
		}
	}
}

void dfs2(int u) {
	for (int i = 1; fa[i][u] = fa[i - 1][fa[i - 1][u]]; ++i);
	for (veit it = G[u].begin(); it != G[u].end(); ++it) {
		dep[it->to] = dep[u] + 1;
		fa[0][it->to] = u;
		dis[it->to] = dis[u] + it->w;
		dfs2(it->to);
	}
}

inline int Lca(int u, int v, int &fu, int &fv) {
	fu = fv = 0;
	if (dep[u] < dep[v])
		swap(u, v);
	for (int i = 0, j = dep[u] - dep[v]; j; ++i, j >>= 1)
		if (j & 1) u = fa[i][u];
	if (u == v)
		return u;
	for (int i = 14; ~i; --i)
		if (fa[i][u] ^ fa[i][v]) {
			u = fa[i][u];
			v = fa[i][v];
		}
	fu = u, fv = v;
	return fa[0][u];
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("t.in", "r", stdin);
#endif
	int n, m, q, u, v, w, lca, fu, fv;
	scanf("%d%d%d", &n, &m, &q);
	while (m--) {
		scanf("%d%d%d", &u, &v, &w);
		g[u].push_back(eg(v, w));
		g[v].push_back(eg(u, w));
	}
	dfs1(1, 0);
	dfs2(1);
	while (q--) {
		scanf("%d%d", &u, &v);
		lca = Lca(u, v, fu, fv);
		if (mark[lca] && bel[fu] && bel[fu] == bel[fv]) {
			w = abs(dist[fu] - dist[fv]);
			w = min(w, tot[bel[fu]] - w);
			printf("%d\n", dis[u] + dis[v] - dis[fu] - dis[fv] + w);
		} else
			printf("%d\n", dis[u] + dis[v] - 2 * dis[lca]);
	}
	return 0;
}
