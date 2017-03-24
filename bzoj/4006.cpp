#include <queue>
#include <cstdio>
#include <cstring>
#include <algorithm>

const int maxn(1005), maxm(3005), maxp(11), maxstatus(1025), inf(0x3f3f3f3f);

std::queue<int> q;

struct edge {
	int to, cost;
	edge *nxt;
} edge_mset[maxm * 2 + 10], *g[maxn], *cedge = edge_mset;

inline void add_edge(int u, int v, int w) {
	*cedge = (edge) {v, w, g[u]};
	g[u] = cedge++;
}

bool inq[maxn]; 
int contian[maxp], val[maxn], n, m, p;
int dis[maxstatus][maxn], dp[maxstatus];

inline void spfa(int status) {
	int *d = dis[status];
	while (!q.empty()) {
		static int p, v;
		static edge *it;
		p = q.front();
		q.pop();
		inq[p] = false;
		for (it = g[p]; it; it = it->nxt) {
			v = it->to;
			if (d[v] <= d[p] + it->cost)
				continue;
			d[v] = d[p] + it->cost;
			if (!inq[v]) 
				inq[v] = true, q.push(v);
		}
	}
}

inline bool check(int status) {
	for (register int i = 1; i <= p; ++i)
		if ((status & contian[i]) && (status & contian[i]) != contian[i])
			return false;
		return true;
}

int main() {
	int u, v, w, c, d;
	scanf("%d%d%d", &n, &m, &p);
	memset(dis, 63, sizeof dis);
	while (m--) {
		scanf("%d%d%d", &u, &v, &w);
		add_edge(u, v, w);
		add_edge(v, u, w);
	}
	for (register int i = 1; i <= p; ++i) {
		scanf("%d%d", &c, &d);
		contian[c] ^= 1 << (i - 1);
		val[d] = 1 << (i - 1);
		dis[val[d]][d] = 0;
	}
	int all = (1 << p);
	for (register int status = 1; status ^ all; ++status) {
		for (register int i = 1; i <= n; ++i) {
			for (register int s = (status - 1) & status; s; s = (s - 1) & status)
				if (dis[status][i] > dis[s][i] + dis[status ^ s][i])
					dis[status][i] = dis[s][i] + dis[status ^ s][i];
				if (dis[status][i] ^ inf) {
					inq[i] = true;
					q.push(i);
				}
		}
		spfa(status);
	}
	memset(dp, 63, sizeof dp);
	for (register int i = 1; i ^ all; ++i)
		for (register int j = 1; j <= n; ++j)
			if (dp[i] > dis[i][j]) dp[i] = dis[i][j];

	for (register int i = 1; i ^ all; ++i) if (check(i))
		for (register int j = (i - 1) & i; j; j = (j - 1) & i)
			if (check(j) && (dp[i] > dp[j] + dp[i ^ j])) dp[i] = dp[j] + dp[i ^ j];
	printf("%d\n", dp[all - 1]);
	return 0;
}