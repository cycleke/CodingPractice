#include <cstdio>
#include <cstring>

int sum[30][30], dp[30][30][30][30];
inline int min(int a, int b) {return a<b?a:b;}
inline int getsum(int a, int b, int c, int d) {
	--a, --b;
	return sum[c][d] - sum[a][d] - sum[c][b] + sum[a][b];
}

bool mark[30][30];

int main() {
	int n, m, t, _x, _y,Case=0;
	while (scanf("%d%d%d",&n,&m,&t)^EOF) {
		memset(mark, 0, sizeof mark);
		while (t--) {
			scanf("%d%d", &_x, &_y);
			mark[_x][_y] = 1;
		}
		for (int i = 1; i <= n; ++i)
		  for (int j = 1; j <= m; ++j)
			sum[i][j] = sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+mark[i][j];
		for (int x = 1; x <= n; ++x)
		  for (int y = 1; y <= m; ++y)
			for (int i = 1; i+x-1 <= n; ++i)
			  for (int j = 1; j+y-1 <= m; ++j) {
				  int _i =i+x-1,_j=j+y-1;
				  int s = getsum(i,j,_i,_j);
				  if ((i==_i&&j==_j)||(s<2))
					dp[i][j][x][y]=0;
				  else if (i==_i||j==_j)
					dp[i][j][x][y]=s-1;
				  else {
					  dp[i][j][x][y]=0x7f7f7f7f;
					  for (int k = i; k < _i; ++k)
						if (getsum(i,j,k,_j)>0&&getsum(k+1,j,_i,_j)>0)
						  dp[i][j][x][y]=min(dp[i][j][x][y],dp[i][j][k-i+1][y]+dp[k+1][j][_i-k][y]+y);
					  for (int k = j; k < _j; ++k)
						if (getsum(i,j,_i,k)>0&&getsum(i,k+1,_i,_j)>0)
						  dp[i][j][x][y]=min(dp[i][j][x][y],dp[i][j][x][k-j+1]+dp[i][k+1][x][_j-k]+x);
				  }
				  //printf("%d %d %d %d %d\n", i, j, x, y, dp[i][j][x][y]);
			  }
		printf("Case %d: %d\n", ++Case, dp[1][1][n][m]);
	}
	return 0;
}
