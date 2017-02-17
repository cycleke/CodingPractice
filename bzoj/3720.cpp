#include <cstdio>
#include <algorithm>
#define N 30003
#define inf 2147483647
//#define inf 20
struct edge {
	int t;
	edge *n;
} me[N * 3], *g[N << 1], *ce = me;
#define adde(a, b) (*ce = (edge){b, g[a]}, g[a] = ce++)
typedef int arrN2[N << 1];
arrN2 w, pre, in, ou, anc, fa, stk, dq, flag;
int n, dfn, _flag, totnode, *stktp;
struct node {
	int sum;
	node *ls, *rs;
} mset[2000001], *rt[N << 1], *cnode;
void Insert(node *x, node * &y, int l, int r, const int &val) {
	*(y = ++cnode) = *x;
	++y->sum;
	if (l >= r)
	  return;
	int m = ((long long)l + r) >> 1;
	if (val <= m)
	  Insert(x->ls, y->ls, l, m, val);
	else 
	  Insert(x->rs, y->rs, m + 1, r, val);
}
int Query(node *x, node *y, const int &p) {
	static int l, r, m, ret;
	for (l = 0, r = inf, ret = 0; (l ^ r) && (x->sum ^ y->sum);) {
		m = ((long long)l + r) >> 1;
		if (p <= m) {
			ret += y->rs->sum - x->rs->sum;
			x = x->ls;
			y = y->ls;
			r = m;
		} else
		  x = x->rs, y = y->rs, l = m + 1;
	}
	return ret;
}
void dfs(int u) {
	dq[in[u] = ++dfn] = u;
	for (edge *it = g[u]; it; it = it->n)
	  if (it->t ^ fa[u]) {
		  fa[it->t] = u;
		  dfs(it->t);
	  }
	ou[u] = dfn;
}
void rebuild() {
	++_flag;
	n = totnode;
	cnode = mset;
	stktp = stk;
	dfn = 0;
	dfs(1);
	for (int i = 1; i <= n; ++i) {
		Insert(rt[i - 1], rt[i], 0, inf, w[dq[i]]);
		anc[i] = in[i];
	}
}
void dfsquery(int u, const int &x, int &v) {
	if (x < w[u])
	  ++v;
	for (edge *it = g[u]; it; it = it->n)
	  dfsquery(it->t, x, v);
}
int main() {
	//freopen("t.in", "r", stdin);
	//freopen("t.out", "w", stdout);
	int m, u, v, i, Count = 0, lastans = 0;
	scanf("%d", &n);
	for (i = 1; i < n; ++i) {
		scanf("%d%d", &u, &v);
		adde(u, v);
		adde(v, u);
	}
	for (i = 1; i <= n; ++i) 
	  scanf("%d", w + i);
	totnode = n;
	*rt = mset;
	**rt = (node){0, *rt, *rt};
	rebuild();
	scanf("%d", &m);
	while (m--) {
		scanf("%d%d%d", &i, &u, &v);
		//printf("%d\n", m);
		u ^= lastans;
		v ^= lastans;
		if (i) {
			if (i & 1) {
				if (u <= n && (flag[u] ^ _flag)) {
					flag[u] = _flag;
					pre[u] = w[u];
					*stktp++ = u;
				}
				w[u] = v;
			} else {
				++totnode;
				adde(u, totnode);
				anc[totnode] = anc[u];
				w[totnode] = v;
			}
			if (++Count > 3000) {
				rebuild();
				Count = 0;
			}
		} else {
			lastans = 0;
			if (u <= n) {
				lastans = Query(rt[in[u] - 1], rt[ou[u]], v);
				for (int *it = stk; it < stktp; ++it) 
				  if (in[u] <= in[*it] && ou[u] >= in[*it]){
					  if (pre[*it] > v)
						--lastans;
					  if (w[*it] > v)
						++lastans;
				  }
				for (i = n + 1; i <= totnode; ++i)
				  if (w[i] > v && in[u] <= anc[i] && ou[u] >= anc[i])
					++lastans;
			} else 
			  dfsquery(u, v, lastans);
			printf("%d\n", lastans);
		}
	}
	return 0;
}
