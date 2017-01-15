#include <cstdio>
#include <algorithm>
using namespace std;
inline int gi() {
	static int a; static char c, f;
	for (f = 0; (c = getchar()) < '0';) f |= c == '-';
	for (a = c - '0'; '-' < (c = getchar());) a = (a << 3) + (a << 1) + c - '0';
	return f ? -a : a;
}
#define N 2003
#define mo 1000000007
int r[N], a[N], C[N][N], f[N], g[N], dt;
inline bool cmp(const int &i, const int &j) {
	return a[i] < a[j];
}
inline void mov(int &a, const int &b) {
	(a += b) >= mo ? a -= mo : 0;
}
inline void add(int *tr, int x, const int &v) {
	for (; x < dt; x += x & -x)
		mov(tr[x], v);
}
inline int sum(int *tr, int x) {
	static int r;
	for (r = 0; x; x -= x & -x)
		mov(r, tr[x]);
	return r;
}
int main() {
	int n = gi(), i, j, last, ans = 0, t;
	for (i = 1; i <= n; ++i) *(a + (r[i] = i)) = gi();
	sort(r + 1, r + n + 1, cmp);
	last = a[r[1]];
	a[r[1]] = dt = 1;
	for (i = 2; i <= n; ++i) {
		if (last ^ a[j = r[i]]) last = a[j], ++dt;
		a[j] = dt;
	}
	++dt;
	add(C[0], 1, 1);
	for (i = 1; i <= n; ++i)
		for (j = i; j; --j) {
			t = sum(C[j - 1], a[i]);
			mov(f[j], t);
			add(C[j], a[i], t);
		}
	for (i = *g = 1; i <= n; ++i) g[i] = (long long)g[i - 1] * i % mo;
	for (i = 1; i <= n; ++i) {
		mov(ans, (int)((long long)f[i] * g[n - i] % mo));
		if (i ^ n) mov(ans, (int)(mo - (long long)f[i + 1] * (i + 1) % mo * g[n - i - 1] % mo));
	}
	printf("%d\n", ans);
	return 0;
}
