#include <cstdio>
#include <cmath>

const double Pi = acos(-1.), eps = 1e-6;
double S;
double p2(const double &a) { return a * a; }

double geth(const double &r) {
	double tmp = S - Pi * p2(r);
	tmp /= Pi * r;
	tmp = p2(tmp) - p2(r);
	if (tmp <= 0) return -1;
	return sqrt(tmp);
}

int main() {
	double l, r, md, mdd, h1, h2;
	while (scanf("%lf", &S) == 1) {
		l = 0, r = sqrt(S / (2. * Pi));
		while (r - l > eps) {
			md = (l + r) / 2., mdd = (md + r) / 2.;
			h1 = geth(md), h2 = geth(mdd);
			if (h1 * p2(md) < h2 * p2(mdd)) l = md;
			else r = mdd;
		}
		h1 = geth(l);
		printf("%.2lf\n%.2lf\n%.2lf\n", h1 * Pi * p2(l) / 3., h1, l);
	}
	
	return 0;
}
