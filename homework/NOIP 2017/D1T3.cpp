#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <queue>
#include <algorithm>

using namespace std;

const int inf = 0x3f3f3f3f;
const int N = 100005, M = 200005, K = 55;

int n, m, k, p;
struct Edge {
	int to, cost;
	Edge *nxt;
} EdgeMemory[M * 3], *CEdge, *g[N], *xg[N], *ng[N];
int d1[N], d2[N], dp[N][K];
int degree[N];

void Read() {
	scanf("%d %d %d %d", &n, &m, &k, &p);
	for (int i = 1; i <= n; ++i) {
		degree[i] = 0;
		d1[i] = d2[i] = inf;
		g[i] = xg[i] = ng[i] = NULL;
	}
	CEdge = EdgeMemory;
	for (int step = 0; step < m; ++step) {
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);
		*CEdge = (Edge) {b, c, g[a]};
		g[a] = CEdge++;
		*CEdge = (Edge) {a, c, xg[b]};
		xg[b] = CEdge++;
	}
}
void ADD(int &a, int b) {
	a += b;
	if (a >= p) a-= p;
}

int dfs(int s, int dis) {
	if (dp[s][dis] != -1)
		return dp[s][dis];
	int &x = dp[s][dis];
	x = 0;
	for (Edge *it = ng[s]; it != NULL; it = it->nxt) {
		int to = it->to;
		int cost = it->cost;
		if (cost > dis)
			continue;
		ADD(x, dfs(to, dis - cost));
	}
	return x;
}

bool CheckInf() {
	queue < int > q;
	int count = n;
	for (int i = 1; i <= n; ++i)
		if (degree[i] == 0) {
			--count;
			q.push(i);
		}
	while (!q.empty()) {
		int s = q.front();
		q.pop();
		for (Edge *it = ng[s]; it != NULL; it = it->nxt) {
			--degree[it->to];
			if (degree[it->to] == 0) {
				--count;
				q.push(it->to);
			}
		}
	}
	return count != 0;
}

void Dijstra(int s, int *d, Edge *g[N]) {
	priority_queue < pair < int, int > > heap;
	d[s] = 0;
	heap.push(make_pair(0, s));
	while (!heap.empty()) {
		int s = heap.top().second;
		int dis = -heap.top().first;
		heap.pop();
		if (dis != d[s]) continue;
		for (Edge *it = g[s]; it != NULL; it = it->nxt) {
			int to = it->to;
			if (d[to] > dis + it->cost) {
				d[to] = dis + it->cost;
				heap.push(make_pair(-d[to], to));
			}
		}
	}
}

int Work() {
	Dijstra(1, d1, g);
	Dijstra(n, d2, xg);
	for (int i = 1; i <= n; ++i) {
		for (Edge *it = g[i]; it != NULL; it = it->nxt)
			if (d1[i] + it->cost + d2[it->to] <= d1[n] + k) {
				*CEdge = (Edge) {i, it->cost - d1[it->to] + d1[i], ng[it->to]};
				if (CEdge->cost == 0) ++degree[i];
				ng[it->to] = CEdge++;
			}
	}
	if (CheckInf())
		return -1;

	int res = 0;
	memset(dp, -1, sizeof dp);
	dp[1][0] = 1;
	for (int i = 0; i <= k; ++i) {
		ADD(res, dfs(n, i));
	}
	return res;
}

int main() {
	int _;
	scanf("%d", &_);
	while (_--) {
		Read();
		printf("%d\n", Work());
	}
	return 0;
}
