#include <cstdio>
long long f[22][22][22];
int i,j,k,t;
int main() {
	f[1][1][1]=1;
	for(i=2;i<22;++i)
	  for(j=1;j<=i;++j)
		for(k=1;k<=i;++k)
		  f[i][j][k]=f[i-1][j-1][k]+f[i-1][j][k-1]+f[i-1][j][k]*(i-2);
	for(scanf("%d",&t);t;--t) {
		scanf("%d%d%d",&i,&j,&k);
		printf("%lld\n",f[i][j][k]);
	}
	return 0;
}
