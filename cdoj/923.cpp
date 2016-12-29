#include <cstdio>
#include <cstring>
#define N 705
#define M 10001
inline int gcd(int a, int b) {
	for (int t = a % b; t; a = b, b = t, t = a % b);
	return b;
}
int dp[M];
int main() {
	int n, i, G = 0, g, a, j;
	memset(dp, 63, sizeof dp); *dp = 0;
	for (scanf("%d", &n), j = n; j; --j) {
		scanf("%d", &a); G = gcd(G, a);
		for (i = N - 1; ~i; --i) {
			g = gcd(i, a);
			if (dp[g] > dp[i] + 1) dp[g] = dp[i] + 1;
		}
	}
	printf("%d", n - dp[G]);
	return 0;
}
