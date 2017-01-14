#include <cstdio>
#include <algorithm>
const int N = 50013;
const double eps = 1e-9;
struct point {
	double x, y;
	void input() {
		scanf("%lf%lf", &x, &y);
	}
	point() {}
	point(double _x, double _y) : x(_x), y(_y) {}
	point operator + (const point &a) const {
		return point(x + a.x, y + a.y);
	}
	point operator - (const point &a) const {
		return point(x - a.x, y - a.y);
	}
	point operator * (const double &a) const {
		return point(a * x, a * y);
	}
	double operator * (const point &a) const {
		return x * a.y - y * a.x;
	}
	bool operator < (const point &a) const {
		return (x != a.x) ? x < a.x : y > a.y;
	}
}pt[N];
int stk1[N], stk2[N], tp1, tp2, n;
void cmax(double &a, double b) {
	if (a < b) a = b;
}
double rotating() {
	double ret = 0;
	for (int i = 0; i < tp2; ++i) {
		int p = 1, q = 1;
		for (int j = i + 2; j < tp2; ++j) {
			while (((pt[stk2[p + 1]] - pt[stk2[i]]) * (pt[stk2[j]] - pt[stk2[i]])) > ((pt[stk2[p]] - pt[stk2[i]]) * (pt[stk2[j]] - pt[stk2[i]])))
				if (++p >= tp2) p = 0;
			while (((pt[stk2[j]] - pt[stk2[i]]) * (pt[stk2[q + 1]] - pt[stk2[i]])) > ((pt[stk2[j]] - pt[stk2[i]]) * (pt[stk2[q]] - pt[stk2[i]])))
				if (++q >= tp2) q = 0;
			cmax(ret,
				 ((pt[stk2[p]] - pt[stk2[i]]) * (pt[stk2[j]] - pt[stk2[i]])) + ((pt[stk2[j]] - pt[stk2[i]]) * (pt[stk2[q]] - pt[stk2[i]]))
				);
		}
	}
	return ret;
}
int main() {
	freopen("1069.in", "r", stdin);
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) pt[i].input();
	std::sort(pt + 1, pt + n +1);
	tp1 = 0;
	tp2 = -1;
	for (int i = 1; i <= n; ++i) {
		while (tp1 > 1&& ((pt[i] - pt[stk1[tp1]]) * (pt[stk1[tp1]] - pt[stk1[tp1 - 1]])) >= 0) --tp1;
		stk1[++tp1] = i;
	}
	for (int i = 1; i < tp1; ++i)
		stk2[++tp2] = stk1[i];
	tp1 = 0;
	for (int i = 1; i <= n; ++i) {
		while (tp1 > 1&& ((pt[i] - pt[stk1[tp1]]) * (pt[stk1[tp1]] - pt[stk1[tp1 - 1]])) <= 0) --tp1;
		stk1[++tp1] = i;
	}
	for (int i = tp1; i; --i)
		stk2[++tp2] = stk1[i];
	printf("%.3lf\n", rotating() / 2.0);
	return 0;
}
