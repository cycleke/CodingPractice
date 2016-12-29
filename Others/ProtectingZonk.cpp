#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 1e4+5, inf = 0x3f3f3f3f;
int n, C1, C2, dp[N][3][4];
vector<int>G[N];
inline int Min(int a, int b, int c) {
	return min(min(a,b),c);
}
#define FOR(a,b) for (vector<int>::iterator a = G[b].begin(); a != G[b].end(); ++a)
void cal(int u, int fa) {
	FOR(it, u) if (*it ^ fa) cal(*it, u);
	int sum = 0;
	FOR(it, u) if (*it ^ fa)
		sum += Min(dp[*it][0][1],dp[*it][1][2],dp[*it][2][3]);
	int t0 = inf;
	FOR (it, u) if (*it ^ fa)
		t0 = min(t0, sum - Min(dp[*it][0][1],dp[*it][1][2],dp[*it][2][3])+dp[*it][2][3]);
	dp[u][0][0] = t0, dp[u][1][0] = t0 + C1, dp[u][2][0] = t0 + C2;

	for (int k = 1; k < 4; ++k) {
		int tmp = 0;
		FOR (it, u) if (*it ^ fa)
			tmp += Min(dp[*it][0][k-1],dp[*it][1][2],dp[*it][2][3]);
		FOR (it, u) if (*it ^ fa)
			tmp = min(tmp, sum - Min(dp[*it][0][1],dp[*it][1][2],dp[*it][2][3])+dp[*it][2][3]);
		dp[u][0][k] = tmp, dp[u][1][k] = tmp + C1, dp[u][2][k] = tmp + C2;
	}

}

int main() {
	int a, b;
	while (scanf("%d%d%d",&n,&C1,&C2)!=EOF&&n) {

		for (int i = 1; i <= n; ++i) G[i].clear();

		for (int i = 1; i < n; ++i) {
			scanf("%d%d", &a, &b);
			G[a].push_back(b);
			G[b].push_back(a);
		}

		memset(dp, 63, sizeof dp);

		cal(1, -1);

		printf("%d\n", Min(dp[1][0][1], dp[1][1][2], dp[1][2][3]));

	}
	return 0;
}
