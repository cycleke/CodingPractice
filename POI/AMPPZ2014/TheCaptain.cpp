#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;

typedef pair<int, int> pr;
priority_queue<pr>heap;
#define inf 0x7fffffff
#define N 200005
struct edge {int t, v; edge *n;} me[N * 8 + 1], *g[N * 3], *ce = me;
struct node {int x, y, id;} a[N];
#define adde(a, b, c) (ce->t = b, ce->v = c, ce->n = g[a], g[a] = ce++)
inline void link(int a, int b, int c) {
	adde(a, b, c);
	adde(b, a, c);
}
int d[N * 3], cnd;
bool cx(const node &a, const node &b) {
	return a.x < b.x;
}
bool cy(const node &a, const node &b) {
	return a.y < b.y;
}
inline bool cmin(int &a, const int &b) {
	if (b < a) return a = b, true;
	return false;
}
inline void dijstra() {
	int u, v, dis;
	edge *it;
	heap.push(make_pair(0, 1));
	while (!heap.empty()) {
		u = heap.top().second;
		dis = -heap.top().first;
		heap.pop();
		if (dis ^ d[u]) continue;
		for (it = g[u]; it; it = it->n)
			if (cmin(d[v = it->t], dis + it->v))
				heap.push(make_pair(-d[v], v));
	}
}

int main() {
	int n, i, j, x, y;
	scanf("%d", &n);
	for (i = 0; i < n; ++i) {
		scanf("%d%d", &x, &y);
		a[i] = (node) {x, y, i + 1};
	}
	cnd = n;
	sort(a, a + n, cx);
	a[n] = (node) {inf, inf};
	for (y = i = 0; i < n; i = j) {
		++cnd;
		for (j = i; a[j].x == a[i].x; ++j)
			link(cnd, a[j].id, 0);
		if (y) link(cnd, y, a[i].x - x);
		x = a[i].x, y = cnd;
	}
	sort(a, a + n, cy);
	for (y = i = 0; i < n; i = j) {
		++cnd;
		for (j = i; a[j].y == a[i].y; ++j)
			link(cnd, a[j].id, 0);
		if (y) link(cnd, y, a[i].y - x);
		x = a[i].y, y = cnd;
	}
	for (i = 1; i <= cnd; ++i) d[i] = inf;
	d[1] = 0;
	dijstra();
	printf("%d\n", d[n]);
	return 0;
}
