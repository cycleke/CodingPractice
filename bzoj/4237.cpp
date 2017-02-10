#include <bits/stdc++.h>
#define N 200005
#define wlp while
struct P{int x, y;} p[N], t[N], s1[N], s2[N];
bool operator < (const P &a, const P &b) {
	return a.x < b.x;
}
long long ans;
int tp1, tp2;
inline int gi() {
	static int a;
	static char c;
	wlp (c = getchar(), c < '0'); a = c - '0';
	wlp (c = getchar(), '-' < c) a = (a << 3) + (a << 1) + c - '0';
	return a;
}
inline void conbi(const int &x, int l, int r) {
	for (static int m; l <= r; )
		if (s2[m = l + r >> 1].y < x)
			l = m + 1;
		else
			r = m - 1;
	ans += tp2 - (l - 1);
}
void divide(int l, int r) {
	if (l >= r) return;
	int m = l + r >> 1;
	divide(l, m); divide(m + 1, r);
	tp1 = tp2 = 0;
	for (register int i = m + 1, pos = l; i <= r; ++i) {
		wlp (tp1 && s1[tp1].x > p[i].x) --tp1;
		s1[++tp1] = p[i];
		wlp (pos <= m && p[pos].y < p[i].y) {
			while (tp2 && s2[tp2].x < p[pos].x) --tp2;
			s2[++tp2] = p[pos++];
		}
		conbi(s1[tp1 - 1].y, 1, tp2);
	}
	for (register int i = l, i1 = l, i2 = m + 1; i <= r; ++i)
		if (i1 > m || (i2 <= r && p[i2].y < p[i1].y))
			t[i] = p[i2++];
		else
			t[i] = p[i1++];
	for (register int i = l; i <= r; ++i)
		p[i] = t[i];
}

int main() {
	//freopen("t.in", "r", stdin);
	int n = gi();
	//scanf("%d", &n);
	for (register int i = 0; i < n; ++i)
		//scanf("%d%d", &p[i].x, &p[i].y);
		p[i] = (P){gi(), gi()};
	std::sort(p, p + n);
	divide(0, n - 1);
	printf("%lld\n", ans);
	return 0;
}
