#include <cstdio>
#include <cstdlib>
int n, k;
int a[2010], dp[2010];

int SelfMin(int &a, const int &b) {
	if (b < a) a = b;
}

bool check(const long long& x) {
	dp[1] = 0;
	for (int i = 2; i <= n; ++i) {
		dp[i] = i - 1;
		for (int j = 1; j < i; ++j)
			if (abs(a[i] - a[j]) <= (i - j) * x)
				SelfMin(dp[i], dp[j] + i - j - 1);
		if (dp[i] + n - i <= k) return true;
	}
	return false;
}

int main() {
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; ++i) scanf("%d", a + i);
	if (n <= 1) {
		puts("0"); return 0;
	}
	long long l = 0, r = 2e9, mid, ans;
	while (l <= r) {
		mid = (l + r) >> 1;
		if (check(mid)) {
			ans = mid; r = mid - 1;
		} else l = mid + 1;
	}
	printf("%I64d", ans);
	return 0;
}
