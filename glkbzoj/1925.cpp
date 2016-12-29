#include <cstdio>
#include <cstring>
int dp[2][4203];
int main() {
	int siz=sizeof dp[0],*f=dp[0],*g=dp[1],*t,n,mo;
	register int i,j,an;
	scanf("%d%d",&n,&mo);
	f[1]=1;
	for(i=2;i<=n;++i) {
		t=f,f=g,g=t;
		memset(f,0,siz);
		for(j=1;j<=i;++j)
			for(f[j]=f[j-1]+g[i-j+1];f[j]>=mo;f[j]-=mo);
	}
	for(an=0,i=1;i<=n;++i)
		for(an+=f[i];an>=mo;an-=mo);
	(an=an<<1)>=mo?an-=mo:1;
	printf("%d\n",an);
	return 0;
}
