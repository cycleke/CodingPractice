#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

const int N = 1e5+10;
int lc[N<<2], rc[N<<2], C[N<<2], ly[N<<2];
vector<int>g[N];
int n, m, dfs_Time, pre[N], co[N], cc[N], top[N], fa[N], son[N], dep[N];
#define FOR(a,b) for (vector<int>::iterator a=g[b].begin();a!=g[b].end();++a)
int dfs1(int u) {
	int ret = 1, mx = 0, t, v;
	FOR(it, u)
		if ((v = *it) ^ fa[u]) {

			fa[v] = u; dep[v] = dep[u] + 1;
			t = dfs1(v); ret += t;
			if (t > mx) mx = t, son[u] = v;
		}
	return ret;
}
void dfs2(int u, int tp) {
	top[u] = tp; pre[u] = ++dfs_Time;
	if (son[u]) dfs2(son[u], tp);
	FOR(it, u)
		if (!pre[*it]) dfs2(*it, *it);
}

#define ls u<<1
#define rs u<<1|1
#define lson u<<1,l,mid
#define rson u<<1|1,mid+1,r
#define MID int mid = l + r >> 1
#define root 1,1,n
void Down(int u) {
	if (~ly[u]) {
		lc[ls] = rc[ls] = ly[u];
		lc[rs] = rc[rs] = ly[u];
		ly[ls] = ly[rs] = ly[u];
		C[ls] = C[rs] = 1;
		ly[u] = -1;
	}
}
void Up(int u) {
	lc[u] = lc[ls], rc[u] = rc[rs];
	C[u] = C[ls] + C[rs] - (rc[ls]==lc[rs]);
}
void Build(int u, int l, int r) {
	if (l ^ r) {
		MID;Build(lson); Build(rson); Up(u);
	} else lc[u] = rc[u] = cc[l], C[u] = 1;
	ly[u] = -1;
}
void Tree_Update(int u, int l, int r, int x, int y, int val) {
	if (l >= x && r <= y) {
		lc[u] = rc[u] = ly[u] = val;
		C[u] = 1; return;
	}
	MID; Down(u);
	if (y <= mid) Tree_Update(lson, x, y, val);
	else if (x > mid) Tree_Update(rson, x, y, val);
	else Tree_Update(lson,x,mid,val),Tree_Update(rson,mid+1,y,val);
	Up(u);
}
int Tree_Query(int u, int l, int r, int x, int y) {
	if (l >= x && r <= y) return C[u];
	MID; Down(u);
	if (y <= mid) return Tree_Query(lson, x, y);
	else if (x > mid) return Tree_Query(rson, x, y);
	return Tree_Query(lson, x, mid) + Tree_Query(rson, mid+1, y) - (rc[ls]==lc[rs]);
}

void Change(int u, int v, int val) {
	while (top[u] ^ top[v]) {
		if (dep[top[u]] < dep[top[v]]) swap(u, v);
		Tree_Update(root, pre[top[u]], pre[u], val);
		u = fa[top[u]];
	}
	if (dep[u] < dep[v]) swap(u, v);
	Tree_Update(root, pre[v], pre[u], val);
}

int color(int u, int l,int r, int p) {
	if (l == r) return lc[u];
	MID; Down(u);
	if (p <= mid) return color(lson, p);
	else return color(rson, p);
}

int Count(int u, int v) {
	int ret = 0;
	while (top[u] ^ top[v]) {
		if (dep[top[u]] < dep[top[v]]) swap(u, v);
		ret += Tree_Query(root, pre[top[u]], pre[u]);
		if (color(root,pre[fa[top[u]]])==color(root,pre[top[u]])) --ret;
		u = fa[top[u]];
	}
	if (dep[u] < dep[v]) swap(u, v);
	return ret + Tree_Query(root,pre[v],pre[u]);
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("paint.in","r",stdin);
	freopen("my.out","w",stdout);
#endif
#ifdef cana
	int _size = 64 << 20;
	char *_p = (char*)malloc(_size) + _size;
	__asm__("movl %0, %%esp\n" :: "r"(_p));
#endif
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i)
	  scanf("%d", co + i);
	int a, b, c; char op[3];
	for (int i = 1; i < n; ++i) {
		scanf("%d%d", &a, &b);
		g[a].push_back(b); g[b].push_back(a);
	}
	dfs1(1); dfs2(1,1);
	for (int i = 1; i <= n; ++i)
	  cc[pre[i]] = co[i];
	Build(1,1,n);
	while (m--) {
		scanf("%s%d%d", op, &a, &b);
		if (*op ^ 'C') printf("%d\n", Count(a,b));
		else {
			scanf("%d", &c);
			Change(a,b,c);
		}
	}
	return 0;
}
