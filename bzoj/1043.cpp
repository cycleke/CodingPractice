#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;
typedef pair <double, double> pdd;
#define X first
#define Y second
const double pi = acos(-1);
double x[1005], y[1005], r[1005];
int n, tp;
pdd q[1005];
inline double sqr(const double &a) {
	return a * a;
}
inline double dis(const int &i, const int &j) {
	return sqrt(sqr(x[i] - x[j]) + sqr(y[i] - y[j]));
}
inline bool inside(const int &i, const int &j) {
	return r[i] >= r[j] + dis(i, j);
}
inline void pb(const int &i, const int &j) {
	static double d, t, st, l;
	d = dis(i, j);
	t = (sqr(r[i]) + sqr(d) - sqr(r[j])) / (2 * d);
	st = atan2(x[i] - x[j], y[i] - y[j]);
	l = acos(t / r[i]);
	q[tp++] = make_pair(st - l, st + l);
}
double cal(const int &x) {
	for (int i = x + 1; i <= n; ++i)
		if (inside(i, x)) return 0.0;
	tp = 0;
	static double tmp, now;
	for (int i = x + 1; i <= n; ++i)
		if (!inside(x, i) && r[x] + r[i] >= dis(x, i)) pb(x, i);
	tmp = now = 0;
	for (int i = 0; i < tp; ++i) {
		if (q[i].X < 0) q[i].X += 2 * pi;
		if (q[i].Y < 0) q[i].Y += 2 * pi;
		if (q[i].X > q[i].Y) {
			q[tp++] = make_pair(0, q[i].Y);
			q[i].Y = 2 * pi;
		}
	}
	sort(q, q + tp);
	for (int i = 0; i < tp; ++i)
		if (q[i].X > now) {
			tmp += q[i].X - now;
			now = q[i].Y;
		} else now = max(now, q[i].Y);
	tmp += 2 * pi - now;
	return r[x] * tmp;
}
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i)
		scanf("%lf%lf%lf", r + i, x + i, y + i);
	double ans = 0;
	for (int i = 1; i <= n; ++i)
		ans += cal(i);
	printf("%.3lf", ans);
	return 0;
}
