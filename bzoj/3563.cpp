#include <bits/stdc++.h>
char s[1009], mark[500001];
std::pair<int, int> e[500001];
int fa[100001], ans[50001];
int gf(int u) {
	return ::fa[u] == u ? u : ::fa[u] = gf(::fa[u]);
}
#define isdight(c) (c >= '0' && c <= '9')
inline bool uni(int x, int y) {
	x = gf(x), y = gf(y);
	if (x ^ y) return ::fa[x] = y, true;
	return false;
}
int main() {
	int n, m, q, i, j, k, _k, block;
	scanf("%d%d", &n, &m);
	for (i = 1; i <= m; ++i) 
		scanf("%d%d", &::e[i].first, &::e[i].second);
	scanf("%d", &q);
	for (i = 1; i <= q; ++i) {
		scanf("%d", &_k);
		gets(::s + 1); k = 0;
		for (char *it = ::s + 1; *it; ++it)
			if (isdight(*it) && !isdight(it[1]))
				++k;
		::ans[i] = k ^ _k;
	}
	for (i = 1; i < q; ++i)
		puts((::ans[i + 1] ^ ::ans[i]) ? "Connected" : "Disconnected");
	
	for (i = *::s = 1, k = 0; ::s[i - 1]; ++i)
		if (isdight(::s[i]))
			k = k * 10 + ::s[i] - '0';
		else if (isdight(::s[i - 1]))
			::mark[k ^ ::ans[q]] = 1, k = 0;
	block = n;
	for (i = 1; i <= n; ++i)
		::fa[i] = i;

	for (i = 1; i <= m; ++i)
		if (!mark[i] && uni(e[i].first, e[i].second))
			--block;
	puts(block == 1 ? "Connected" : "Disconnected");
	return 0;
}
