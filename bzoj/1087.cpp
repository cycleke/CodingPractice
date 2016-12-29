#include <cstdio>
long long dp[10][150][85];
int c[200],ct[200];
inline int CT(int i) {
    int r=0;
    for(;i;i=i&(i-1))++r;
	return r;
}
int main() {
    int n,K;
    scanf("%d%d",&n,&K);
	register int i,j,k,ck,en=1<<n,cs=0;
	for(i=0;i<en;++i)((i<<1)&i)?1:(c[cs]=i,ct[cs]=CT(i),++cs);
	dp[0][0][0]=1;
	for(k=1;k<=n;++k)
		for(i=0;i<cs;++i)
			for(ck=0;ck<=K;++ck)
				if(dp[k-1][i][ck])for(j=0;j<cs;++j)
									  if(ck+ct[j]<=K&&!((c[i]&c[j])|(c[i]<<1&c[j])|(c[i]>>1&c[j])))
										  dp[k][j][ck+ct[j]]+=dp[k-1][i][ck];
	long long ans=0;
	for(i=0;i<cs;++i)ans+=dp[n][i][K];
	printf("%lld\n",ans);
	return 0;
}
