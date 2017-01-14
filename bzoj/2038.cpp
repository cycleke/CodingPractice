#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>

const int N = 50003;

struct node {int l, r, ln, id;}a[N];
int up[N], down[N], cnt[N], col[N];

int gcd(int a, int b) {
	for (static int t; b; t = a % b, a = b, b = t);
	return a;
}

bool operator < (const node &a, const node &b) {
	return (a.ln ^ b.ln) ? (a.ln < b.ln) : ((a.ln & 1) ? b.r < a.r : a.r < b.r);
}

void giveans(int a, int b, int c) {
	if (!a) up[c] = 0, down[c] = 1;
	else {
		static int g;
		b = (long long)b * (b - 1) / 2;
		g = gcd(a, b);
		up[c] = a / g;
		down[c] = b / g;
	}
}

int main() {
	int n, m, l, r, i, rightchose = 0, tl, tr, t;
	scanf("%d%d", &n, &m);
	for (i = 1; i <= n; ++i) scanf("%d", col + i);
	t = sqrt(n + 0.5);
	for (i = 0; i < m; ++i) {
		scanf("%d%d", &l, &r);
		a[i] = (node){l, r, l / t, i};
	}
	std::sort(a, a + m);
	for (l = 1, r = 0, i = 0; i < m; ++i) {
		tl = a[i].l, tr = a[i].r;
		while (r < tr) {
			rightchose += cnt[col[++r]];
			++cnt[col[r]];
		}
		while (l > tl) {
			rightchose += cnt[col[--l]];
			++cnt[col[l]];
		}
		while (r > tr) {
			rightchose -= cnt[col[r]] - 1;
			--cnt[col[r--]];
		}
		while (l < tl) {
			rightchose -= cnt[col[l]] - 1;
			--cnt[col[l++]];
		}
		//printf("%d %d %d\n", tl, tr, rightchose);
		giveans(rightchose, tr - tl + 1, a[i].id);
	}
	for (i = 0; i < m; ++i) printf("%d/%d\n", up[i], down[i]);
	return 0;
}
