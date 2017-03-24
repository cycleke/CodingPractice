#include <cstdio>
#include <cstring>
#include <algorithm>

const int maxn(3e5 + 1e2);
typedef int arr[maxn];
#define rep(i, l, r) for (i = l; i < r; ++i)

inline bool cmp(int *r, int i, int j, int len) {
	return r[i] == r[j] && r[i + len] == r[j + len];
}

arr str, sa, rk, ht, ta, tb;

inline void da(int n, int m) {
	int i, j, p, *x = ta, *y = tb, *t;
	static arr s;
	rep(i, 0, m) s[i] = 0;
	rep(i, 0, n) ++s[x[i] = str[i]];
	rep(i, 1, m) s[i] += s[i - 1];
	for (i = n - 1; ~i; --i) sa[--s[x[i]]] = i;
	for (p = j = 1; p < n; j <<= 1, m = p) {
		for (p = 0, i = n - j; i < n; ++i) y[p++] = i;
		rep(i, 0, n) if (sa[i] >= j) y[p++] = sa[i] - j;
		rep(i, 0, m) s[i] = 0;
		rep(i, 0, n) ++s[x[y[i]]];
		rep(i, 1, m) s[i] += s[i - 1];
		for (i = n - 1; ~i; --i) sa[--s[x[y[i]]]] = y[i];
		for (t = x, x = y, y = t, i = p = 1, x[sa[0]] = 0; i < n; ++i)
			x[sa[i]] = cmp(y, sa[i], sa[i - 1], j) ? p - 1 : p++;
		//rep(i, 0, n) printf("%d ", sa[i]);
		//puts("");
	}
}

inline void calcht(int n) {
	int i, j, k(0);
	rep(i, 0, n) rk[sa[i]] = i;
	for (i = 0; i < n; ht[rk[i++]] = k)
		if (rk[i]) for (k ? --k : 0, j = sa[rk[i] - 1]; str[i + k] == str[j + k]; ++k);
}

arr vis, ans, from, que, length;

int main() {

	//freopen("2754.in", "r", stdin);

	int n, m, _vis(0), x, len(0);

	scanf("%d%d", &n, &m);

	memset(from, -1, sizeof from);
	for (register int i = 0; i < n; ++i) {
		scanf("%d", &x);
		for (register int j = 0; j < x; ++j)
			scanf("%d", &str[len]), from[len++] = i;
		str[len++] = 10001;
		scanf("%d", &x);
		for (register int j = 0; j < x; ++j)
			scanf("%d", &str[len]), from[len++] = i;
		str[len++] = 10001;
	}

	for (register int i = 0; i < m; ++i) {
		scanf("%d", &x);
		que[i] = len;
		length[i] = x;
		for (register int j = 0; j < x; ++j)
			scanf("%d", &str[len++]);
		str[len++] = 10001;
	}
	str[len] = -1;
	da(len, 10002);
	calcht(len);
	for (register int i = 0; i < m; ++i) {
		static int p, tot;
		tot = 0;
		++_vis;
		p = rk[que[i]];
		while (ht[p] >= length[i]) {
			if ((~from[sa[p - 1]]) && (vis[from[sa[p - 1]]] ^ _vis)) {
				vis[from[sa[p - 1]]] = _vis;
				++tot;
				++ans[from[sa[p - 1]]];
			}
			if (!--p) break;
		}
		p = rk[que[i]];
		while (ht[p + 1] >= length[i]) {
			if ((~from[sa[p + 1]]) && (vis[from[sa[p + 1]]] ^ _vis)) {
				vis[from[sa[p + 1]]] = _vis;
				++tot;
				++ans[from[sa[p + 1]]];
			}
			if (++p >= len) break;
		}
		printf("%d\n", tot);
	}
	printf("%d", ans[0]);
	for (register int i = 1; i < n; ++i) printf(" %d", ans[i]);
	return 0;
}
