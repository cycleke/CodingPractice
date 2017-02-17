#include <cstdio>

#define N 200003
#define Pri_Num 18000
#define inf 0x3fffffff
typedef int arr[Pri_Num];

int ans, n, cnt, T;
arr dis, prime, q, g;
bool mark[Pri_Num];
struct edge {
	int t, n, v, c;
}e[N];

void Link(int u, int v, int w, int c) {
	e[cnt] = (edge) {v, g[u], w, c}; g[u] = cnt++;
	e[cnt] = (edge) {u, g[v], 0, -c}; g[v] = cnt++;
}

#define nxt(x) (++x >= Pri_Num ? x = 0 : x)

bool spfa() {
	static bool inq[Pri_Num];
	for (int i = 0; i < T; ++i) dis[i] = -inf;
	int head = 0, tail = 1, u, i;
	q[0] = T;
	dis[T] = 0;
	while (head ^ tail) {
		u = q[head];
		nxt(head);
		inq[u] = false;
		for (i = g[u]; ~i; i = e[i].n) 
		  if (e[i ^ 1].v && dis[e[i].t] + e[i].c < dis[u]) {
			dis[e[i].t] = dis[u] - e[i].c;
			if (!inq[e[i].t]) {
				q[tail] = e[i].t;
				nxt(tail);
				inq[e[i].t] = true;
			}
		  }
	}
	return 0 < dis[0];
}

int V(int n, int x) {
	int r = x;
	while ((long long)r * x <= n)
	  r *= x;
	return r;
}

void Build() {
	static bool vis[N];
	static arr q1, q2;
	int tot = 0, *t1 = q1, *t2 = q2;
	g[0] = g[1] = -1;
	for (int i = 2; i <= n; ++i) {
		if (!vis[i])
		  prime[++tot] = i;
		for (int j = 1, t; (t = prime[j] * i) <= n; ++j) {
			vis[t] = true;
			if (!(i % prime[j]))
			  break;
		}
		g[i] = -1;
	}
	T = tot + 1;
	for (int i = 1; i <= tot; ++i) {
		int t = prime[i];
		if (2 * t > n) {
			ans += t;
			continue;
		}
		if ((long long)t * t <= n) {
			Link(0, i, 1, 0);
			ans += V(n, t);
			*t1++ = i;
		} else {
			Link(i, T, 1, 0);
			ans += t;
			*t2++ = i;
		}
	}
	for (int *i1 = q1; i1 < t1; ++i1)
	  for (int *i2 = q2; i2 < t2; ++i2) {
		  int a = prime[*i1], b = prime[*i2];
		  if (a * b <= n) {
			  int t = V(n / b, a) * b;
			  if (t > V(n, a) + b)
				Link(*i1, *i2, 1, t - V(n, a) - b);
		  } else break;
	  }
}

int min(const int &a, const int &b) {
	return a < b ? a : b;
}

int dfs(int u, int flow) {
	mark[u] = true;
	if (u == T)
	  return flow;
	int w, ret = 0;
	for (int i = g[u]; ~i; i = e[i].n) 
	  if (e[i].v && dis[u] - e[i].c == dis[e[i].t] && !mark[e[i].t]) {
		w = dfs(e[i].t, min(e[i].v, flow));
		e[i].v -= w; e[i ^ 1].v += w;
		ret += w, flow -= w;
		ans += e[i].c * w;
		if (!flow) return ret;
	  }
	return ret;
}

void zkw() {
	while (spfa()) {
		for (int i = 0; i < T; ++i) mark[i] = 0;
		mark[T] = 1;
		while (mark[T])
		  mark[T] = 0, dfs(0, inf);
	}
}

int main() {
	scanf("%d", &n);
	Build();
	zkw();
	printf("%d\n", ans + 1);
	return 0;
}
