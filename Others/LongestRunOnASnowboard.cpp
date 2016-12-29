#include <cstdio>
#include <cstring>
#define cmax(a,b) ((__t=(b))>a?a=__t:1)

int dp[110][110],h[110][110];

const int dx[]={1,-1,0,0};
const int dy[]={0,0,1,-1};

int cal(int x, int y) {
	if (~dp[x][y]) return dp[x][y];
	dp[x][y] = 0; int __t;
	for (int i = 0; i < 4; ++i) {
		int _x = x + dx[i], _y = y + dy[i];
		if (h[_x][_y]<h[x][y]) cmax(dp[x][y],cal(_x,_y)+1);
	}
	return dp[x][y];
}

int main() {
	char name[100]; int T,n,m,ans,__t;
	scanf("%d",&T);
	while (T--) {
		scanf("%s %d %d", name, &n, &m);
		memset(h, 127, sizeof h);
		for (int i = 1; i <= n; ++i)
		  for (int j = 1; j <= m; ++j)
			scanf("%d", h[i] + j);
		memset(dp, -1, sizeof dp);
		ans = 0;
		for (int i = 1; i <= n; ++i)
		  for (int j = 1; j <= m; ++j)
			cmax(ans,cal(i,j));
		printf("%s: %d\n", name, ans+1);
	}


	return 0;
}
