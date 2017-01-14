#include <queue>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define inf 0x3f3f3f3f
typedef int edge[400003], vert[1003];

edge to, nt, c, w;
vert hd, la, d, dt;
int n, m, tote, k;

void adde(int x, int y, int z, int v) {
	to[tote] = y; nt[tote] = hd[x]; 
	c[tote] = z; w[tote] = v;
	hd[x] = tote++;
}

int dfs(int u, int flow) {
	if (u == n || !flow) return flow;
	int ret = 0, tmp;
	for (int &i = la[u], v; ~i; i = nt[i]) 
	if (0 < c[i] && d[v = to[i]] + 1 == d[u]) {
		tmp = dfs(v, min(flow, c[i]));
		ret += tmp, flow -= tmp;
		c[i] -= tmp, c[i^1] += tmp;
		if (!flow || d[1] >= n) return ret;
	}
	la[u] = hd[u];
	if (!(--dt[d[u]])) d[1] = n;
	++dt[++d[u]];
	return ret;
}

int SAP() {
	for (int i = 1; i <= n; ++i) la[i] = hd[i];
	int ans = 0; d[0] = n;
	while (d[1] < n) ans += dfs(1, inf);
	return ans;
}

vert from, fromedge;
bool inq[1003];

bool SPFA() {
	static queue<int> q;
	static int i, u, dis, v;
	memset(d, 63, sizeof d);
	d[0] = 0;
	q.push(0);
	while (!q.empty()) {
		u = q.front();
		q.pop();
		dis = d[u];
		inq[u] = false;
		for (i = hd[u]; i; i = nt[i]) 
			if (c[i] > 0 && d[v = to[i]] > dis + w[i]) {
				d[v] = dis + w[i];
				from[v] = u;
				fromedge[v] = i;
				if (!inq[v]) inq[v] = 1, q.push(v);
			}
	}
	return d[n] < inf;
}

int mcf() {
	static int f, p, ans;
	f = inf, p = n;
	for (; p; p = from[p])
		f = min(f, c[fromedge[p]]);
	for (ans = 0, p = n; p; p = from[p]) {
		ans += f * w[fromedge[p]];
		c[fromedge[p]] -= f;
		c[fromedge[p]^1] += f;
	}
	return ans;
}

int expand() {
	memset(hd, -1, sizeof hd);
	//puts("");
	int u, v, t, i, ret;
	for (i = tote - 1; ~i; i -= 2) {
		u = to[i], v = to[i^1];
		if (c[i^1] > 0) {
			adde(u, v, c[i^1], 0);
			adde(v, u, c[i], 0);
		}
		adde(u, v, inf, w[i^1]);
		adde(v, u, 0, -w[i^1]);
	//	printf("%3d -> %3d c = %3d w = %3d\n", u, v, c[i^1], w[i^1]);
	}
	adde(0, 1, k, 0);
	adde(1, 0, 0, 0);
	for (ret = 0; SPFA();) ret += mcf();
	return ret;
}

int main() {
	//freopen("t.in", "r", stdin);
	//freopen("t.out", "w", stdout);
	scanf("%d%d%d", &n, &m, &k);
	memset(hd, -1, sizeof hd);
	for (int x, y, z, v; m; --m) {
		scanf("%d%d%d%d", &x, &y, &z, &v);
		adde(x, y, z, v);
		adde(y, x, 0, 0);
	}
	printf("%d ", SAP());
	printf("%d\n", expand());
	return 0;
}
