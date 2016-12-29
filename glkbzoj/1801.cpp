#include <cstdio>
#define mod 9999973LL
#define ll long long
#define add(a) (f[i][j][k]=(f[i][j][k]+(a)%mod)%mod)
ll f[105][105][105];
int main() {
	int n,m,i,j,k,ans=0;
	scanf("%d%d",&n,&m);
	f[0][0][0]=1;
	for(i=1;i<=n;++i)
	for(j=0;j<=m;++j)
	for(k=0;k<=m-j;++k) {
		f[i][j][k]=f[i-1][j][k];
		(k)?add(f[i-1][j+1][k-1]*(j+1)),add(f[i-1][j][k-1]*j*(m-k-j+1)):1;
		(j)?add(f[i-1][j-1][k]*(m-k-j+1)):1;
		(1<k)?add(f[i-1][j+2][k-2]*(j+2)*(j+1)/2):1;
		(1<j)?add(f[i-1][j-2][k]*(m-j-k+2)*(m-j-k+1)/2):1;
	}
	for(j=0;j<=m;++j) for(k=0;k<=m-j;++k)
	ans=(ans+f[n][j][k])%mod;
	return printf("%d\n",ans),0;
}
