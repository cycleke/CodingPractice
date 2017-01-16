#include <cstdio>
inline int gi() {
	static int a; static char c;
	while ((c = getchar()) < '0'); a = c - '0';
	while ('-' < (c = getchar())) a = (a << 3) + (a << 1) + c - '0';
	return a;
}
#define N 100003
struct edge{int t, w; edge *n;}me[2000003], *ce = me, *hd[N];
inline void adde(int a, int b, int c) {
	ce->t = b, ce->w = c;
	ce->n = hd[a], hd[a] = ce++;
}
bool vis[N]; int dep[N], mx, mi, t;

inline int gcd(int a, int b) {
	for (int t; b; t = a % b, a = b, b = t);
	return a;
}
inline int abs(const int &a) {
	return a < 0 ? -a : a;
}
void dfs(int u) {
	vis[u] = true;
	if (mx < dep[u]) mx = dep[u];
	if (dep[u] < mi) mi = dep[u];
	for (edge *it = hd[u]; it; it = it->n)
		if (!vis[it->t]){
			dep[it->t] = dep[u] + it->w;
			dfs(it->t);
		} else t = gcd(abs(dep[u] + it->w - dep[it->t]),t);
}

int main() {
	int n = gi(), m = gi(), a, b, i, sum = 0;
	while (m--) {
		a = gi(), b = gi();
		adde(a, b, 1); adde(b, a, -1);
	}
	for (i = 1; i <= n; ++i) if (!vis[i]) {
			mx = mi = 0;
			dfs(i);
			sum += mx - mi + 1;
		}
	if (!t) (sum < 3) ? puts("-1 -1") : printf("%d %d\n", sum, 3);
	else if (t < 3) puts("-1 -1");
	else {
		for (i = 3; t % i; ++i);
		printf("%d %d\n", t, i);
	}
	return 0;
}
