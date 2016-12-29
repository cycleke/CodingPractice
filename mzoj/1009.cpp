#include <cstdio>
#include <iostream>
typedef long long LL;

inline LL Cal(const int &a, const int &b, const int &c, const int &l) {
	if (a < b + c) return 0LL;
	LL t = std::min(a - b - c, l);
	return (t + 1LL) * (t + 2LL) >> 1;
}

int main() {
	int a, b, c, l;
	LL ans;
	scanf("%d%d%d%d", &a, &b, &c, &l);
	ans = 1;
	for (LL i = 1; i <= l; ++i) {
		ans += ((i + 1LL) * (i + 2LL) >> 1);
	}
	for (int i = 0; i <= l; ++i) {
		ans -= Cal(a + i, b, c, l - i);
		ans -= Cal(b + i, a, c, l - i);
		ans -= Cal(c + i, a, b, l - i);
	}
	printf("%lld\n", ans);
	return 0;
}
