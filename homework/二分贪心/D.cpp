#include <cstdio>
#include <cstring>
#include <cmath>

const double eps = 1e-9, Pi = acos(-1.);

template<class T> 
T max(const T &a, const T &b) {
	return (a > b) ? a : b;
}
template<class T>
T min(const T &a, const T &b) {
	return (a < b) ? a : b;
}


struct point {
	int x, y;
	void Read() {
		scanf("%d%d", &x, &y);
	}
	bool operator < (const point& a) const {
		if (x == a.x) return y < a.y;
		return x < a.x;
	}
};

point H[35];
int N;

double Try(const double &ang) {
	double _x, _y, maxx, maxy, minx, miny;
	double sa = sin(ang), ca = cos(ang);
	maxx = maxy = 0.; minx = miny = 1e9;
	for (int i = N; i; --i) {
		_x = H[i].x * sa - H[i].y * ca;
		_y = H[i].x * ca + H[i].y * sa;
		maxx = max(maxx, _x); minx = min(minx, _x);
		maxy = max(maxy, _y); miny = min(miny, _y);
	}
	return max(maxx - minx, maxy - miny);
}

void Work() {
	scanf("%d", &N);
	for (int i = N; i; --i) H[i].Read();
	double l = 0, r = Pi, mid1, mid2;
	double ans1, ans2;
	while (r - l > eps) {
		mid1 = (l + r) / 2.;
		mid2 = (mid1 + r) / 2.;
		if (Try(mid1) < Try(mid2)) r = mid2;
		else l = mid1;
	}
	ans1 = Try(l);
	printf("%.2lf\n", ans1 * ans1);
}

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		Work();
	}
	return 0;
}
