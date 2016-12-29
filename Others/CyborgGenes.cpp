#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;
int f[40][40];
char s1[40], s2[40];
long long g[40][40];

int main() {
	int T, Ca=0; scanf("%d", &T); getchar();
	while (Ca<T) {
		gets(s1+1); gets(s2+1);
		//scanf("%s\n%s",s1+1,s2+1);
		int l1=strlen(s1+1),l2=strlen(s2+1);
		memset(f,0,sizeof f);
		memset(g,0,sizeof g);
		for (int i = 1; i <= l1; ++i)
		  g[i][0] = 1LL;
		for (int i = 1; i <= l2; ++i)
		  g[0][i] = 1LL;
		g[0][0]=1LL;
		for (int i = 1; i <= l1; ++i)
		  for (int j = 1; j <= l2; ++j)
			if (s1[i]==s2[j]) {
				f[i][j] = f[i-1][j-1]+1;
				g[i][j] = g[i-1][j-1];
			} else if (f[i-1][j] ^ f[i][j-1]){
				if (f[i-1][j] < f[i][j-1]) {
					f[i][j] = f[i][j-1];
					g[i][j] = g[i][j-1];
				} else {
					f[i][j] = f[i-1][j];
					g[i][j] = g[i-1][j];
				}
			} else {
				f[i][j] = f[i-1][j];
				g[i][j] = g[i-1][j] + g[i][j-1];
			}
		printf("Case #%d: %d %lld\n", ++Ca, l1+l2-f[l1][l2], g[l1][l2]);
	}

	return 0;
}
