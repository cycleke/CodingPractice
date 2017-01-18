#include <cstdio>
#include <cstring>
inline char gc() {
	static char buf[1<<16], *s = buf, *e = buf;
	if (s == e) e = (s = buf) + fread(buf, 1, 1<<16, stdin);
	return *s++;
}
inline int gi() {
	static int a; static char c;
	while ((c = gc()) < '0'); a = c - '0';
	while ('-' < (c = gc())) a = (a << 3) + (a << 1) + c - '0';
	return a;
}
int C[400003], ans, cur;
#define UP(u) ((C[u<<1]==C[u<<1|1]&&C[u]==-1)?C[u]=C[u<<1]:1)
#define DOWN(u) ((~C[u])?C[u<<1]=C[u<<1|1]=C[u],C[u]=-1:1)
void update(int u, int l, int r, const int &x, const int &y, const int &opt) {
	if (x <= l && r <= y) {
		if (opt < 2) return (void)(C[u] = opt);
		else if (~C[u]) return (void)(C[u] ^= 1);
	}DOWN(u);
	int m = l + r >> 1;
	if (x <= m) update(u<<1, l, m, x, y, opt);
	if (y >  m) update(u<<1|1, m + 1, r, x, y, opt);
}
int qsum(int u, int l, int r, const int &x, const int &y) {
	if (x <= l && r <= y)
		if (~C[u]) return C[u] ? r - l + 1 : 0;
	DOWN(u);
	int m = l + r >> 1, ret = 0;
	if (x <= m) ret += qsum(u<<1, l, m, x, y);
	if (y >  m) ret += qsum(u<<1|1, m + 1, r, x, y);
	return ret;
}
void q(int u, int l, int r, const int &x, const int &y) {
	if (x <= l && r <= y && (~C[u])) {
		if (C[u]) cur += r - l + 1;
		else cur = 0;
		if (ans < cur) ans = cur;
		return;
	}DOWN(u);
	int m = l + r >> 1;
	if (x <= m) q(u<<1, l, m, x, y);
	if (y > m) q(u<<1|1, m + 1, r, x, y);
}
int main() {
	int n, m, l, r, opt;
	n = gi(), m = gi(); r = n - 1;
	for (l = 0; l < n; ++l) update(1, 0, r, l, l, gi());
	--n;
	while (m--) {
		opt = gi(), l = gi(), r = gi();
		if (opt < 3) update(1, 0, n, l, r, opt);
		else if (opt < 4) printf("%d\n", qsum(1, 0, n, l, r));
		else {
			ans = cur = 0;
			q(1, 0, n, l, r);
			printf("%d\n", ans);
		}
	}
	return 0;
}
