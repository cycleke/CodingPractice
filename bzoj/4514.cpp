#include <queue>
#include <cstdio>
#include <cstring>
#include <algorithm>

const int maxn(215), inf(0x3f3f3f3f);

inline int fast_pow(int a, int b, int mod) {
	static int r;
	for (r = 1; b; b >>= 1, a = 1ll * a * a % mod)
		if (b & 1) r = 1ll * r * a % mod;
	return r;
}

inline bool is_prime(const int &x) {
	static const int p[] = {2, 3, 5, 7, 11, 13, 998244353};

	for (int i = 0; i < 7; ++i) {
		if (x == p[i])
			return true;
		if (x % p[i] == 0)
			return false;
		if (fast_pow(p[i], x - 1, x) ^ 1)
			return false;
	}

	return true;
}

struct node {
	int a, b, c;
} a[maxn];

inline bool operator < (const node &x, const node &y) {
	return x.a < y.a;
}

struct edge {
	int to, cap, flow, nxt;
	long long cost;
} e[maxn * maxn * 10];

int g[maxn], cnt;
bool inq[maxn], col[maxn];

inline void add_edge(int u, int v, int cap, long long cost) {
	e[cnt] = (edge) {v, cap, 0, g[u], cost};
	g[u] = cnt++;
	e[cnt] = (edge) {u,   0, 0, g[v], -cost};
	g[v] = cnt++;
}


inline void EK(int s, int t, const int &n, int &max_flow, long long &min_cost) {

	min_cost = max_flow = 0;

	while (true) {
		static long long dis[maxn];
		static int from[maxn], flow[maxn];
		memset(from, -1, n * sizeof(int));
		memset(flow,  0, n * sizeof(int));
		memset(dis, 63, n * sizeof(long long));

		static std::queue<int> q;
		dis[s] = 0;
		flow[s] = inf;
		q.push(s);

		while (!q.empty()) {
			int u = q.front();
			q.pop();
			inq[u] = false;
			for (int i = g[u]; ~i; i = e[i].nxt)
				if (e[i].flow < e[i].cap && dis[e[i].to] > dis[u] + e[i].cost){
					dis[e[i].to] = dis[u] + e[i].cost;
					from[e[i].to] = i;
					flow[e[i].to] = std::min(flow[u], e[i].cap - e[i].flow);
					if (!inq[e[i].to]) {
						inq[e[i].to] = true;
						q.push(e[i].to);
					}
				}
		}

		if (dis[t] >= 0x3f3f3f3f3f3f3f3fll) break;

		for (int i = from[t]; ~i; i = from[e[i ^ 1].to]) {
			e[i].flow += flow[t];
			e[i ^ 1].flow -= flow[t];
		}

		max_flow += flow[t];
		min_cost += flow[t] * dis[t];

	}

}

inline bool check(const int &mid, const int &n) {

	for (int i = 0; i < n; ++i) {
		for (int j = g[i]; ~j; j = e[j].nxt)
			e[j].flow = 0;
	}

	e[cnt - 2].cap = mid;
	static int flow;
	static long long min_cost;
	EK(n - 1, n - 2, n, flow, min_cost);
	return min_cost <= 0;
}

inline int solve(const int &n) {
	e[cnt - 2].cap = inf;
	int flow;
	long long min_cost;
	EK(n - 1, n - 2, n, flow, min_cost);

	int l = 0, r = flow, mid;

	while (l <= r) {
		mid = (l + r) >> 1;
		if (check(mid, n))
			l = mid + 1;
		else
			r = mid - 1;
	}

	return l - 1;

}

int main() {

	//freopen("4514.in", "r", stdin);

	int n;
	scanf("%d", &n);

	for (int i = 0; i < n; ++i) scanf("%d", &a[i].a);
	for (int i = 0; i < n; ++i) scanf("%d", &a[i].b);
	for (int i = 0; i < n; ++i) scanf("%d", &a[i].c);

	std::sort(a, a + n);

	static bool match[maxn][maxn];

	memset(g, -1, sizeof g);

	for (int i = 0; i < n; ++i)
		for (int j = 0; j < i; ++j)
			if (a[i].a % a[j].a == 0 && is_prime(a[i].a / a[j].a)) {
				match[i][j] = true;
				add_edge(i, j, 0, 0);
			}

	for (int i = 0; i < n; ++i)
		if (!inq[i]) {
			static std::queue<int> q;
			q.push(i);
			col[i] = true;
			while (!q.empty()) {
				int u = q.front();
				q.pop();
				for (int i = g[u]; ~i; i = e[i].nxt)
					if (!inq[e[i].to]) {
						q.push(e[i].to);
						inq[e[i].to] = true;
						col[e[i].to] = col[u] ^ true;
					}
			}
		}

	memset(g, -1, sizeof g);
	memset(inq, 0, sizeof inq);

	cnt = 0;
	int s = n, t = n + 1, ss = n + 2;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < i; ++j)
			if (match[i][j]) {
				if (col[i])
					add_edge(i, j, inf, -1ll * a[i].c * a[j].c);
				else
					add_edge(j, i, inf, -1ll * a[i].c * a[j].c);
			}
		if (col[i])
			add_edge(s, i, a[i].b, 0);
		else
			add_edge(i, t, a[i].b, 0);
	}

	add_edge(ss, s, 0, 0);

	printf("%d\n", solve(n + 3));

	return 0;
}
