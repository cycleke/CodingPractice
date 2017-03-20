#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;
const int MaxN = 30005;
int dq[MaxN], order[MaxN], n, cnt;
struct point {
	double x, y;
	point(double x = 0, double y = 0) :
		x(x), y(y) {}
} p[MaxN];
struct line {
	point a, b;
	double ang;
} l[MaxN];
inline int sign(const double &x) {
	if (fabs(x) < 1e-10) return 0;
	return x < 0 ? -1 : 1;
}
inline double area(const point &a, const point &b, const point &c) {
	return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}
inline bool cmp(const int &x, const int &y) {
	register int d = sign(l[x].ang - l[y].ang);
	if (d)
	  return d < 0;
	else
	  return sign(area(l[x].a, l[y].a, l[y].b)) > 0;
}
inline void add_line(const double &x1, const double &y1, const double &x2, const double &y2) {
	l[n].a = point(x1, y1);
	l[n].b = point(x2, y2);
	l[n].ang = atan2(y2 - y1, x2 - x1);
	order[n] = n;
	++n;
}
inline void getpoint(const line &l1, const line &l2, point &p) {
	static double dot1, dot2;
	dot1 = area(l2.a, l1.b, l1.a);
	dot2 = area(l1.b, l2.b, l1.a);
	p.x = (l2.a.x * dot2 + l2.b.x * dot1) / (dot2 + dot1);
	p.y = (l2.a.y * dot2 + l2.b.y * dot1) / (dot2 + dot1);
}
inline bool judge(const line &l0, const line &l1, const line &l2) {
	static point p;
	getpoint(l1, l2, p);
	return sign(area(p, l0.a, l0.b)) < 0;
}
inline void HPI() {
	sort(order, order + ::n, cmp);
	{
		register int i = 1, j = 0;
		for (; i < n; ++i)
		  if (sign(l[order[i]].ang - l[order[j]].ang) > 0)
			order[++j] = order[i];
		::n = j + 1;
	}
	int *bot = dq, *top = dq + 1;
	*bot = order[0];
	*top = order[1];
	for (register int i = 2; i < ::n; ++i) {
		while (bot < top && judge(l[order[i]], l[top[-1]], l[*top])) --top;
		while (bot < top && judge(l[order[i]], l[bot[ 1]], l[*bot])) ++bot;
		*++top = order[i];
	}
	while (bot < top && judge(l[*bot], l[top[-1]], l[*top])) --top;
	while (bot < top && judge(l[*top], l[bot[ 1]], l[*bot])) ++bot;
	::cnt = 0;
	for (register int *i = bot; i < top; ++i)
	  getpoint(l[*i], l[i[1]], p[::cnt++]);
	if (top > bot + 1)
	  getpoint(l[*top], l[*bot], p[::cnt++]);
}
inline double get_area() {
	double S = 0.0;
	for (register int i = 1; i < cnt - 1; ++i)
	  S += area(p[0], p[i], p[i + 1]);
	return fabs(S) / 2.0;
}
int main() {
	int n;
	double x1, x2, y1, y2;
	scanf("%d", &n);
	for (register int i = ::n = 0; i < n; ++i) {
		scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);
		add_line(x1, y1, x2, y2);
	}
	add_line(0, 0, 10000, 0);
	add_line(0, 10000, 0, 0);
	add_line(10000 , 0, 10000, 10000);
	add_line(10000 , 10000, 0, 10000);
	HPI();
	printf("%.1f\n", get_area());
	return 0;
}
