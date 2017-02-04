#include <cmath>
#include <cstdio>
#include <algorithm>
 
#define N 50005
 
struct P {
    double x, y;
    P() {}
    P(double _x, double _y) : x(_x), y(_y) {}
}p[N], hull[N], pivot, rect[8];
 
inline int zero(const double &a) {
    return fabs(a) < 1e-4;
}
inline int sign(const double &a) {
    if (fabs(a) < 1e-8)
        return 0;
    return a < 0 ? -1 : 1;
}
inline double cross(const P &A, const P &B, const P &C) {
    return (B.x - A.x) * (C.y - A.y) - (B.y - A.y) * (C.x - A.x);
}
inline double dis2(const P &A, const P &B) {
    return (A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y);
}
inline bool cmp(const P &A, const P &B) {
    double t = cross(pivot, A, B);
    return (sign(t) == 1) || (sign(t) == 0 && sign(dis2(pivot, A) - dis2(pivot, B)) == -1);
}
 
inline void convexhull(int n, P *s, int &size) {
    int i, tp, k;
    for (k = 0, i = 1; i < n; ++i)
        if (::p[i].y < ::p[k].y || (::p[i].y == ::p[k].y && ::p[i].x < ::p[k].x)) k = i;
    pivot = ::p[k], ::p[k] = ::p[0], ::p[0] = pivot;
    std::sort(::p + 1, ::p + n, cmp);
    s[0] = pivot, s[1] = ::p[1];
    for (tp = 1, i = 2; i < n; ++i) {
        while (tp && sign(cross(::p[i], s[tp], s[tp - 1])) >= 0)
            --tp;
        s[++tp] = ::p[i];
    }
    size = tp + 1;
}
 
inline double area(const P &A, const P &B, const P &C) {
    return fabs(cross(A, B, C));
}
inline P vertical(const P &A, const P &B) {
    return P(A.x - B.y + A.y, A.y + B.x - A.x);
}
 
#define nxt(a) ((++a) < n ? (a) : (a = 0))
 
bool del[N];
 
int main() {
    int n, i, j, k, l, r;
    P A, B, C;
    double ans = 1e22, t, w, h, _len;
    scanf("%d", &n);
    for (i = 0; i < n; ++i) 
        scanf("%lf%lf", &p[i].x, &p[i].y);
    convexhull(n, hull, n);
    for (i = 1; i < n; ++i)
        del[i] = zero(hull[i].x - hull[i - 1].x) && zero(hull[i].y - hull[i - 1].y);
    for (k = i = 0; i < n; ++i)
        if (!del[i]) hull[k++] = hull[i];
    for (hull[n = k] = hull[i = j = l = r = 0]; i < n; ++i) {
        A = hull[i], B = hull[i + 1];
        C = vertical(A, B);
        while (sign(area(A, B, hull[j]) - area(A, B, hull[j + 1])) < 1) nxt(j);
        while (sign(cross(A, C, hull[l]) - cross(A, C, hull[l + 1])) < 1) nxt(l);
        while (sign(cross(A, C, hull[r]) - cross(A, C, hull[r + 1])) > -1) nxt(r);
        _len = 1.0 / sqrt(dis2(A, B));
        h = area(A, B, hull[j]) * _len;
        w = (cross(A, C, hull[l]) - cross(A, C, hull[r])) * _len;
        if (sign(h * w - ans) == -1) {//update ans
            ans = h * w;
 
            t = area(A, B, hull[l]) * _len * _len;
            rect[0] = P(hull[l].x + t * (A.x - C.x), hull[l].y + t * (A.y - C.y));
 
            t = h * _len;
            rect[3] = P(rect[0].x + t * (C.x - A.x), rect[0].y + t * (C.y - A.y));
             
            t = w * _len;
            rect[1] = P(rect[0].x + t * (B.x - A.x), rect[0].y + t * (B.y - A.y));
            rect[2] = P(rect[3].x + t * (B.x - A.x), rect[3].y + t * (B.y - A.y));
        }
    }
    for (i = 0; i ^ 4; ++i)
        rect[i + 4] = rect[i];
    for (j = 0, i = 1; i ^ 4; ++i)
        if (sign(rect[i].y - rect[j].y) == -1 || (sign(rect[i].y - rect[j].y) == 0 && sign(rect[i].x - rect[j].x) == -1))
            j = i;
    printf("%.0f.00000\n", ans);
    //printf("%.5lf\n", ans);
    for (i = 0; i ^ 4; ++i)
        printf("%.0lf.00000 %.0lf.00000\n", rect[j + i].x, rect[j + i].y);
	//printf("%.5lf %.5lf\n", rect[j + i].x, rect[j + i].y);
    return 0;
}
