#include <cstdio>
#include <cstring>
inline int gi() {
	static int a; static char c;
	while ((c = getchar()) < '0'); a = c - '0';
	while ('-' < (c = getchar())) a = (a << 3) + (a << 1) + c - '0';
	return a;
}
#define N 100003
int f[N], dp[3][12][N], Q;
struct edge {int t; edge *n;}me[200003], *ce = me, *hd[N];
inline void adde(int a, int b) {
	ce->t = b, ce->n = hd[a];
	hd[a] = ce++;
}
inline int gf(int u) {
	static int r, t;
	for (r = u; f[r] ^ r; r = f[r]);
	while (u ^ r) t = f[u], f[u] = r, u = t;
	return r;
}

inline int gn(const long long &a) {
	static int t;
	if (!a) return 0;
	return (t = a % Q) ? t : Q;
}

void dfs(int u, int k, int fa) {
	int v, t1, t2;
	int &d0 = dp[0][k][u];
	int &d1 = dp[1][k][u];
	int &d2 = dp[2][k][u];
	d0 = 1;
	for (edge *it = hd[u]; it; it = it->n)
		if ((v = it->t) ^ fa) {
			dfs(v, k, u);
			t1 = k ? gn((long long)dp[0][k-1][v]+dp[1][k-1][v]+dp[2][k-1][v]) : 0;
			t2 = gn((long long)dp[0][k][v] + dp[1][k][v]);
			d2 = gn((long long)d2*t1 + (long long)d1*t2);
			d1 = gn((long long)d1*t1 + (long long)d0*t2);
			d0 = gn((long long)d0*t1);
		}
}

int main() {
	int n = gi(), m = gi(), i, a, b;
	Q = gi();
	for (i = 1; i <= n; ++i) f[i] = i;
	while (m--) {
		f[gf(a = gi())] = gf(b = gi());
		adde(a, b); adde(b, a);
	}
	for (i = 1; i < n; ++i) if (gf(i) ^ gf(n)) return puts("-1\n-1"), 0;
	for (i = 0; ; ++i) {
		dfs(1, i, 0);
		if (a = dp[0][i][1] + dp[1][i][1] + dp[2][i][1]) {
			printf("%d\n%d\n", i, a % Q);
			break;
		}
	}
	return 0;
}
