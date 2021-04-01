#include <queue>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 100007, K = 51;

struct edge {
	int to, cost;
	edge *next;
};

int n, m, k, p;
edge pool[N << 2], *cp, *g1[N], *g2[N];
int dp[N][K], d1[N], d2[N];
bool mark[N][K];

//input
const int buffer_size = (1 << 16) ^ 1;
char buffer[buffer_size], *cbuf(buffer), *ebuf(buffer);
inline char get_char() {
	if (cbuf == ebuf) {
		cbuf = buffer;
		ebuf = buffer + fread(buffer, 1, buffer_size, stdin);
	}
	return (cbuf == ebuf) ? EOF : *cbuf++;
}
inline void getusint(int &a) {
	register char c;
	while (c = get_char(), c < '0');
	a = c - '0';
	while (c = get_char(), '-' < c)
		a = (a << 3) + (a << 1) + c - '0';
}

inline void add_edge(edge **g, int u, int v, int w);
inline void Dijstra(int *d, edge **g, int source);
bool dfs(int u, int x);

int main() {
	freopen("park.in", "r", stdin);
	freopen("park.out", "w", stdout);
	int _;
	getusint(_);
	while (_--) {
		cp = pool;
		getusint(n);
		getusint(m);
		getusint(k);
		getusint(p);
		for (register int i = 1; i <= n; ++i) {
			g1[i] = g2[i] = NULL;
			d1[i] = d2[i] = 0x7f7f7f7f;
			for (register int j = 0; j <= k; ++j) {
				dp[i][j] = -1;
				mark[i][j] = false;
			}
		}
		while (m--) {
			int u, v, w;
			getusint(u);
			getusint(v);
			getusint(w);
			add_edge(g1, u, v, w);
			add_edge(g2, v, u, w);
		}
		Dijstra(d1, g1, 1);
		Dijstra(d2, g2, n);
		if (dfs(1, 0))
			puts("-1");
		else
			printf("%d\n", dp[1][0]);
	}
	return 0;
}


inline void add_edge(edge **g, int u, int v, int w) {
	*cp = (edge) {v, w, g[u]};
	g[u] = cp++;
}

std::pair < int, int > Array[N << 1];
inline void Dijstra(int *d, edge **g, int source) {
	using namespace std;
	pair < int, int > t, *top = Array, *end = Array;
	*end++ = make_pair(d[source] = 0, source);
	while (top < end) {
		pop_heap(top, end);
		t = *(--end);
		register int u = t.second;
		if (d[u] + t.first != 0)
			continue;
		for (edge *it = g[u]; it != NULL; it = it->next)
			if (d[it->to] > d[u] + it->cost) {
				*end++ = make_pair(-(d[it->to] = d[u] + it->cost), it->to);
				push_heap(top, end);
			}
	}
}

bool dfs(int u, int x) {
	if (mark[u][x])
		return true;
	if (dp[u][x] != -1)
		return false;
	mark[u][x] = true;
	dp[u][x] = (u == n) ? 1 : 0;
	for (edge *it = g1[u]; it != NULL; it = it->next) {
		int delta = d1[u] + it->cost + x - d1[it->to];
		if (delta <= k && d1[u] + x + it->cost + d2[it->to] - d2[1] <= k) {
			if (dfs(it->to, delta))
				return true;
			dp[u][x] += dp[it->to][delta];
			if (dp[u][x] >= p)
				dp[u][x] -= p;
		}
	}
	return mark[u][x] = false;
}
