#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
#define inf 0x3f3f3f3f
int p[35], f[35][110], g[35][110];

int main() {
	int n, m;
	while (scanf("%d%d",&n,&m)^EOF) {
		if (!(n|m)) break;
		
		for (int i = 1; i <= m; ++i)
		  scanf("%d", p + i);
		
		memset(f, 0, sizeof f);

		for (int i = 1; i <= m; ++i) {
			f[i-1][0] = inf;
			for (int j = 1; j <= n; ++j) {
				f[i][j] = f[i-1][j];
				for (int k = 1; k <= j; ++k)
				  f[i][j] = max(f[i][j],min(f[i-1][j-k],p[i]/k));
			}
		}

		memset(g, 63, sizeof g);

		for (int i = 1; i <= m; ++i) {
			g[i-1][0] = 0;
			for (int j = 1; j <= n; ++j) {
				g[i][j] = g[i-1][j];
				for (int k = 1; k <= j; ++k) 
				  if (p[i]/k>=f[m][n])
					g[i][j]=min(g[i][j],g[i-1][j-k]+p[i]);
				else break;
			}
		}
		if (!f[m][n]) g[m][n]=0;
		printf("%d %d\n", f[m][n], g[m][n]);
	}
	return 0;
}
