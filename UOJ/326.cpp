#include "triangles.h"
#include <cmath>
#include <algorithm>

typedef long long i64;

struct vec {
	int x, y;

	vec(){}
	vec(int x,  int y) : x(x), y(y) {}

	vec operator - (const vec &another) const {
		return vec(x - another.x, y - another.y);
	}
	i64 operator * (const vec &another) const {
		return (i64)x * another.y - (i64)y * another.x;
	}

};

struct point {
	vec v;
	int id, color;
	double angle;

	point() {}
	point(vec v, int id, int color, double angle) :
		v(v), id(id), color(color), angle(angle) {}

	bool operator < (const point &another) const {
		return angle < another.angle;
	}
};

const double pi = acos(-1.0);

void check_triangles(int n, int m, int *rx, int *ry, int *bx, int *by, int **result) {
	point *pbegin, *pend;
	pend = pbegin = new point[(n + m) << 1 | 1];

	for (int i = 0; i < n; ++i) {
		*pend++ = point(vec(rx[i], ry[i]), i, 1, atan2(ry[i], rx[i]));
	}
	for (int i = 0; i < m; ++i) {
		*pend++ = point(vec(bx[i], by[i]), i, 0, atan2(by[i], bx[i]));
	}
	std::sort(pbegin, pend);
	for (point *l(pbegin), *r(pbegin), *c(pend); l != pend; ++l, ++c) {
		*c = *l;
		c->angle += 2 * pi;
		while (r != c && r->angle - l->angle < pi) {
			++r;
		}
		if (l->color == 0) continue;
		int id = -1;
		vec v1(0, 0), v2;
		for (point *it = l; it != r; ++it) {
			v2 = it->v - l->v;
			if (it->color == 1) {
				int temp = v1 * v2 < 0 ? id : -1;
				if (l->id < it->id)
					result[l->id][it->id] = temp;
				else
					result[it->id][l->id] = temp;
			} else if (v1 * v2 >= 0) {
				id = it->id;
				v1 = v2;
			}
		}
	}

	delete pbegin;
}
