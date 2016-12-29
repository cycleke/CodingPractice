#include <cstdio>
#include <cstring>
#define N 100010
int a[N],mx[N],dp[N];
#define max(a,b) (a<b?b:a)
int main() {
	int n,m,i,j,k,mxx;
	while(scanf("%d%d",&m,&n)^EOF) {
		for(i=1;i<=n;++i) scanf("%d",a+i),mx[i]=dp[i]=0;
		dp[0]=mx[0]=0;
		for(i=1;i<=m;++i) {
			mxx=-0x7f7f7f7f;
			for(j=i;j<=n;++j) {
				dp[j]=max(dp[j-1],mx[j-1])+a[j];
				mx[j-1]=mxx;
				mxx=max(mxx,dp[j]);
			}
		}
		printf("%d\n",mxx);
	}return 0;
}
