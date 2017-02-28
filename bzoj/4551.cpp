#include <cstdio>

const int BUF = 1<<16|127;
inline char gc() {
    static char b[BUF], *s = b, *e = b;
    if (s == e) e = (s = b) + fread(b, 1, BUF, stdin);
    return (s == e) ? EOF : *s++;
}
 
inline void gi(int &a) {
    static char c;
    while (c = gc(), c < '0'); a = c - '0';
    while (c = gc(), '-' < c) a = (a << 3) + (a << 1) + c - '0';
}

typedef int _[100003];

_ f, fa, mark, X, opt, ans;

inline int gf(int u) {
	static int r, t;
	for (r = u; f[r] ^ r; r = f[r]);
	while (u ^ r) t = f[u], f[u] = r, u = t;
	return r;
}

int main() {
	char c;
	int n, q, u, v;
	gi(n), gi(q);
	for (register int i = 1; i < n; ++i) {
		gi(u), gi(v);
		fa[v] = u;
	}
	mark[1] = 1;
	for (register int i = 0; i < q; ++i) {
		do c = gc(); while ((c ^ 'Q') && (c ^ 'C'));
		gi(X[i]);
		if (c ^ 'Q') ++mark[X[i]], opt[i] = 1;
	}
	for (register int i = 1; i <= n; ++i)
		f[i] = mark[i] ? i : fa[i];
	for (register int i = q - 1; ~i; --i)
		if (opt[i]) {
			if (!--mark[X[i]]) f[X[i]] = fa[X[i]];
		} else ans[i] = gf(X[i]);
	for (register int i = 0; i < q; ++i)
		if (!opt[i]) printf("%d\n", ans[i]);
	return 0;
}
