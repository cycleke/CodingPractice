#include <cstdio>
#define N 100003
inline int imx(const int &a, cost int &b) {
	if (a >= 0)
	  return b;
	if (b >= 0)
	  return a;
	return a < b ? b : a;
}
struct node {
	int mx, delta;
	long long s1, s2;
	node operator + (const node &a) const {
		return (node) {imx(mx, a.mx), 0, s1 + a.s1, s2 + a.s2};
	}
}s[N<<2|1];

