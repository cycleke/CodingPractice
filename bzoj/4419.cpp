#include <cstdio>
#define N 200001
#define M 500001
unsigned int x[M], y[M], a[N];
int s[N];
char opt[M];
int main() {
	unsigned int n, m;
	register unsigned int i = 0;
	scanf("%u%u", &n, &m);
	for (register char c; i < m; ++i) {
		do c = getchar(); while ((c ^ '!') && (c ^ '+') && (c ^ '-'));
		opt[i] = c;
		if (c ^ '!') scanf("%u%u", x + i, y + i);
		else scanf("%u", x + i);
	}
	for (i = m - 1; ~i; --i)
		if (opt[i] ^ '!') {
			if (opt[i] ^ '+') s[x[i]] -= a[y[i]], s[y[i]] -= a[x[i]];
			else s[x[i]] += a[y[i]], s[y[i]] += a[x[i]];
		} else ++a[x[i]];
	for (i = 1; i < n; ++i) printf("%u ", s[i]);
	return printf("%u", s[n]),0;
}
