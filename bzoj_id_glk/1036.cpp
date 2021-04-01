#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

//Input
int Ina; bool InSign; char Inc;
inline int geti() {
	InSign = false; 
	while ((Inc = getchar()) < '0' || Inc > '9') InSign |= Inc == '-'; 
	Ina = Inc - '0';
	while ((Inc = getchar()) >= '0' && Inc <= '9') Ina = (Ina << 3) + (Ina << 1) + Inc - '0'; 
	return InSign ? -Ina : Ina;
}
const int N = 3e5 + 10;
int Max[N << 2], pre;
long long Sum[N << 2];

#define Up(u) Max[u] = max(Max[u<<1], Max[u << 1 | 1]), Sum[u] = Sum[u << 1] + Sum[u << 1 | 1]

void Update(int pos, const int &val) {
	pos += pre;
	for (Max[pos] = Sum[pos] = val, pos >>= 1; pos; pos >>= 1) 
	  Up(pos);
}

pair<long long, int> Query(int s, int t) {
	long long rets = 0; int retm = -30002;
	for (s += pre - 1, t += pre + 1; s ^ t ^ 1; s >>= 1, t >>= 1) {
		if (~s & 1) rets += Sum[s ^ 1], retm = max(retm, Max[s ^ 1]);
		if ( t & 1) rets += Sum[t ^ 1], retm = max(retm, Max[t ^ 1]);
	}
	return make_pair(rets, retm);
}

//Tree
int Tid, id[N], anc[N], fa[N], sz[N], hv[N], dep[N], a[N]; 
int head[N], to[N << 1], nxt[N << 1], totE;
inline void adde(const int &a, const int &b) {
	to[totE] = b, nxt[totE] = head[a];
	head[a] = totE++;
}

void dfs1(int u, int f) {
	sz[u] = 1, fa[u] = f; dep[u] = dep[f] + 1;
	for (int i = head[u]; ~i; i = nxt[i]) 
	  if (to[i] ^ f){
		  dfs1(to[i], u);
		  sz[u] += sz[to[i]];
		  if (sz[to[i]] > sz[hv[u]]) hv[u] = to[i];
	  }
}

void dfs2(int u, int ac) {
	id[u] = ++Tid; anc[u] = ac; Sum[Tid + pre] = Max[Tid + pre] = a[u];
	if (hv[u]) dfs2(hv[u], ac);
	for (int i = head[u]; ~i; i = nxt[i])
	  if (to[i] != fa[u] && to[i] != hv[u]) dfs2(to[i], to[i]);
}

pair<long long, int> query(int u, int v) {
	long long rets = 0;	int retm = -30002; pair<long long, int>tmp;
	while (anc[u] ^ anc[v]) {
		if (dep[anc[u]] < dep[anc[v]]) swap(u, v);
		tmp = Query(id[anc[u]], id[u]);
		rets += tmp.first;
		retm = max(retm, tmp.second);
		u = fa[anc[u]];
	}
	if (dep[u] > dep[v]) swap(u, v);
	tmp =  Query(id[u], id[v]);
	rets += tmp.first;
	retm = max(retm, tmp.second);
	return make_pair(rets, retm);
}

int main() {
	int n = geti(), x, y; char op[10];
	memset(op, 0, sizeof op);
	memset(head, -1, sizeof head);
	for (int i = 1; i < n; ++i) adde(x = geti(), y = geti()), adde(y, x);
	for (pre = 1; pre <= n + 1; pre <<= 1);
	for (int i = 1; i <= n; ++i) a[i] = geti();
	dfs1(1, 0); dfs2(1, 1);
	for (int i = pre; i; --i) Up(i);
	for (n = geti(); n; --n) {
		scanf("%s", op);
		x = geti(), y = geti();
		if (op[1] == 'S') {
			printf("%lld\n", query(x, y).first);
		} else if (op[1] == 'M') {
			printf("%d\n", query(x, y).second);
		}
		else Update(id[x], y);
	}
	return 0;
}
