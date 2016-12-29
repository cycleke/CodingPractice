#include <cstdio>
#define ll long long
int n,g[4][33],i,j,k,x,y;
bool vis[4];
ll f[4][33];
char s[4];
int main() {
	for(scanf("%d",&n),i=0;i<6;++i) {
		scanf("%s",s);
		x=*s-'A'+1,y=s[1]-'A'+1;
		vis[x]?1:(vis[x]=true,g[x][1]=y,f[x][1]=1LL,1);
	}
	for(i=2;i<=n;++i)
	  for(j=1;j<4;++j){
		y=g[j][i-1],k=6-y-j;
		(k^g[y][i-1])?(f[j][i]=(f[j][i-1]<<1)+2+f[y][i-1],g[j][i]=y):(f[j][i]=f[j][i-1]+f[y][i-1]+1,g[j][i]=k);
	  }
	printf("%lld\n",f[1][n]);
	return 0;
}
