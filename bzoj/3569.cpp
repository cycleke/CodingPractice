#include <bits/stdc++.h>
#define N 100001
#define M 500001
#define CON "Connected"
#define DIS "Disconnected"
struct edge {int t, n;} me[M<<1|1];
int g[N], a[M], b[N], stk[17], tp;
#define FOR(a, b) for (int a = g[b]; a; a = me[a].n)
inline void adde(int a, int b) {
	static unsigned int ce = 1;
	me[++ce] = (edge) {b, g[a]};
	g[a] = ce;
}
void d1(int u, int f) {
	static bool vis[N];
	vis[u] = true;
	unsigned int v;
	FOR (i, u) if ((v = me[i].t) ^ f) {
		if (!vis[v]) d1(v, u);
		else if (!~a[i >> 1]) {
			a[i >> 1] = ((rand() << 12) ^ rand()) & ((1U << 31) - 1);
			b[v] ^= a[i >> 1];
			b[u] ^= a[i >> 1];
		}
	}
}
void d2(int u) {
	static bool vis[N];
	vis[u] = true;
	FOR(i, u) if (!vis[me[i].t]) {
		d2(me[i].t);
		a[i >> 1] = b[me[i].t];
		b[u] ^= b[me[i].t];
	}
}
inline void guass() {
	static int i, j, k;
	for (k = 0, j = 1 << 30; j; j >>= 1) {
		for (i = k + 1; i <= tp; ++i)
			if (stk[i] & j) break;
		if (i > tp) continue;
		std::swap(stk[i], stk[++k]);
		for (i = 1; i <= tp; ++i)
			if (stk[i] & j && (i ^ k))
				stk[i] ^= stk[k];
	}
}
int main() {

	//freopen("t.in", "r", stdin);
	
	srand(1234321);
	int i, x, y, k, n, m, q, last_ans = 0U;
	scanf("%d%d", &n, &m);
	for (i = 1; i <= m; ++i) {
		scanf("%d%d", &x, &y);
		adde(x, y), adde(y, x);
	}
	memset(a, -1, sizeof a);
	d1(1, 0); d2(1);
	scanf("%d", &q);
	while (q--) {
		scanf("%d", &k);
		tp = 0;
		while (k--) {
			scanf("%d", &x);
			stk[++tp] = a[x ^ last_ans];
		}
		guass();
		last_ans += (bool)stk[tp];
		puts(stk[tp] ? CON : DIS);
	}
	return 0;
}
