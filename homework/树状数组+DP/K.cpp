#include <bits/stdc++.h>
using namespace std;

const long long INF = 1LL << 60;
int val[1010][1010];
long long dpL[1010], dpR[1010], max_dp[1010][1010], sum[1010];

void SelfMax(long long &a, long long b) {
	if (a < b) a = b;
}

int main() {
	int N, M, maxval = -0x7f7f7f7f; long long ans = -INF;
	scanf("%d%d", &N, &M);
	for (int i = 1; i <= N; ++i)
		for (int j = 1; j <= M; ++j) {
			scanf("%d", val[i] + j);
			if (maxval < val[i][j]) maxval = val[i][j];
		}
	long long mv;
	for (int i = 1; i <= N; ++i) {
		mv = -INF; 
		memset(dpL, 0, sizeof dpL);
		memset(dpR, 0, sizeof dpR);
		for (int j = 1; j <= M; ++j) {
			SelfMax(dpL[j], val[i][j]);
			SelfMax(dpL[j + 1], dpL[j] + val[i][j + 1]);
			sum[j] = sum[j - 1] + val[i][j];
		}
		for (int j = M; j; --j) {
			SelfMax(dpR[j], val[i][j]);
			SelfMax(dpR[j - 1], dpR[j] + val[i][j - 1]);
		}
		mv = -INF;
		for (int j = 1; j <= M; ++j) {
			SelfMax(mv, dpL[j - 1] - sum[j - 1] + max_dp[i][j]);
			SelfMax(max_dp[i + 1][j], mv + dpR[j + 1] + sum[j]);
			SelfMax(ans, val[i][j] + dpL[j - 1] + dpR[j + 1]);
			SelfMax(ans, max_dp[i + 1][j]); 
		}
		mv = -INF;
		for (int j = M; j; --j) {
			SelfMax(ans, sum[j]+dpR[j+1]+max(max_dp[i][j],0LL));
			SelfMax(mv, dpR[j + 1] + sum[j] + max_dp[i][j]);
			SelfMax(max_dp[i + 1][j], mv + dpL[j - 1] - sum[j - 1]);
			SelfMax(ans, max_dp[i + 1][j]); 
		}
	}
	if (maxval <= 0LL && ans == 0) ans = maxval;
	printf("%lld\n", ans);
	return 0;
}
