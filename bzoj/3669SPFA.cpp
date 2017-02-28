#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MaxN = 50005, MaxM = 100005;
inline void gi(int &a) {
	static char c;
	do c = getchar(); while (c < '0');
	for (a = c - '0'; '-' < (c = getchar()); a = (a << 3) + (a << 1) + c - '0');
}
struct Link {
	int u, v, a, b;
} e[MaxM];
bool operator < (const Link &a, const Link &b) {
	return a.a < b.a;
}
struct edge {
	int to, v;
	edge *nxt;
} edge_mset[MaxM << 1], *cedge = edge_mset, *g[MaxN];
inline void add_edge(int u, int v, int w) {
	*cedge = (edge) { v, w, g[u]};
	g[u] = cedge++;
}
int d[MaxN], heap[MaxN], pos[MaxN], top;
inline void swn(int &a, int &b) {
	swap(a, b);
	swap(pos[a], pos[b]);
}
inline void adj(int x) {
	for (int p = pos[x]; (p >> 1) && d[heap[p]] < d[heap[p >> 1]]; p >>= 1)
		swn(heap[p], heap[p >> 1]);
}
inline void push(int x) {
	heap[pos[x] = ++top] = x;
	adj(x);
}
inline void pop() {
	swn(heap[1], heap[top]);
	pos[heap[top]] = 0;
	heap[top--] = 0;
    for (int u = 1, p; u < top; u = p) {
		p = d[heap[u << 1]] < d[heap[u << 1 | 1]] ? (u << 1) : (u << 1 | 1);
		if (d[heap[p]] < d[heap[u]])
			swn(heap[u], heap[p]);
		else
			break;
	}
}
inline void SPFA() {
	for (int u; top; ) {
		u = heap[1]; pop();
		for (edge *it = g[u]; it; it = it->nxt)
			if (max(d[u], it->v) < d[it->to]) {
				d[it->to] = max(d[u], it->v);
				if (pos[it->to]) adj(it->to);
				else push(it->to);
			}
	}
	//puts("Y");
}
int main() {
	//freopen("t.in", "r", stdin);
	int n, m, u, v, i, a, b, ans = 0x3f3f3f3f;
	gi(n), gi(m);
	for (i = 0; i < m; ++i)
		gi(e[i].u), gi(e[i].v), gi(e[i].a), gi(e[i].b);
	sort(e, e + m);
	memset(d, 63, sizeof d);
	d[1] = 0;
	for (i = 0; i < m; ++i) {
		u = e[i].u, v = e[i].v, a = e[i].a, b = e[i].b;
		add_edge(u, v, b);
		add_edge(v, u, b);
		//printf("%d %d %d %d\n", u, v, a, b);
		if (d[u] > d[v]) swap(u, v);
		if (max(d[u], b) < d[v])
			d[v] = max(d[u], b), push(v);
		if (a ^ e[i + 1].a)
			SPFA();
		ans = min(ans, a + d[n]);
	}
	printf("%d\n", ans < 0x3f3f3f3f ? ans : -1);
	return 0;
}
