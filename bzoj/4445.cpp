#include <cmath>
#include <cstdio>
#include <algorithm>
const int MaxN = 1e5 + 7;
struct FI {
	char b[5<<19], *s, sign;
	FI() : s(b) {
		b[fread(b, 1, 5 << 19, stdin)] = 0;
	}
	inline void gi(int &a) {
		sign = a = 0;
		while (*s < 48) if (*s++ == 45) sign = 1;
		while (32 < *s) a = (a << 3) + (a << 1) + *s++ - 48;
		if (sign) a = -a;
	}
} io;
struct point {
	double x, y;
	point() {}
	point(double x, double y) :
		x(x), y(y) {}
} s[MaxN], p[MaxN];
struct line {
	point p, v;
	double ang;
	line() {}
	line(point p, point v) :
		p(p), v(v), ang(atan2(v.y, v.x)) {}
} q[MaxN], t[MaxN];
inline point operator + (const point &a, const point &b) {
	return point(a.x + b.x, a.y + b.y);
}
inline point operator - (const point &a, const point &b) {
	return point(a.x - b.x, a.y - b.y);
}
inline point operator * (const double &k, const point &a) {
	return point(k * a.x, k * a.y);
}
inline double operator * (const point &a, const point &b) {
	return a.x * b.y - a.y * b.x;
}
inline bool operator < (const line &a, const line &b) {
	return a.ang < b.ang;
}
inline bool judge(const point &a, const line &b) {
	return (a - b.p) * b.v > 0;
}
inline point getpoint(const line &a, const line &b) {
	return a.p + (b.v * (a.p - b.p)) / (a.v * b.v) * a.v;
}
#define nxt(a) ((a + 1) < n ? (a + 1) : 0)
inline double area(const point *a, const int &n) {
	double u_u = 0.0;
	for (register int o_o = 0; o_o < n; ++o_o)
		u_u += a[o_o] * a[nxt(o_o)];
	return u_u;
}
int main() {
	int n, m = 0, bot = 1, top = 0;
	io.gi(n);
	for (register int i = 0; i < n; ++i) {
		static int x, y;
		io.gi(x), io.gi(y);
		p[i].x = x;
		p[i].y = y;
	}
	for (register int i = 1, j = nxt(i); i < n; ++i, j = nxt(i)) {
		static double a, b, c;
		a = p[i].y - p[j].y - p[0].y + p[1].y;
		b = p[j].x - p[i].x - p[1].x + p[0].x;
		c = p[i] * p[j] - p[0] * p[1];
		q[m++] = line(a ? point(-c / a, 0) : point(0, -c / b), point(b, -a));
	}
	q[m++] = line(p[0], p[1] - p[0]);
	std::sort(q, q + m);
	for (register int i = 0; i < m; ++i) {
		while (bot < top && judge(s[top - 1], q[i])) --top;
		while (bot < top && judge(s[bot], q[i])) ++bot;
		if (bot > top || q[i].ang != t[top].ang)
			t[++top] = q[i], s[top - 1] = getpoint(t[top], t[top - 1]);
	}
	while (bot < top && judge(s[top - 1], t[bot])) --top;
	if (top > bot + 1) s[top] = getpoint(t[top], t[bot]);
	printf("%.4lf\n", area(s + bot, top - bot + 1) / area(p, n));
	return 0;
}
