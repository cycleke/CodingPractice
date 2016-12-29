#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 2e5 + 50;
struct op {
	int x, y, id, c, k;
	bool operator < (const op &a) const { return c < a.c || c == a.c && k < a.k; }
}P[N];

int in[N], out[N], Tim, C[N], n, m, root, anc[N], fa[N], son[N], dep[N];
int to[N], nxt[N], totE, head[N], cnt, ans[2][N], s[N];
#define adde(a,b) (to[totE]=b,nxt[totE]=head[a],head[a]=totE++)
void Add(int x, int val) { for (; x <= n; x += x & -x) C[x] += val; }
int Sum(int x) {
	int ret = 0; for (; x; x -= x & -x) ret += C[x];
	return ret;
}
#define FOR(a,u) for(int a = head[u]; ~a; a = nxt[a])
int dfs1(int u) {
	s[u] = 1; son[u] = 0;
	FOR(i, u) if (to[i] ^ fa[u]){
		fa[to[i]] = u;
		dep[to[i]] = dep[u] + 1;
		dfs1(to[i]); s[u] += s[to[i]];
		if (s[to[i]] > s[son[u]]) son[u] = to[i];
	}
}
void dfs2(int u, int tp) {
	in[u] = ++Tim; anc[u] = tp;
	if (son[u]) dfs2(son[u], tp);
	FOR(i, u) if ((to[i] ^ son[u]) && (to[i] ^ fa[u])) 
		dfs2(to[i], to[i]);
	out[u] = Tim;
}
int lca(int a, int b) {
	for (; anc[a] ^ anc[b]; a = fa[anc[a]])
	  if (dep[anc[a]] < dep[anc[b]]) swap(a, b);
	return (dep[a] < dep[b]) ? a : b;
}
int main() {
#ifndef ONLINE_JUDGE
	freopen("T.in", "r", stdin);
#endif
	scanf("%d", &n); int t;
	memset(head, -1, sizeof head);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &t);
		if (t) adde(t, i);
	}
	dep[1] = 1; dfs1(1); dfs2(1, 1);
	scanf("%d", &m);
	for (int i = 1; i <= m; ++i) {
		scanf("%d", &P[i].k);
		if (P[i].k == 1) {
			scanf("%d%d%d", &P[i].x, &P[i].y, &t);
			P[i].c = i - t; P[i].id = ++cnt;
		} else {
			scanf("%d", &P[i].x); P[i].c = i;
		}
	}
	sort(P + 1, P + m + 1);
	for (int i = 1; i <= m; ++i) 
	  if (P[i].k == 1) {
		int f = lca(P[i].x, P[i].y), ff = fa[f];
		ans[0][P[i].id] = dep[P[i].x] + dep[P[i].y] - dep[f] - dep[ff];
		ans[1][P[i].id] = Sum(in[P[i].x]) + Sum(in[P[i].y]) - Sum(in[ff]) - Sum(in[f]);
	  } else {
		Add(in[P[i].x], 1); Add(out[P[i].x]+1, -1);
	  }
	for (int i = 1; i <= cnt; ++i) printf("%d %d\n", ans[0][i], ans[1][i]);
	return 0;
}
