#include <cstdio>
#include <cstring>

const int N = 12, FullStatus = (1 << 12) + 1, INF = 0x3f3f3f3f;

int g[N][N], f[FullStatus], d[N], ans, p[FullStatus], All;

inline int min(const int &a, const int &b) {
	return a < b ? a : b;
}

void dfs(int s) {
	int i, _s = All ^ s, ss = s;
	if (f[s] >= ans)
		return;
	if (s == All) {
		ans = f[s];
		return;
	}
	while (ss != 0) {
		i = ss & -ss;
		ss ^= i;
		i = p[i];
		int _ss = _s, j;
		while (_ss != 0) {
			j = _ss & -_ss;
			_ss ^= j;
			j = p[j];
			if (g[i][j] == INF)
				continue;
			//printf("%d %d %d\n", f[s ^ (1 << j)], f[s], d[i] * g[i][j]);
			if (f[s ^ (1 << j)] > f[s] + d[i] * g[i][j]) {
				int tmp = d[j];
				d[j] = d[i] + 1;
				f[s ^ (1 << j)] = f[s] + d[i] * g[i][j];
				dfs(s ^ (1 << j));
				d[j] = tmp;
			}
		}
	}
}

int main() {
	int n, m;
	memset(g, 63, sizeof(g));
	scanf("%d %d", &n, &m);
	for (int i = 0; i < m; ++i) {
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);
		--u, --v;
		g[v][u] = g[u][v] = min(g[u][v], w);
	}
	All = (1 << n) - 1;
	ans = INF;
	for (int i = 0; i < n; ++i) p[1 << i] = i;
	for (int i = 0; i < n; ++i) {
		memset(d, 63, sizeof(d));
		memset(f, 63, sizeof(f));
		d[i] = 1;
		f[1 << i] = 0;
		dfs(1 << i);
	}
	printf("%d\n", ans);
	return 0;
}
