#include <bits/stdc++.h>
#define wlp while
#define rep(i, l, r) for (i = l; i < r; ++i)
#define Rep(i, l, r) for (i = l; i <= r; ++i)
#define N 500005

int sa[N], h[N], lg[N], tarr[4][N], st[19][N];
bool cmp(int *r, int i, int j, int l) {
	return r[i] == r[j] && r[i + l] == r[j + l];
}
void da(char *a, int n, int m) {
	int i, j, p, *x = tarr[0], *y = tarr[1], *s = tarr[2], *v = tarr[3], *t;
	rep(i, 0, m) s[i] = 0;
	rep(i, 0, n) ++s[x[i] = a[i] - 'a'];
	rep(i, 1, m) s[i] += s[i - 1];
	for (i = n - 1; ~i; --i) sa[--s[x[i]]] = i;
	for (j = p = 1; p < n; j <<= 1, m = p) {
		for (p = 0, i = n - j; i < n; ++i) y[p++] = i;
		rep(i, 0, n) if (sa[i] >= j) y[p++] = sa[i] - j;
		rep(i, 0, m) s[i] = 0;
		rep(i, 0, n) ++s[v[i] = x[y[i]]];
		rep(i, 1, m) s[i] += s[i - 1];
		for (i = n - 1; ~i; --i) sa[--s[v[i]]] = y[i];
		for (t = x, x = y, y = t, p = i = 1, x[sa[0]] = 0; i < n; ++i)
			x[sa[i]] = cmp(y, sa[i], sa[i - 1], j) ? p - 1 : p++;
	}
}
void calheight(char *s, int n) {
	int i, j, k, *rk = tarr[0];
	rep(i, 0, n) rk[sa[i]] = i;
	for (i = k = 0; i < n; h[rk[i++]] = k)
		if (rk[i]) for (k ? --k : 0, j = sa[rk[i] - 1]; s[i + k] == s[j + k]; ++k);
}
void initst(int n) {
	int i, j, lgn = lg[n - 1] + 1;
	rep(i, 0, n) st[0][i] = h[i];
	Rep(j, 1, lgn) rep(i, 1, n - (1 << j - 1))
		st[j][i] = std::min(st[j - 1][i], st[j - 1][i + (1 << j - 1)]);
}
int ask(int l, int r) {
	static int t;
	t = lg[r - l + 1];
	return std::min(st[t][l], st[t][r - (1 << t) + 1]);
}
bool _cp(const int &a, const int &b) {
	return tarr[0][a] < tarr[0][b];
}
int stk[N], th[N], a[N];
char str[N];
int main() {
	//freopen("t.in", "r", stdin);
	int i, n, m, qk, *rk, tp;
	long long ans, _t;
	scanf("%d%d%s", &n, &m, str);
	lg[0] = -1;
	Rep(i, 1, n) lg[i] = lg[i>>1] + 1;
	da(str, n, 26);
	calheight(str, n);
	initst(n);

	rk = tarr[0];
	while (m--) {
		scanf("%d", &qk);
		Rep(i, 1, qk) scanf("%d", a + i), --a[i];
		std::sort(a + 1, a + qk + 1, _cp);
		qk = std::unique(a + 1, a + qk + 1) - a - 1;
		ans = _t = 0;
		stk[tp = 1] = 1;
		Rep(i, 2, qk) {
			th[i] = ask(rk[a[i - 1]] + 1, rk[a[i]]);
			while (1 < tp && th[stk[tp]] >= th[i]) {
				_t -= (long long)th[stk[tp]] * (stk[tp] - stk[tp - 1]);
				--tp;
			}
			_t += (long long)th[i] * (i - stk[tp]);
			stk[++tp] = i;
			ans += _t;
		}
		printf("%lld\n", ans);
	}
	
	return 0;
}
