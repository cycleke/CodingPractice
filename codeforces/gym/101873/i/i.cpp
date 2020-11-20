// by OwenCreeper
#include "bits/stdc++.h"
#define N 10000000
using namespace std;
int dp[N + 5], n, m;
int main(int argc, char const *argv[]) {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) {
		int x;
		scanf("%d", &x);
		if (i <= m) continue;
		dp[i] = max(dp[i - 1], dp[i - m] + x);
		// printf("%d ", dp[i]);
	}
	// puts("");
	printf("%d\n", dp[n]);
	return 0;
}
