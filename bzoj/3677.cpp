#include <cstdio>
#include <algorithm>
using namespace std;

struct FI {
	char b[5 << 20], *s;
	FI() : s(b) {
		b[fread(b, 1, 5 << 20, stdin)] = 0;
	}
	inline void gi(int &a) {
		while (*s < 48) ++s;
		a = *s++ - 48;
		while (47 < *s) a = (a << 3) + (a << 1) + *s++ - 48;
	}
} io;

const int MaxN = 200005, inf = 0x3f3f3f3f;

struct edge {
	int to, weight;
	edge *nxt;
} edge_mset[MaxN << 1], *cedge = edge_mset, *g[MaxN];

inline void add_edge(int u, int v, int w) {
	*cedge = (edge) {v, w, g[u]};
	g[u] = cedge++;
}

inline void cmax(int &a, const int &b) {
    if (a < b) a = b;
}

int dp[MaxN][2], mx[MaxN][2], cost[MaxN], fa[MaxN], ans;

inline void dfs(int u) {
    int v, temp;
    mx[u][0] = mx[u][1] = -inf;
    for (edge *it = g[u]; it; it = it->nxt)
        if ((v = it->to) ^ fa[u]) {
            fa[v] = u;
            cost[v] = it->weight;
            dfs(v);
            temp = max(it->weight + dp[v][1], dp[v][0]);
            dp[u][0] += temp;
            temp = it->weight + dp[v][0] - temp;
            if (temp > mx[u][0])
                mx[u][1] = mx[u][0], mx[u][0] = temp;
            else if (temp > mx[u][1])
                mx[u][1] = temp;
        }
    dp[u][1] = dp[u][0] + mx[u][0];
}

inline void change_root(int u) {
    int m0 = mx[u][0], m1 = mx[u][1], dp0 = dp[u][0], dp1 = dp[u][1];
    if (u ^ 1) {
        int temp = max(cost[u] + dp[fa[u]][1], dp[fa[u]][0]);
        dp[u][0] += temp;
        temp = cost[u] + dp[fa[u]][0] - temp;
        if (temp > mx[u][0])
            mx[u][1] = mx[u][0], mx[u][0] = temp;
        else if (temp > mx[u][1])
            mx[u][1] = temp;
    }
    cmax(ans, dp[u][0]);
    int v, t0, t1, temp;
    for (edge *it = g[u]; it; it = it->nxt)
        if ((v = it->to) ^ fa[u]) {
            t0 = dp[u][0], t1 = dp[u][1];
            temp = max(it->weight + dp[v][1], dp[v][0]);
            dp[u][0] -= temp;
            temp = it->weight + dp[v][0] - temp;
            dp[u][1] = dp[u][0] + (temp == mx[u][0] ? mx[u][1] : mx[u][0]);
            change_root(v);
            dp[u][0] = t0;
            dp[u][1] = t1;
        }
    mx[u][0] = m0;
    mx[u][1] = m1;
    dp[u][0] = dp0;
    dp[u][1] = dp1;
}

int main() {
	int n, u, v, w;
	io.gi(n);
	for (register int i = 1; i < n; ++i) {
		io.gi(u), io.gi(v), io.gi(w);
		add_edge(u, v, w);
		add_edge(v, u, w);
	}
    dfs(1);
    change_root(1);
    printf("%d\n", ans);
	return 0;
}
