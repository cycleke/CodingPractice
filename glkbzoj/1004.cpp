#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const int N = 65, M = 105;
int n, m, p, sr, sb, sg;
int dp[N][N][N], cha[M][N], d[N];
bool vis[N];
#define Inc(a,b) ((a) = ((a) + (b))%p)
int Cal(const int &x) {
	memset(dp, 0, sizeof dp); 
	memset(vis, 0, sizeof vis);
	int Sum = 0, t;
	for (int i = 1; i <= n; ++i) 
	  if (!vis[i]) {
		  d[++Sum] = 1; vis[t = i] = true;
		  while (!vis[cha[x][t]]) {
			  ++d[Sum]; t = cha[x][t];
			  vis[t] = true;
		  }
	  }
	dp[0][0][0] = 1;
	for (t = 1; t <= Sum; ++t)
	  for (int i = sr; ~i; --i)
		for (int j = sb; ~j; --j)
		  for (int k = sg; ~k; --k) {
			  if (i >= d[t]) Inc(dp[i][j][k], dp[i-d[t]][j][k]);
			  if (j >= d[t]) Inc(dp[i][j][k], dp[i][j-d[t]][k]);
			  if (k >= d[t]) Inc(dp[i][j][k], dp[i][j][k-d[t]]);
		  }
	//printf("%d\n", dp[sr][sb][sg]);
	return dp[sr][sb][sg];
}

long long Mod_Pow(long long b, int c) {
	long long ans = 1LL;
	while (c) {
		if (c&1) ans = ans * b % p;
		b = b * b % p;
		c >>= 1;
	}
	return ans;
}

int main() {
	scanf("%d%d%d%d%d", &sr, &sb, &sg, &m, &p);
	n = sr + sb + sg;
	for (int i = 1; i <= m; ++i)
	  for (int j = 1; j <= n; ++j)
		scanf("%d", cha[i] + j);
	++m;
	long long ans = 0;
	for (int i = 1; i <= n; ++i) cha[m][i] = i;
	for (int i = 1; i <= m; ++i) Inc(ans, Cal(i));
	//printf("%d\n", ans);
	ans = ans * Mod_Pow(m, p - 2) % p;
	printf("%lld\n", ans);
	return 0;
}

