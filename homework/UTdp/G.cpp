#include <bits/stdc++.h>
using namespace std;

int dp[40000];
const int goal = (1 << 15) - 1;

inline bool check(int a, int b) {
	while (a && b) {
		if (a & 1 && b & 1) return false;
		a >>= 1; b >>= 1;
	}
	return true;
}

void SelfMin(int &a, const int &b) {
	if (b < a) a = b;
}

int main() {
	int d, n, a, c, sta;
	memset(dp, 0, sizeof dp);
	for (int i = 0; i < 15; ++i) {
		scanf("%d", &d);
		for (int p = 0; p <= goal; ++p)
			if (p & (1 << i)) dp[p] += d;
	}
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		scanf("%d", &d); sta = 0;
		for (int j = 0; j < d; ++j) {
			scanf("%d", &a); sta |= 1 << (a - 1);
		}
		scanf("%d", &c);
		if (dp[sta] <= c) continue;
		for (int p = 0; p < goal; ++p)
			if (check(p, sta)) SelfMin(dp[p | sta], dp[p] + c);
	}
	printf("%d\n", dp[goal]);
	return 0;
}
