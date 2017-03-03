#include <cstdio>
#include <cstring>

const int MaxN = 5e3 + 5, MaxM = 1005, inf = 0x3f3f3f3f;
typedef int arr[MaxM + MaxN];

struct edge {
	int to, cap, cost, nxt;
} e[(MaxN + MaxM) * 10];

int S, T, edgecnt, ans, que[(MaxM + MaxN) * 10], _vis;
arr head, dis, win, lose, C, D, remin, vis;
bool inq[MaxN + MaxM];

inline void add_edge(int u, int v, int cap, int cost) {
	e[edgecnt] = (edge) {v, cap, cost, head[u]}, head[u] = edgecnt++;
	e[edgecnt] = (edge) {u,  0, -cost, head[v]}, head[v] = edgecnt++;
}

inline bool spfa() {
	static int i, u, v, *l, *r;
	for (i = S; i < T; ++i)
	  dis[i] = inf, inq[i] = false;
	dis[T] = 0;
	l = r = que;
	*r++ = T;
	while (l < r) {
		u = *l++;
		inq[u] = false;
		for (i = head[u]; ~i; i = e[i].nxt) {
			v = e[i].to;
			if (e[i ^ 1].cap && dis[u] + e[i ^ 1].cost < dis[v]) {
				dis[v] = dis[u] + e[i ^ 1].cost;
				if (!inq[v]) {
					*r++ = v;
					inq[v] = true;
				}
			}
		}
	}
	return dis[S] ^ inf;
}

int dfs(int u, int flow) {
	vis[u] = _vis;
	if (u == T)
	  return flow;
	int ret = 0, t, v;
	for (int i = head[u]; ~i; i = e[i].nxt) {
		v = e[i].to;
		if ((vis[v] ^ _vis) && e[i].cap && dis[u] == dis[v] + e[i].cost) {
			t = dfs(v, flow < e[i].cap ? flow : e[i].cap);
			e[i].cap -= t;
			e[i ^ 1].cap += t;
			ret += t;
			flow -= t;
			ans += t * e[i].cost;
			if (!flow)
			  return ret;
		}
	}
	return ret;
}

inline void zkw() {
	while (spfa()) {
		vis[T] = ++_vis;
		//puts("1");
		//printf("%d\n", ans);
		while (vis[T] >= _vis) {
			++_vis;
			dfs(S, inf);
		}
	}
}

int main() {
	//freopen("t.in", "r", stdin);
	int n, m, i, x, y;
	scanf("%d%d", &n, &m);
	S = 0, T = n + m + 1;
	memset(head, -1, sizeof head);
	for (i = 1; i <= n; ++i) scanf("%d%d%d%d", win + i, lose + i, C + i, D + i);
	for (i = 1; i <= m; ++i) {
		scanf("%d%d", &x, &y);
		++remin[x];
		++remin[y];
		add_edge(S, i, 1, 0);
		add_edge(i, x + m, 1, 0);
		add_edge(i, y + m, 1, 0);
	}
	for (i = 1; i <= n; ++i) {
		lose[i] += remin[i];
		ans += win[i] * win[i] * C[i] + lose[i] * lose[i] * D[i];
		for (x = 1; x <= remin[i]; ++x) {
			add_edge(i + m, T, 1, 2 * (win[i] * C[i] - lose[i] * D[i]) + C[i] + D[i]);
			++win[i], --lose[i];
		}
	}
	//printf("%d\n", ans);
	zkw();
	printf("%d\n", ans);
	return 0;
}
