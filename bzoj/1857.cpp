#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;
double p, q, r;
pair<double, double>pp[4];
const double eps = 1e-5;
inline double sqr(const double &a) {
	return a * a;
}
inline double dist(const pair<double, double> &a, const pair<double, double> &b) {
	return sqrt(sqr(a.first - b.first) + sqr(a.second - b.second));
}
inline pair<double, double> cal(const int &i, const int &j, const double &r) {
	return make_pair(pp[i].first + (pp[j].first - pp[i].first) * r, pp[i].second + (pp[j].second - pp[i].second) * r);
}
inline double g(const pair<double, double> &x, const pair<double, double> &y) {
	return dist(pp[0], x) / p + dist(x, y) / r + dist(y, pp[3]) / q;
}
inline double solve(const pair<double, double> &x) {
	static double L, R, seg, m1, m2;
	static pair<double, double> t1, t2;
	for (L = 0.0, R = 1.0; L + eps < R; ) {
		seg = (R - L) / 3.0;
		m1 = L + seg, m2 = R - seg;
		t1 = cal(2, 3, m1), t2 = cal(2, 3, m2);
		if (g(x, t1) < g(x, t2)) R = m2; else L = m1;
	}
	return g(x, cal(2, 3, L));
}
int main() {
	for (int i = 0, t1, t2; i < 4; ++i) {
		scanf("%d%d", &t1, &t2);
		pp[i] = make_pair((double)t1, (double)t2);
	}
	int t;
	scanf("%d", &t); p = t;
	scanf("%d", &t); q = t;
	scanf("%d", &t); r = t;
	double L = 0.0, R = 1.0, seg, m1, m2;
	pair<double, double> t1, t2;
	while (L + eps < R) {
		seg = (R - L) / 3.0;
		m1 = L + seg, m2 = R - seg;
		t1 = cal(0, 1, m1), t2 = cal(0, 1, m2);
		if (solve(t1) < solve(t2)) R = m2; else L = m1;
	}
	printf("%.2lf\n", solve(cal(0, 1, L)));
	return 0;
}
