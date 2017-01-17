#include <cstdio>
#include <cstring>
#include <algorithm>
inline int gi() {
	static int a; static char c, f;
	for (f = 0; (c = getchar()) < '0';) f|= c == '-';
	for (a = c - '0'; '-' < (c = getchar());) a = (a << 3) + (a << 1) + c - '0';
	return f ? -a : a;
}
int n, Max, Min;
long long a, b, c;
struct D {
	int s, h; long long sum;
	inline D input() {
		h = gi(), s = gi();
		sum = a * h + b * s;
		return *this;
	}
}dh[5003], dsum[5003];
bool ch(const D &a, const D &b) {
	return a.h < b.h;
}
bool csum(const D &a, const D &b) {
	return a.sum < b.sum;
}
bool g(const D &a) {
	return a.s <= Max && a.s >= Min;
}
int main() {
	int i, j, k, ans = 0, cnt = 0, l, r;
	long long t;
	n = gi();
	scanf("%lld%lld%lld", &a, &b, &c);
	for (i = 0; i < n; ++i) dh[i] = dsum[i].input();
	std::sort(dh, dh + n, ch);
	std::sort(dsum, dsum + n, csum);
	for (i = 0; i < n; ++i) {
		l = r = -1; cnt = 0;
		Min = dh[i].s, Max = Min + c / b;
		for (j = 0; j < n; ++j) {
			t = a * dh[j].h + b * dh[i].s + c;
			while (r + 1 < n && dsum[r + 1].sum <= t)
				cnt += g(dsum[++r]);
			while (l + 1 < n && dh[l+1].h < dh[j].h)
				cnt -= g(dh[++l]);
			if (ans < cnt) ans = cnt;
		}
	}
	printf("%d\n", ans);
	return 0;
}
