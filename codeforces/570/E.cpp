#include <bits/stdc++.h>
using namespace std;

const int Mod = 1e9 + 7, N = 505;
#define Add(a,b) (a = (a + b), (a >= Mod) ? a -= Mod : 1)
int dp[2][N][N]; char mp[N][N];

int main() {
	int n, m, cur, Siz = sizeof dp[0]; scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i) scanf("%s", mp[i] + 1);
	if (mp[1][1] ^ mp[n][m]) return puts("0"), 0;
	dp[cur = 1][1][n] = 1; 
	for (int s = 2, end = n + m >> 1; s <= end; ++s) {
		memset(dp[cur ^= 1], 0, Siz);
		for (int x1 = 1; x1 <= s; ++x1)
		  for (int x2 = n, _t = n - s + 1; x2 >= _t; --x2) {
				int y1 = s + 1 - x1, y2 = n + m + 1 - s - x2;
				if (x1 > x2 || y1 > y2) continue;
				if (mp[x1][y1] ^ mp[x2][y2]) continue;
				Add(dp[cur][x1][x2], dp[cur^1][x1][x2]);
				Add(dp[cur][x1][x2], dp[cur^1][x1][x2+1]);
				Add(dp[cur][x1][x2], dp[cur^1][x1-1][x2]);
				Add(dp[cur][x1][x2], dp[cur^1][x1-1][x2+1]);
		  }
	}
	int ans = 0;
	if (n + m & 1) for (int i = 1; i <= n; ++i) Add(ans, dp[cur][i][i]), Add(ans, dp[cur][i][i+1]);
	else for (int i = 1; i <= n; ++i) Add(ans, dp[cur][i][i]);
	printf("%d\n", ans);
	return 0;
}
