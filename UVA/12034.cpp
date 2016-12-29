#include <cstdio>
#define mod 10056
int c[1005][1005],f[1005],i,j,n;
int main() {
	for(i=0;i<1005;++i)
	  for(c[i][0]=j=1;j<=i;++j)
		(c[i][j]=c[i-1][j]+c[i-1][j-1])>=mod?c[i][j]-=mod:1;
	for(f[0]=f[1]=1,i=2;i<1005;++i)
	  for(j=1;j<=i;++j)
		f[i]=(f[i]+c[i][j]*f[i-j])%mod;
	for(scanf("%d",&i),j=1;j<=i;++j) {
		scanf("%d",&n);
		printf("Case %d: %d\n",j,f[n]);
	}
	return 0;
}
