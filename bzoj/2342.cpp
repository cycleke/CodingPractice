#include <cstdio>
#include <cstring>

const int MaxN = 1000009;
typedef int arr[MaxN];
arr p, f, fa;
char s[MaxN];
int gf(int u) {
	return (fa[u] ^ u) ? fa[u] = gf(fa[u]) : u;
}
inline int min(const int &a, const int &b) {
	return a < b ? a : b;
}
inline void cmax(int &a, const int & b) {
	if (a < b) a = b;
}

int main() {
	int n, ans = 0, t, i, k;
	scanf("%d%s", &n, s + 1);
	for (i = n; i; --i) s[i * 2] = s[i], s[i * 2 - 1] = '*';
	s[0] = '#', s[n * 2 + 1] = '*';
	t = n * 2 + 1;
	for (i = 2, k = 0; i <= t; ++i) {
		if (k + p[k] - 1 < i) p[i] = 1;
		else p[i] = min(p[2 * k - i], k + p[k] - i);
		while (s[i + p[i]] == s[i - p[i]]) ++p[i];
		if (i + p[i] > k + p[k]) k = i;
	}
	for (i = 1; i <= n; ++i) f[i] = (p[i * 2 + 1] - 1) / 2;
	for (i = 1; i <= n; ++i) fa[i] = i;
	for (i = 1; i <= n; ++i) {
		for (t = gf(i - f[i] / 2); t + f[t] < i; t = fa[t])
			fa[t] = gf(t + 1);
		cmax(ans, i - t);
	}
	printf("%d\n", ans * 4);
	return 0;
}
