#include <bits/stdc++.h>
using namespace std;

const int Maxn = 1010, INF = 0x7f7f7f7f;
int a[Maxn], b[Maxn];
int dp[Maxn][(1 << 8) + 10][22];

void SelfMin(int &a, const int &b) {
	if (b < a) a = b; 
}

int Cal(const int &a, const int &b) {
	return (a | b) - (a & b);
}

int main() {
	int n, all = 1 << 8;
	scanf("%d", &n);
	memset(dp, 0x7f, sizeof dp);
	dp[0][all - 1][19] = 0;
	for (int i = 1; i <= n; ++i) scanf("%d%d", a + i, b + i);
	for (int i = 0; i <= n; ++i) 
	for (int j = 0; j < all; ++j)
	for (int k = 0; k < 20; ++k) 
		if (dp[i][j][k] != INF) {
			int ed = min(8, i), CanOff = INF;
			for (int p = ed - 1; p >= 0; --p) 
				if (((j >> p) & 1) == 0) SelfMin(CanOff, i - p + b[i - p]);
			if ((j >> 7) & 1) SelfMin(dp[i + 1][(j ^ (1 << 7)) << 1][min(k + 1, 19)], dp[i][j][k]);
			for (int p = ed - 1; p >= 0 && i - p <= CanOff; --p)
				if (((j >> p) & 1) == 0)
					SelfMin(dp[i][j | (1 << p)][p], 
					dp[i][j][k] + ((k == 19) ? a[i - p] : Cal(a[i - p], a[i - k])));
		}
	int ans = INF;
	for (int i = 0; i < 20; ++i) SelfMin(ans, dp[n][all - 1][i]);
	cout << ans;
	return 0;
}
