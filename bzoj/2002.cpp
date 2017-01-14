#include <cstdio>
const int N = 200009;
bool rt[N];
int siz[N], ch[2][N], fa[N];

inline void update(const int &u) {
	siz[u] = siz[ch[0][u]] + siz[ch[1][u]] + 1;
}

inline void rot(int u) {
	static int v, d;
	v = fa[u], d = ch[1][v] == u;
	fa[ch[d][v] = ch[d^1][u]] = v;
	fa[u] = fa[v];
	fa[ch[d^1][u] = v] = u;
	if (rt[v]) rt[v] = false, rt[u] = true;
	else ch[ch[1][fa[v]]==v][fa[u]] = u;
	update(v); update(u);
}

inline void splay(int u) {
	for (static int f; !rt[u]; rot(u))
		if (!rt[f = fa[u]])
			rot(((ch[1][fa[f]]==f)==(ch[1][f]==u)) ? f : u);
}

inline void access(int u) {
	static int v;
	for (v = 0; u; u = fa[v = u]) {
		splay(u);
		rt[ch[1][u]] = true;
		rt[ch[1][u] = v] = false;
		update(u);
	}
}

int main() {
	int n, m, i, x, y;
	scanf("%d", &n);
	for (i = 1; i <= n; ++i) {
		scanf("%d", &x);
		x += i;
		if (x > n) x = n + 1;
		fa[i] = x;
		siz[i] = 1;
		rt[i] = true;
	}
	siz[n + 1] = 1;
	rt[n + 1] = true;
	scanf("%d", &m);
	while (m--) {
		scanf("%d", &i);
		if (i < 2) {
			scanf("%d", &x);
			++x;
			access(x);
			splay(x);
			printf("%d\n", siz[ch[0][x]]);
		} else {
			scanf("%d%d", &x, &y);
			++x;
			access(x);
			splay(x);
			i = ch[0][x];
			fa[i] = fa[x];
			fa[x] = 0;
			rt[i] = true;
			ch[0][x] = 0;
			update(x);
			y += x;
			if (y > n) y = n + 1;
			fa[x] = y;
		}
	}
	return 0;
}
