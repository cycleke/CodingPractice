#include <cstdio>
#include <cstring>
#include <iostream>

int pre;
long long C[1000005 << 2];

int Update(int x, long long val) {
	for (C[x += pre] = val, x >>= 1; x; x >>= 1)
	  C[x] = std::max(C[x<<1], C[x<<1|1]);
}

long long Query(int l, int r) {
	long long ret = 1LL << 63;
	for (l = l + pre - 1, r = r + pre + 1; l ^ r ^ 1; l >>= 1, r >>= 1) {
		if (~l & 1) ret = std::max(ret, C[l^1]);
		if ( r & 1) ret = std::max(ret, C[r^1]);
	}
	return ret;
}

int main() {
	int n, k, a; long long Sum = 0, f, ans = 0, last = 0;
	scanf("%d%d", &n, &k);
	memset(C, 128, sizeof C);
	for (pre = 1; pre <= n + 1; pre <<= 1);
	for (int i = 1; i <= k; ++i) {
		scanf("%d", &a); Sum += a;
		f = Sum; Update(i, last - Sum); last = f;
	}
	for (int i = k + 1; i <= n; ++i) {
		scanf("%d", &a); Sum += a;
		f = Query(i - k, i - 1) + Sum;
		Update(i, last - Sum); last = f;
		if (f > ans) ans = f;
	}
	printf("%lld\n", ans);
	return 0;
}
