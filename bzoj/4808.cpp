#include <queue>
#include <cstdio>
#include <cstring>

const int dx[]={-1, -1, 1, 1, -2, -2, 2, 2};
const int dy[]={2, -2, 2, -2, 1, -1, 1, -1};

const int maxn(202), maxp(200 * 200 + 15), maxdep(200 * 200 + 10);

int a[maxn][maxn], d[maxp], dt[maxp], g[maxp], la[maxp], cnt, tot, s, t;

struct edge {
	int to, cap, nxt;
} e[500010];

inline void add_edge(int u, int v, int cap) {
	e[cnt] = (edge) {v, cap, g[u]};
	g[u] = cnt++;
	e[cnt] = (edge) {u,   0, g[v]};
	g[v] = cnt++;
}

int dfs(int u, int flow) {
	if (u == t || flow == 0) return flow;
	int ret = 0, tmp;
	for (int &i = la[u]; ~i; i = e[i].nxt)
		if (e[i].cap && d[u] == d[e[i].to] + 1) {
			tmp = dfs(e[i].to, e[i].cap < flow ? e[i].cap : flow);
			ret += tmp;
			flow -= tmp;
			e[i].cap -= tmp;
			e[i ^ 1].cap += tmp;
			if (!flow || d[s] >= maxdep)
				return ret;
		}
	la[u] = g[u];
	if (!--dt[d[u]]) d[s] = maxdep;
	++dt[++d[u]];
	return ret;
}

int main() {

	freopen("t.in", "r", stdin);

	int n, m, x, ans = 0;
	scanf("%d%d", &n, &m);
	s = tot++, t = tot++;
	memset(g, -1, sizeof g);
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j) {
			scanf("%d", &x);
			if (!x) a[i][j] = tot++, ++ans;
		}

	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j)
			if (a[i][j]) {
				if ((i ^ j) & 1) {
					add_edge(s, a[i][j], 1);
					for (int d = 0; d < 8; ++d) {
						int _i = i + dx[d];
						int _j = j + dy[d];
						if (_i >= 0 && _j >= 0 && _i < n && _j < m && a[_i][_j])
							add_edge(a[i][j], a[_i][_j], 0x3f3f3f3f);
					}
				} else
					add_edge(a[i][j], t, 1);
			}

	memset(d, -1, sizeof d);

	static std::queue<int> q;

	q.push(t);
	d[t] = 0;

	while (!q.empty()) {
		int u = q.front();
		q.pop();
		for (int i = la[u] = g[u]; ~i; i = e[i].nxt)
			if (e[i].cap == 0 && d[e[i].to] < 0) {
				d[e[i].to] = d[u] + 1;
				q.push(e[i].to);
			}
	}

	for (int i = 0; i < tot; ++i) ++dt[d[i]];

	while (d[s] < maxdep) ans -= dfs(s, 0x3f3f3f3f);

	printf("%d\n", ans);

	return 0;
}
