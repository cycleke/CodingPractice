#include <cstdio>
#include <algorithm>
#define N 100005
inline void gi(int &a) {
	static char c;
	while (c = getchar(), c < '0'); a = c - '0';
	while (c = getchar(), '-' < c) a = (a << 3) + (a << 1) + c - '0';
}
int fa[N], ch[2][N];
bool rev[N];
//LCT
inline bool isrt(int u) {
	return (ch[0][fa[u]] ^ u) && (ch[1][fa[u]] ^ u);
}
inline void updr(int u) {
	if (!u) return;
	std::swap(ch[0][u], ch[1][u]);
	rev[u] ^= 1;
}
inline void pd(int u) {
	if (!rev[u]) return;
	updr(ch[0][u]);
	updr(ch[1][u]);
	rev[u] = false;
}
inline void rot(int u) {
	static int f, d;
	f = fa[u], d = u == ch[1][f];
	if (ch[d][f] = ch[d^1][u]) fa[ch[d][f]] = f;
	if (!isrt(f)) ch[f == ch[1][fa[f]]][fa[f]] = u;
	fa[u] = fa[f], fa[f] = u;
	ch[d^1][u] = f;
}
void P(int u) {
	if (!isrt(u)) P(fa[u]);
	pd(u);
}
inline void splay(int u) {
	static int f;
	for (P(u); !isrt(u); rot(u))
		if (!isrt(f = fa[u]))
			rot(((f == ch[1][fa[f]]) ^ (u == ch[1][f])) ? u : f);
}
inline void access(int u) {
	static int v;
	for (v = 0; u; u = fa[v = u])
		splay(u), ch[1][u] = v;
}
inline void mrt(int u) {
	access(u);
	splay(u);
	updr(u);
}
inline int frt(int u) {
	while (fa[u]) u = fa[u];
	return u;
}
inline void link(int u, int v) {
	mrt(u);
	fa[u] = v;
}
inline void cut(int u, int v) {
	mrt(u);
	splay(v);
	fa[ch[0][v]] = fa[v];
	fa[v] = 0;
	ch[0][v] = 0;
}

int main() {
	int n, m, u, v;
	char ops[10];
	gi(n), gi(m);
	while (m--) {
		scanf("%s", ops);
		gi(u), gi(v);
		if (*ops == 'C') link(u, v);
		else if (*ops == 'D') cut(u, v);
		else puts((frt(u) ^ frt(v)) ? "No" : "Yes");
	}
	return 0;
}
