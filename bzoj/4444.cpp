#include <cstdio>
#include <algorithm>

const int MaxN = 2e5 + 7;
int C[MaxN], D[MaxN], ha[MaxN << 1], f[MaxN << 3], ans[MaxN << 3], _ans, m;

struct edge {
	int to;
	edge *nxt;
} edge_mset[MaxN << 3], *g[MaxN << 3];

inline void add_edge(int from, int to) {
	static edge *cedge = edge_mset;
	*cedge = (edge) {to, g[from]};
	g[from] = cedge++;
}

inline void cmax(int &a, const int &b) {
	if (a < b) a = b;
}

inline void dfs(int u) {
	static int stk[MaxN << 3], *top = stk;
	*++top = u;
	if (u <= ::m)
		for (register int i = _ans; ; ++i)
			if (top[-i] >= u + ::m) {
				ans[u] = i;
				break;
			}
	for (edge *it = ::g[u]; it; it = it->nxt)
		dfs(it->to);
	--top;
}

int main() {
	int n, m = 0;
	scanf("%d%*d", &n);
	for (register int i = 0; i < n; ++i) {
		scanf("%d%d", C + i, D + i);
		ha[m++] = C[i];
		ha[m++] = D[i];
	}
	::m = m;
	std::sort(ha, ha + m);
	for (register int i = 0, s, t; i < n; ++i) {
		C[i] = s = std::lower_bound(ha, ha + m, C[i]) - ha + 1;
		t = std::lower_bound(ha, ha + m, D[i]) - ha + 1;
		if (s < t)
			cmax(f[s], t), cmax(f[s + m], t + m);
		else
			cmax(f[1], t), cmax(f[s], t + m), cmax(f[s + m], m << 1);
	}
	for (register int i = 1; i < (m << 1); ++i) {
		cmax(f[i], f[i - 1]);
		add_edge(f[i], i);
	}
	_ans = -1;
	for (register int i = 1; i <= m; i = f[i]) ++_ans;
	dfs(m << 1);
	for (register int i = 0; i < n; ++i)
		printf("%d ", ans[C[i]]);
	return 0;
}
