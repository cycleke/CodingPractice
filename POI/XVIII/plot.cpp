#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <algorithm>

#define eps 1e-10
#define MaxN 100005

struct Point {
	double x, y;
} b[MaxN], O;
int n, m;

inline double disc(const Point &a, const Point &b) {
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}
inline Point Center(const Point &a, const Point &b, const Point &c) {
	double a1 = b.x - a.x, b1 = b.y - a.y, c1 = (a1 * a1 + b1 * b1) / 2.0;
	double a2 = c.x - a.x, b2 = c.y - a.y, c2 = (a2 * a2 + b2 * b2) / 2.0;
	double d = a1 * b2 - a2 * b1;
	return (Point) {a.x + (c1 * b2 - c2 * b1) / d, a.y + (a1 * c2 - a2 * c1) / d};
}
inline int r32() {
	return ((rand() << 16) | (rand())) & (~0U >> 1);
}
inline void min_cover(int l, int r, double &R) {
	static Point a[MaxN];
	int i, j, k, n = 0;
	for (i = l; i <= r; ++i) a[n++] = b[i];
	for (i = 0; i < n; ++i) std::swap(a[i], a[r32() % n]);
	O = a[0];
	R = 0.0;
	for (i = 1; i < n; ++i)
		if (disc(a[i], O) > R + eps) {
			O = a[i], R = 0;
			for (j = 0; j < i; ++j)
				if (disc(a[j], O) > R + eps) {
					O = (Point) {(a[i].x + a[j].x) / 2.0, (a[i].y + a[j].y) / 2.0};
					R = disc(a[i], O);
					for (k = 0; k < j; ++k)
						if (disc(a[k], O) > R + eps) {
							O = Center(a[i], a[j], a[k]);
							R = disc(O, a[i]);
						}
				}
		}
}

inline bool check(const double &x, int &now) {
	int i, j, l, r, mid;
	double R;
	now = 0;
	for (i = 1; i <= n; i = l) {
		for (j = 1; i + j - 1 <= n; j <<= 1) {
			min_cover(i, i + j - 1, R);
			if (R > x + eps)
				break;
		}
		l = i + (j >> 1) - 1, r = std::min(i + j - 1, n);
		while (l <= r) {
			mid = (l + r) >> 1;
			min_cover(i, mid, R);
			if (R > x + eps)
				r = mid - 1;
			else
				l = mid + 1;
		}
		if (++now > m)
			return false;
	}
	return true;
}


inline void output(const double &x) {
	double R;
	Point o;
	int i, j, l, r, mid;
	for (i = 1; i <= n; i = l) {
		for (j = 1; i + j - 1 <= n; j <<= 1) {
			min_cover(i, i + j - 1, R);
			if (R > x + eps)
				break;
		}
		l = i + (j >> 1) - 1, r = std::min(i + j - 1, n);
		while (l <= r) {
			mid = (l + r) >> 1;
			min_cover(i, mid, R);
			if (R > x + eps)
				r = mid - 1;
			else {
				l = mid + 1;
				o = O;
			}
		}
		printf("%.8lf %.8lf\n", o.x, o.y);
	}
}


int main() {
	srand(10007);
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i)
		scanf("%lf%lf", &b[i].x, &b[i].y);
	if (m == 1) {
		double R;
		min_cover(1, n, R);
		printf("%.8lf\n1\n%.8lf %.8lf\n", R, O.x, O.y);
		return 0;
	}
	double l = 0, r, mid;
	int ans = m, tmp;
	min_cover(1, n, r);
	for (int _ = 0; _ ^ 45; ++_) {
		mid = (l + r) / 2.0;
		if (check(mid, tmp)) {
			r = mid;
			ans = tmp;
		} else
			l = mid;
	}
	printf("%.8lf\n%d\n", r, ans);
	output(r);
	return 0;
}
