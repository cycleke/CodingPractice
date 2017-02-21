#include <vector>
#include <cstdio>
#include <cstring>
using namespace std;

#define N 100005
#define MS 4400005
typedef int arr[N];
bool vis[N];
arr id, sz, f, w;
int cnt, mset_pool[MS], *poolend, all, rt;
const size_t sint = sizeof(int);
struct edge {
	int t; edge *n;
	edge(int t = 0, edge *n = NULL) : t(t), n(n) {}
} me[N << 1], *g[N], *ce;
#define adde(a, b) (*ce = edge(b, g[a]), g[a] = ce++)
#define FOR(u) for (edge *it = g[u]; it; it = it->n)

struct BIT {
	int *tr, n;
	void Init(const int &n) {
		this->n = n;
		tr = poolend;
		memset(tr, 0, n * sint);
		poolend += n;
	}
	void add(int x, const int &delta) {
		for (; x < n; x += x & -x)
		  tr[x] += delta;
	}
	int sum(int x) const {
		int r = 0;
		for (x >= n ? x = n - 1 : 0; x > 0; x ^= x & -x)
		  r += tr[x];
		return r;
	}
}C[N << 1];

struct data {
	int root, subtree, dis;
	data(int root, int subtree, int dis) : root(root), subtree(subtree), dis(dis) {}
};
vector<data> vd[N];

void Init(const int &n) {
	poolend = mset_pool;
	ce = me; cnt = 0;
	for (int i = 1; i <= n; ++i) {
		g[i] = NULL;
		vis[i] = false;
		vd[i].clear();
	}
}

void grt(int u, int fa) {
	sz[u] = 1;
	f[u] = 0;
	FOR(u) if (!vis[it->t] && (it->t ^ fa)) {
		grt(it->t, u);
		sz[u] += sz[it->t];
		if (f[u] < sz[it->t])
		  f[u] = sz[it->t];
	}
	if (f[u] + sz[u] < all) 
	  f[u] = all - sz[u];
	if (f[u] < f[rt]) rt = u;
}

void cal(int u, int fa, int pa, int idx, int d) {
	vd[u].push_back(data(pa, idx, d));
	C[pa].add(d + 1, w[u]);
	C[idx].add(d, w[u]);
	FOR(u) if (!vis[it->t] && (it->t ^ fa))
		cal(it->t, u, pa, idx, d + 1);
}

void work(int u, int num) {
	all = num;
	rt = 0;
	grt(u, 0);
	u = rt;
	vis[u] = 1;
	id[u] = ++cnt;
	vd[u].push_back(data(cnt, -1, 0));
	C[cnt].Init(num + 2);
	C[cnt].add(1, w[u]);
	FOR(u) if (!vis[it->t]) {
		++cnt;
		if (sz[it->t] > sz[u])
		  sz[it->t]  = num - sz[u];
		C[cnt].Init(sz[it->t] + 2);
		cal(it->t, u, id[u], cnt, 1);
	}
	FOR(u) if (!vis[it->t])
		work(it->t, sz[it->t]);
}

int main() {
	int n, m, i, u, v, r;
	char ops[3];
	data d(0, 0, 0);
	f[0] = 0x3f3f3f3f;
	while (scanf("%d%d", &n, &m) != EOF) {
		Init(n);
		for (i = 1; i <= n; ++i) 
		  scanf("%d", w + i);
		for (i = 1; i < n; ++i) {
			scanf("%d%d", &u, &v);
			adde(u, v);
			adde(v, u);
		}
		work(1, n);
		while (m--) {
			scanf("%s%d%d", ops, &u, &v);
			if (*ops == '!') {
				r = v - w[u];
				for (i = 0; i < (int)vd[u].size(); ++i) {
					d = vd[u][i];
					C[d.root].add(d.dis + 1, r);
					if (~d.subtree)
					  C[d.subtree].add(d.dis, r);
				}
				w[u] = v;
			} else {
				r = 0;
				for (i = 0; i < (int)vd[u].size(); ++i) {
					d = vd[u][i];
					r += C[d.root].sum(v - d.dis + 1);
					if (~d.subtree)
					  r -= C[d.subtree].sum(v - d.dis);
				}
				printf("%d\n", r);
			}
		}
	}
	return 0;
}
