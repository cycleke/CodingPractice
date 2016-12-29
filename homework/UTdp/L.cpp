#include <bits/stdc++.h>
using namespace std;

const int Maxn = 1000005;
int a[Maxn], q[Maxn << 1], sum[Maxn << 1], dp[Maxn << 1];

int main() {
	int n, k; 
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; ++i) { scanf("%d", a + i); sum[i] = sum[i - 1] + a[i]; }
	for (int i = 1; i <= n; ++i) sum[i + n] = sum[i + n - 1] + a[i];
	int top(0), tail(0), l(1), r(1); n <<= 1, dp[1] = a[1];
	q[tail++] = 1;
	for (int i = 2; i < n; ++i) {
		while (top < tail && i - q[top] > k) ++top;
		if (dp[i - 1] < sum[i] - sum[q[top]]) {
			dp[i] = sum[i] - sum[q[top]];
			l = q[top] + 1, r = i;
		} else dp[i] = dp[i - 1];
		while (top < tail && sum[i] < sum[q[tail - 1]]) --tail;
		q[tail++] = i;
	} 
	n >>= 1;
	if (l > n) l -= n; if (r > n) r -= n;
	printf("%d %d %d\n", dp[n * 2 - 1], l, r);
	return 0;
}
