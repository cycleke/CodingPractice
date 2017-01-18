#include <cstdio>
#include <cstring>
#include <algorithm>
inline int gi() {
	static int a; static char c, f;
	for (f = 0; (c = getchar()) < '0'; f |= c == '-');
	for (a = c - '0'; '-' < (c = getchar()); a = (a << 3) + (a << 1) + c - '0');
	return f ? -a : a;
}
#define N 300013
#define MS 1200013
struct edge {int t; edge *n;} me[N], *ce = me, *g[N];
inline void adde(int a, int b) {
	ce->t = b, ce->n = g[a], g[a] = ce++;
}
int f[N], a[N], b[N], opt[N], a1[N], a2[N], in[N], out[N], Add[MS], Max[MS], _dfn;
inline int gf(int u) {
	static int r, t;
	for (r = u; f[r] ^ r; r = f[r]);
	while (u ^ r) t = f[u], f[u] = r, u = t;
	return r;
}
void dfs(int u) {
	in[u] = out[u] = ++_dfn;
	for (edge *it = g[u]; it; it = it->n) dfs(it->t);
}
inline void pd(const int &u) {
	if (!Add[u]) return;
	static int ls, rs;
	ls = u<<1, rs = u<<1|1;
	Add[ls] += Add[u], Max[ls] += Add[u];
	Add[rs] += Add[u], Max[rs] += Add[u];
	Add[u] = 0;
}
inline void pu(const int &u) {
	Max[u] = std::max(Max[u<<1], Max[u<<1|1]);
}
void build(int u, int l, int r) {
	Add[u] = 0;
	if (l >= r) return (void)(Max[u] = b[l]);
	int m = l + r >> 1;
	build(u << 1, l, m);
	build(u << 1 | 1, m + 1, r);
	pu(u);
}
void update(int u, int l, int r, const int &x, const int &y, const int &delta) {
	if (x <= l && r <= y) return (void)(Add[u] += delta, Max[u] += delta);
	int m = l + r >> 1; pd(u);
	if (x <= m) update(u << 1, l, m, x, y, delta);
	if (y >  m) update(u << 1 | 1, m + 1, r, x, y, delta);
	pu(u);
}
inline void cmax(int &a, const int &b) {
	if (a < b) a = b;
}
void query(int u, int l, int r, const int &x, const int &y, int &v) {
	if (x <= l && r <= y) return cmax(v, Max[u]);
	int m = l + r >> 1; pd(u);
	if (x <= m) query(u << 1, l, m, x, y, v);
	if (y >  m) query(u << 1 | 1, m + 1, r, x, y, v);
}
int main() {
	//freopen("2333.in", "r", stdin);
	int n, m, i, x, y;
	char str[5];
	n = gi();
	for (i = 1; i <= n; ++i) f[i] = i, a[i] = gi();
	m = gi();
	for (i = 1; i <= m; ++i) {
		scanf("%s", str);
		if (*str == 'U') {
			x = gf(gi()), y = gf(gi());
			if (x == y) continue;
			f[y] = x;
			a1[i] = x, a2[i] = y;
			opt[i] = 1;
		} else if (*str == 'A') {
			if (str[1] == '1') {
				opt[i] = 2;
				a1[i] = gi(); a2[i] = gi();
			} else if (str[1] == '2') {
				opt[i] = 3;
				a1[i] = gf(gi()); a2[i] = gi();
			} else opt[i] = 4, a1[i] = gi();
		} else {
			if (str[1] == '1') opt[i] = 5, a1[i] = gi();
			else if (str[1] == '2') opt[i] = 6, a1[i] = gf(gi());
			else opt[i] = 7;
		}
	}
	for (i = m; i; --i) if (opt[i] == 1) adde(a1[i], a2[i]);
	for (i = 1; i <= n; ++i) if (gf(i) == i) dfs(i);
	for (i = 1; i <= n; ++i) b[in[i]] = a[i];
	build(1, 1, n);
	for (i = 1; i <= m; ++i)
		if (opt[i] == 1) out[a1[i]] = out[a2[i]];
		else if (opt[i] == 2) update(1, 1, n, in[a1[i]], in[a1[i]], a2[i]);
		else if (opt[i] == 3) update(1, 1, n, in[a1[i]], out[a1[i]], a2[i]);
		else if (opt[i] == 4) update(1, 1, n, 1, n, a1[i]);
		else if (opt[i] == 5) {
			x = -0x7fffffff;
			query(1, 1, n, in[a1[i]], in[a1[i]], x);
			printf("%d\n", x);
		} else if (opt[i] == 6) {
			x = -0x7fffffff;
			query(1, 1, n, in[a1[i]], out[a1[i]], x);
			printf("%d\n", x);
		} else if (opt[i] == 7) {
			x = -0x7fffffff;
			query(1, 1, n, 1, n, x);
			printf("%d\n", x);
		}
	return 0;
}
