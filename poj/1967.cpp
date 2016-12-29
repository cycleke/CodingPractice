#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
inline void cmin(int &a,int b) {a<b?1:a=b;}
#define inf 0x3f3f3f3f

#define N 10010
int dp[2][N][2], a[N], b[N];

int main() {
	int n, id;
	while (scanf("%d",&n)^EOF) {
		id = 0;
		for (int i = 1; i <= n; ++i) {
		  scanf("%d%d",a+i,b+i);
		  if (b[i] <= 0) id = -1;
		}
		if (id) {puts("No solution"); continue;}
		memset(dp, 0, sizeof dp);
		for (int i = 1; i < n; ++i) {
			id ^= 1;
			for (int j = 1; j <= n - i; ++j) {
				dp[id][j][0]=min(dp[id^1][j+1][0]+a[j+1]-a[j],dp[id^1][j+1][1]+a[j+i]-a[j]);
				dp[id][j][1]=min(dp[id^1][j][0]+a[j+i]-a[j],dp[id^1][j][1]+a[i+j]-a[i+j-1]);
				if (dp[id][j][0]>=b[j]) dp[id][j][0]=inf;
				if (dp[id][j][1]>=b[i+j]) dp[id][j][1]=inf;
			}
		}
		int t = min(dp[id][1][0],dp[id][1][1]);
		if (t ^ inf) printf("%d\n", t);
		else puts("No solution");
	}
	return 0;
}
