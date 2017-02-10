#include <cstdio>
#define N 100003
int mo;
struct node {
	int sum, add, mul, l, r;
	bool noneed() const {
		return !(add || (mul ^ 1));
	}
	void modify(const int &a, const int &b) {
		add = ((long long)a * add + b) % mo;
		mul = (long long)mul * a % mo;
		sum = ((long long)sum * a + b * (r - l + 1LL)) % mo;
	}
	void done() {
		add = 0;
		mul = 1;
	}
}C[N<<2|1];
inline int gi() {
	static int a;
	static char c;
	while (c = getchar(), c < '0'); a = c - '0';
	while (c = getchar(), '-' < c) a = (a << 3) + (a << 1) + c - '0';
	return a;
}
#define ls u << 1
#define rs u << 1 | 1
inline int mmo(const int &x) {return x < mo ? x : x - mo;}
inline void pu(const int &u) {
	C[u].sum = mmo(C[u<<1].sum + C[u<<1|1].sum);
}
void build(int u, int l, int r) {
	if (l ^ r) {
		build(ls, l, (l + r) >> 1);
		build(rs, (l + r >> 1) + 1, r);
		C[u] = (node) {mmo(C[ls].sum + C[rs].sum), 0, 1, l, r};
	} else C[u] = (node) {gi() % mo, 0, 1, l, r};
}
inline void pd(const int &u) {
	if (C[u].noneed()) return;
	C[ls].modify(C[u].mul, C[u].add);
	C[rs].modify(C[u].mul, C[u].add);
	C[u].done();
}
void upd(int u, const int &x, const int &y, const int &a, const int &b) {
	if (x <= C[u].l && C[u].r <= y) return C[u].modify(a, b);
	int m = C[u].l + C[u].r >> 1; pd(u);
	if (x <= m) upd(ls, x, y, a, b);
	if (y >  m) upd(rs, x, y, a, b);
	pu(u);
}
int quy(int u, const int &x, const int &y, int &v) {
	if (x <= C[u].l && C[u].r <= y)
	  return v = mmo(v + C[u].sum);
	int m = C[u].l + C[u].r >> 1; pd(u);
	if (x <= m) quy(ls, x, y, v);
	if (y >  m) quy(rs, x, y, v);
}
int main() {
	int n, m, opt, t, g, c; 
	n = gi(), mo = gi();
	build(1, 1, n);
	m = gi();
	while (m--) {
		opt = gi(), t = gi(), g = gi();
		if (opt < 3) (opt & 1) ? upd(1, t, g, gi() % mo, 0) : upd(1, t, g, 1, gi() % mo);
		else {
			c = 0;
			quy(1, t, g, c);
			printf("%d\n", c);
		}
	}
	return 0;
}
