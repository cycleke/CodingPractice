#include <cstdio>
#include <algorithm>
using namespace std;
#define N 150003
#define MS 6000005

struct edge {int t, w; edge *n;} me[N<<1|1], *g[N], *ce = me;
#define adde(a, b, c) (*ce = (edge){b, c, g[a]}, g[a] = ce++)

typedef int arr[N];
arr fa, tp, son, sz, in, dis, fd, ud, c1, a;
int dfn;
long long c2[N];

void d1(int u) {
	sz[u] = 1;
	++c1[a[u]];
	c2[a[u]] += dis[u];
	for (edge *it = g[u]; it; it = it->n)
		if (it->t ^ fa[u]) {
			fa[it->t] = u;
			//dep[it->t] = dep[u] + 1;
			dis[it->t] = dis[u] + it->w;
			d1(it->t);
			if (sz[it->t] > sz[son[u]])
				son[u] = it->t;
			sz[u] += sz[it->t];
		}
}

void d2(int u, int anc) {
	tp[u] = anc;
	in[u] = ++dfn;
	ud[dfn] = dis[u];
	fd[dfn] = dis[fa[u]];
	if (son[u]) d2(son[u], anc);
	for (edge *it = g[u]; it; it = it->n)
		if (!in[it->t])
			d2(it->t, it->t);
}

struct SegNode {
	int add;
	long long sum;
	SegNode *ls, *rs;
} SegMst[MS], *SegIt = SegMst, *rt[N];

void Insert(SegNode *x, SegNode * &y, int l, int r, const int &qx, const int &qy) {
	*(y = ++SegIt) = *x;
	if (qx <= l && r <= qy) {
		y->sum += ud[r] - fd[l];
		++y->add;
		return;
	}
	int m = l + r >> 1;
	if (qx <= m) Insert(x->ls, y->ls, l, m, qx, qy);
	if (qy > m) Insert(x->rs, y->rs, m + 1, r, qx, qy);
	y->sum = y->ls->sum + y->rs->sum + (long long)y->add * (ud[r] - fd[l]);
}

void Query(SegNode *x, SegNode *y, int l, int r, const int &qx, const int &qy, long long &v) {
	static int _x = 0, _y = 0;
	if (qx <= l && r <= qy) {
		v += y->sum - x->sum + (long long)(_y - _x) * (ud[r] - fd[l]);
		return;
	}
	int m = l + r >> 1;
	_x += x->add, _y += y->add;
	if (qx <= m) Query(x->ls, y->ls, l, m, qx, qy, v);
	if (qy > m) Query(x->rs, y->rs, m + 1, r, qx, qy, v);
	_x -= x->add, _y -= y->add;
}

void modify(int u, int age) {
	while (u) {
		Insert(rt[age], rt[age], 1, dfn, in[tp[u]], in[u]);
		u = fa[tp[u]];
	}
}

int ha[N], hcnt;
pair <int, int> pr[N];


int main() {
	//freopen("shop_hnoi2015.in", "r", stdin);
	//freopen("shop_hnoi2015.out", "w", stdout);
	int n, q, A, i, l, r, u, v, aa, bb;
	long long ans, t;
	scanf("%d%d%d", &n, &q, &A);
	for (i = 1; i <= n; ++i) {
		scanf("%d", a + i);
		ha[i] = a[i];
	}
	ha[hcnt = n + 1] = A + 1;
	sort(ha + 1, ha + hcnt + 1);
	hcnt = unique(ha + 1, ha + hcnt + 1) - ha - 1;
	for (i = 1; i <= n; ++i) {
		a[i] = lower_bound(ha + 1, ha + hcnt + 1, a[i]) - ha;
		pr[i] = make_pair(a[i], i);
	}
	for (i = 1; i < n; ++i) {
		scanf("%d %d %d", &u, &v, &aa);
		adde(u, v, aa);
		adde(v, u, aa);
	}
	d1(1);
	d2(1, 1);
	for (i = 1; i <= hcnt; ++i) {
		c1[i] += c1[i - 1];
		c2[i] += c2[i - 1];
	}
	*rt = SegIt;
	**rt = (SegNode) {0, 0LL, *rt, *rt};
	sort(pr + 1, pr + n + 1);
	for (i = 1; i <= n; ++i) {
		if (pr[i].first ^ pr[i - 1].first)
			rt[pr[i].first] = rt[pr[i - 1].first];
		modify(pr[i].second, pr[i].first);
	}
	rt[hcnt] = rt[hcnt - 1];

	//for (i = 1; i <= hcnt; ++i)
	//	printf("%lld ", rt[i]->sum);
	//puts("");
	
	ans = 0;
	while (q--) {
		scanf("%d%d%d", &u, &aa, &bb);
		l = (aa + ans) % A;
		r = (bb + ans) % A;
		if (r < l) l ^= r ^= l ^= r;
		l = lower_bound(ha + 1, ha + hcnt + 1, l) - ha - 1;
		r = upper_bound(ha + 1, ha + hcnt + 1, r) - ha - 1;
		ans = c2[r] - c2[l] + (c1[r] - c1[l]) * (long long)dis[u];
		for (t = 0; u; u = fa[tp[u]])
			Query(rt[l], rt[r], 1, n, in[tp[u]], in[u], t);
		ans -= t << 1;
		printf("%lld\n", ans);
	}
	return 0;
}
