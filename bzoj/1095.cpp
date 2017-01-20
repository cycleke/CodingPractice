#include <queue>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 100013;

class heap {
protected:
	priority_queue < int > A, B;
public:
	void push(const int &x) {
		A.push(x);
	}
	void erase(const int &x) {
		B.push(x);
	}
	void pop() {
		while (!B.empty() && !(A.top() ^ B.top()))
			A.pop(), B.pop();
		A.pop();
	}
	int top() {
		while (!B.empty() && !(A.top() ^ B.top()))
			A.pop(), B.pop();
		return A.empty() ? -0x3f3f3f3f : A.top();
	}
	int size() const {
		return A.size() - B.size();
	}
	bool empty() const {
		return !(A.size() ^ B.size());
	}
	int tps() {
		if (size() < 2) return -0x3f3f3f3f;
		int t1, t2;
		while (!B.empty() && !(A.top() ^ B.top()))
			A.pop(), B.pop();
		t1 = A.top(); A.pop();
		while (!B.empty() && !(A.top() ^ B.top()))
			A.pop(), B.pop();
		t2 = A.top(); A.push(t1);
		return t1 + t2;
	}
}GlobleHeap, FirstHeap[N], SecondHeap[N];

struct edge {
	int t;
	edge *n;
} me[N << 1 | 1], *ce = me, *g[N];

inline void adde(const int &a, const int &b) {
	ce->t = b, ce->n = g[a], g[a] = ce++;
}

int deep[N], fa[20][N], dis[20][N], size[N], f[N], totsize, rt, tot_off;
bool vis[N], on[N];

inline void cmax(int &a, const int &b) {
	if (a < b) a = b;
}

void grt(int u, int father) {
	int v;
	size[u] = 1, f[u] = 0;
	for (edge *it = g[u]; it; it = it->n) {
		v = it->t;
		if (vis[v] || (v == father)) continue;
		grt(v, u);
		size[u] += size[v];
		cmax(f[u], size[v]);
	}
	cmax(f[u], totsize - size[u]);
	if (f[u] < f[rt]) rt = u;
}

void dfs(int u, const int &anc, int father, int dep) {
	int v;
	for (edge *it = g[u]; it; it = it->n) {
		v = it->t;
		if (vis[v] || (v == father)) continue;
		fa[++deep[v]][v] = anc;
		dis[deep[v]][v] = dep;
		dfs(v, anc, u, dep + 1);
	}
}

void build(int u) {
	int v, all = totsize;
	vis[u] = true;
	dfs(u, u, 0, 1);
	for (edge *it = g[u]; it; it = it->n) {
		if (vis[v = it->t]) continue;
		if (size[u] < size[v])
			size[v] = all - size[u];
		totsize = size[v];
		rt = 0;
		grt(v, u);
		build(rt);
	}
}

inline void turn_off(const int &u) {
	static int t, i, pre;
	SecondHeap[u].push(0);
	if (SecondHeap[u].size() == 2)
		GlobleHeap.push(SecondHeap[u].top());
	for (i = deep[u]; i > 1; --i)
		if (FirstHeap[fa[i][u]].empty()) {
			FirstHeap[fa[i][u]].push(dis[i - 1][u]);
			pre = SecondHeap[fa[i - 1][u]].tps();
			SecondHeap[fa[i - 1][u]].push(dis[i - 1][u]);
			if (pre > 0) {
				if (pre ^ (t = SecondHeap[fa[i - 1][u]].tps())) {
					GlobleHeap.erase(pre);
					GlobleHeap.push(t);
				}
			} else if ((t = SecondHeap[fa[i - 1][u]].tps()) > 0)
					   GlobleHeap.push(t);
		} else {
			t = FirstHeap[fa[i][u]].top();
			FirstHeap[fa[i][u]].push(dis[i - 1][u]);
			if (t < dis[i - 1][u]) {
				pre = SecondHeap[fa[i - 1][u]].tps();
				SecondHeap[fa[i - 1][u]].erase(t);
				SecondHeap[fa[i - 1][u]].push(dis[i - 1][u]);
				if (pre > 0 && (pre ^ (t = SecondHeap[fa[i - 1][u]].tps()))) {
					GlobleHeap.erase(pre);
					GlobleHeap.push(t);
				}
			}
		}
}

inline void turn_on(const int &u) {
	SecondHeap[u].erase(0);
	if (SecondHeap[u].size() == 1)
		GlobleHeap.erase(SecondHeap[u].top());
	for (int t, pre, i = deep[u]; i > 1; --i) {
		FirstHeap[fa[i][u]].erase(dis[i - 1][u]);
		if (FirstHeap[fa[i][u]].top() < dis[i - 1][u]) {
			pre = SecondHeap[fa[i - 1][u]].tps();
			SecondHeap[fa[i - 1][u]].erase(dis[i - 1][u]);
			if (!FirstHeap[fa[i][u]].empty())
				SecondHeap[fa[i - 1][u]].push(FirstHeap[fa[i][u]].top());
			if (pre > 0 && (pre ^ (t = SecondHeap[fa[i - 1][u]].tps()))) {
				GlobleHeap.erase(pre);
				if (SecondHeap[fa[i - 1][u]].size() > 1)
					GlobleHeap.push(t);
			}
		}
	}
}

inline void Switch(const int &u) {
	if (on[u]) turn_off(u);
	else turn_on(u);
	on[u] ^= 1;
	if (on[u]) --tot_off;
	else ++tot_off;
}

int main() {
	//freopen("1095.in", "r", stdin);
	int n, m, u, v;
	char ops[4];
	scanf("%d", &n);
	for (m = 1; m < n; ++m) {
		scanf("%d%d", &u, &v);
		adde(u, v), adde(v, u);
	}
	f[0] = 0x3f3f3f3f;
	totsize = tot_off = n;
	grt(1, 0);
	build(rt);
	for (m = 1; m <= n; ++m)
		fa[++deep[m]][m] = m, turn_off(m);
	scanf("%d", &m);
	while (m--) {
		scanf("%s", ops);
		if (*ops == 'G') {
			if (!tot_off)puts("-1");
			else printf("%d\n", max(GlobleHeap.top(), 0));
		} else {
			scanf("%d", &u);
			Switch(u);
		}
	}
	return 0;
}
