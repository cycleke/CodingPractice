#include <cstdio>
inline char gc() {
	static char b[1<<16], *s=b, *e=b;
	if (s >= e) e = (s = b) + fread(b, 1, 1<<16, stdin);
	return (s >= e) ? 0 : *s++;
}
inline void gi(int &a) {
	char c;
	while (c = gc(), c < '0'); a = c - '0';
	while (c = gc(), '-' < c) a = (a << 3) + (a << 1) + c - '0';
}
#define nsc(c) ((c < 'A' || 'Z' < c) && (c ^ '*') && (c ^ '?'))
inline void gs(char *s, int &len) {
	for (len = 0; *s = gc(), nsc(*s); );
	for (*(s + 1) = *s, *s = 0, ++s, len = 1; *++s = gc(), !nsc(*s); ++len);
}
char dp[1003][503], a[1003], b[503];
int main() {
	//freopen("1966.in", "r", stdin);
	int n, m, _, __ = 0, i, j;
	gs(a, n);
	gi(_);
	if (a[1] == '*') dp[1][0] = 1;
	dp[0][0] = 1;
	while (_--) {
		gs(b, m);
		for (i = 1; i <= n; ++i)
			for (j = 1; j <= m; ++j)
				if (a[i] == '*') dp[i][j] = dp[i - 1][j - 1] | dp[i][j - 1] | dp[i - 1][j];
				else if (!(a[i] ^ b[j]) || !(a[i] ^ '?')) dp[i][j] = dp[i - 1][j - 1];
				else dp[i][j] = 0;
		__ += !dp[n][m];
	}
	printf("%d\n", __);
}
