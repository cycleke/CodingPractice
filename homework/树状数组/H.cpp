#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

const int Maxn = 2010, INF = 0x7f7f7f7f;
typedef long long LL;

LL gcd(LL a, LL b) {
	for (LL t; b; t = a % b, a = b, b = t);
	return a;
}

struct Point {
	int x, y;
	Point() { x = y = 0; }
	void Read() {
		scanf("%d%d", &x, &y);
	}
	bool operator < (const Point& a) const {
		if (x != a.x) return x < a.x;
		return y < a.y;
	}
}p[Maxn];

struct Vec {
	int x, y; LL a, b;
	Vec() {}
	Vec(const Point &A, const Point &B) {
		x = A.x - B.x, y = A.y - B.y;
		if (x == 0) {
			a = INF, b = A.x;
		} else if ((LL)x * A.y == (LL)y * A.x){
			a = b = 0;
		} else {
			LL g = gcd((LL)x, (LL)x * A.y - (LL)y * A.x);
			a = ((LL)x * A.y - (LL)y * A.x) / g;
			b = x / g;
		}
	}
	bool operator < (const Vec &A) const {
		if (x != A.x) return x < A.x;
		if (y != A.y) return y < A.y;
		if (a != A.a) return a < A.a;
		return b < A.b;
	}
}V[Maxn * Maxn];

int main() {
	int n, totv = 0, i, j, l, r; LL ans = 0;
	scanf("%d", &n);
	for (i = 1; i <= n; ++i) p[i].Read();
	sort(p + 1, p + n + 1); 
	for(i = 1 , j = 2; j <= n; ++j) {
        if(p[i].x == p[j].x && p[i].y == p[j].y) continue;
        p[++i]=p[j]; 
    }
    n = i;
	for (i = 1; i <= n; ++i)
		for (j = 1; j <= n; ++j) 
			if (i != j) {
				++totv;
				V[totv] = Vec(p[i], p[j]);
			}
	sort(V + 1, V + totv + 1);
	for (i = 1, j = 2; j <= totv + 1; ++j) 
		if (j > totv || V[i].x != V[j].x || V[i].y != V[j].y) {
			for (l = i, r = i + 1; r <= j; ++r) 
				if (r == j || V[l].a != V[r].a || V[l].b != V[r].b) 
					ans += ((LL)r - l) * ((LL)l - i), l = r;
			i = j;
		}
	printf("%lld\n", ans >> 2);
	return 0;
}
